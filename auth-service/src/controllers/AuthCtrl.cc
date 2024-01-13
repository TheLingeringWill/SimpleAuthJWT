
#include <drogon/drogon.h>

// Controller includes
#include "AuthCtrl.h"

// Project includes
#include "utils.h"

namespace drogon::famy_auth
{
Task<>
AuthCtrl::signUp(HttpRequestPtr req, AdviceCallback callback)
{
  // Using statement
  using drogon::famy_utils::createHttpRequest;
  using drogon::famy_utils::createHttpResponse;
  using drogon::famy_utils::createJsonResponse;
  using drogon::famy_utils::getObject;
  using drogon::orm::CompareOperator;
  using drogon::orm::Criteria;
  using drogon::orm::UnexpectedRows;

  try
  {
    const auto& jsonRequestPtr = getObject(req->getJsonObject());

    auto response = co_await proxyAccountHandler_->sendRequestCoro(
      createHttpRequest(std::move(*jsonRequestPtr), "/v1/account", Post)
    );

    auto statusCodeResponse = response->getStatusCode();

    switch(statusCodeResponse)
    {
      case k403Forbidden:
        callback(createHttpResponse(
          std::move(createJsonResponse(
            std::make_pair("status", k403Forbidden),
            std::make_pair("code", "FORBIDDEN"),
            std::make_pair("message", "User has already been registered")
          )),
          k403Forbidden
        ));
        break;
      case k201Created:
      case k202Accepted:
      {
        auto&& jsonMessageResponse =
          std::move(*getObject((response->getJsonObject()))) ["message"];

        const auto& id =
          jsonMessageResponse [Account::tableName][Account::Cols::_id].asUInt64(
          );

        CoroMapper<Auth> mapper(getDbClient());

        auto authFound = co_await mapper.findBy(
          Criteria(Auth::Cols::_id, CompareOperator::EQ, id)
        );

        const auto& emailAccount =
          (*jsonRequestPtr) [Account::Cols::_email].asString();

        const auto& verifyToken =
          getJWTPlugin()->create(emailAccount, std::chrono::seconds(1500));

        Auth authToInsert;
        authToInsert.setId(id);
        authToInsert.setVerifyToken(verifyToken);

        if(authFound.size() > 1)
        {
          throw UnexpectedRows("More than one ressources has been found");
        }
        else
        {
          jsonMessageResponse [Auth::tableName] = authToInsert.toJson();

          if(authFound.empty())
          {
            [[maybe_unused]] auto auth = co_await mapper.insert(authToInsert);

            callback(createHttpResponse(
              std::move(createJsonResponse(
                std::make_pair("status", k201Created),
                std::make_pair("code", "CREATED"),
                std::make_pair("message", jsonMessageResponse)
              )),
              k201Created
            ));
          }
          else
          {
            auto count = co_await mapper.update(authToInsert);

            if(! count)
            {
              throw UnexpectedRows("No ressource has been updated");
            }

            callback(createHttpResponse(
              std::move(createJsonResponse(
                std::make_pair("status", k202Accepted),
                std::make_pair("code", "ACCEPTED"),
                std::make_pair("message", jsonMessageResponse)
              )),
              k202Accepted
            ));
          }
          std::cout << "coucou" << std::endl;
          getSMTPMailPlugin()->sendEmail(
            emailAccount,
            "Verify your email",
            "please click on here : http://localhost:3000/auth/" +
              std::to_string(id) + "/confirm-email/" + verifyToken,
            false,
            [](const std::string& message) { std::cout << message; }
          );
          break;
        }
      }
      default:
        callback(response);
    }
  }
  catch(const DrogonDbException& e)
  {
    callback(createHttpResponse(
      std::move(createJsonResponse(
        std::make_pair("status", k500InternalServerError),
        std::make_pair("code", "INTERNAL_SERVER_ERROR"),
        std::make_pair("message", e.base().what())
      )),
      k500InternalServerError
    ));
  }
  catch([[maybe_unused]] const std::runtime_error& e)
  {
    callback(createHttpResponse(
      std::move(createJsonResponse(
        std::make_pair("status", k400BadRequest),
        std::make_pair("code", "UNAUTHORIZED"),
        std::make_pair("message", "No json object is found in the request")
      )),
      k400BadRequest
    ));
  }
}

Task<>
AuthCtrl::confirmSignUp(
  HttpRequestPtr req,
  AdviceCallback callback,
  std::string&& token
)
{
  // Using statement
  using drogon::famy_utils::createHttpRequest;
  using drogon::famy_utils::createHttpResponse;
  using drogon::famy_utils::createJsonResponse;
  using drogon::orm::CompareOperator;
  using drogon::orm::Criteria;
  using drogon::orm::UnexpectedRows;

  if(const auto& tokenReceived =
       req->getAttributes()->get<std::string>("token");
     tokenReceived == std::move(token))
  {
    CoroMapper<Auth> mapper(getDbClient());
    try
    {
      auto authFound = co_await mapper.findOne(
        Criteria(Auth::Cols::_verify_token, CompareOperator::EQ, tokenReceived)
      );

      auto accountResponse = co_await proxyAccountHandler_->sendRequestCoro(
        std::move(createHttpRequest(
          std::move(createJsonResponse(
            std::make_pair(Account::Cols::_id, authFound.getValueOfId()),
            std::make_pair(Account::Cols::_is_verified, true)
          )),
          "/v1/account/" + std::to_string(authFound.getValueOfId()),
          Put
        ))
      );

      if(auto&& jsonResponsePtr = accountResponse->getJsonObject();
         jsonResponsePtr)
      {
        callback(createHttpResponse(
          std::move(createJsonResponse(
            std::make_pair("status", k202Accepted),
            std::make_pair("code", "ACCEPTED"),
            std::make_pair(
              "message",
              createJsonResponse(
                std::make_pair(Auth::tableName, authFound.toJson()),
                std::make_pair(
                  Account::tableName,
                  (*jsonResponsePtr) ["message"][Account::tableName]
                )
              )
            )
          )),
          k202Accepted
        ));
      }
      else
      {
        callback(createHttpResponse(
          std::move(createJsonResponse(
            std::make_pair("status", k500InternalServerError),
            std::make_pair("code", "INTERNAL_SERVER_ERROR"),
            std::make_pair(
              "message",
              "Account service does not respond correctly"
            )

          )),
          k500InternalServerError
        ));
      }
    }
    catch(const DrogonDbException& e)
    {
      callback(createHttpResponse(
        std::move(createJsonResponse(
          std::make_pair("status", k404NotFound),
          std::make_pair("code", "NOT_FOUND"),
          std::make_pair("message", e.base().what())
        )),
        k404NotFound
      ));
    }
  }
  else
  {
    callback(createHttpResponse(
      std::move(createJsonResponse(
        std::make_pair("status", k500InternalServerError),
        std::make_pair("code", "UNAUTHORIZED_ACCESS"),
        std::make_pair(
          "message",
          "Unauthorized access for the requested content"
        )
      )),
      k500InternalServerError
    ));
  }
}

drogon::Task<>
AuthCtrl::signIn(HttpRequestPtr req, AdviceCallback callback)
{
  // Using statement
  using drogon::famy_utils::createHttpRequest;
  using drogon::famy_utils::createHttpResponse;
  using drogon::famy_utils::createJsonResponse;
  using drogon::famy_utils::getObject;
  using drogon::orm::CompareOperator;
  using drogon::orm::Criteria;
  using drogon::orm::UnexpectedRows;

  try
  {
    const auto& jsonRequestPtr = getObject(req->jsonObject());

    auto accountResponse = co_await proxyAccountHandler_->sendRequestCoro(
      std::move(createHttpRequest(
        std::move(*jsonRequestPtr),
        "/v1/account/sign-in",
        Get
      ))
    );

    auto jsonAccountResponse = getObject(accountResponse->getJsonObject());

    if(accountResponse->getStatusCode() == k200OK)
    {
      Auth authToUpdate;

      const auto& otp = drogon::utils::getUuid().substr(0, 8);
      authToUpdate.setOtp(otp);
      authToUpdate.setId((*jsonAccountResponse
      ) ["message"][Account::tableName][Account::Cols::_id]
                           .asUInt64());

      CoroMapper<Auth> mapper(getDbClient());
      std::cout << authToUpdate.toJson();
      auto count = co_await mapper.update(authToUpdate);
      std::cout << authToUpdate.toJson();
      if(count)
      {
        const auto& emailAccount =
          (*jsonRequestPtr) [Account::Cols::_email].asString();

        getSMTPMailPlugin()->sendEmail(
          emailAccount,
          "Verify your email",
          "Here is the code : " + otp,
          false,
          [](const std::string& message) { std::cout << message; }
        );

        callback(createHttpResponse(
          std::move(createJsonResponse(
            std::make_pair("status", k202Accepted),
            std::make_pair("code", "ACCEPTED"),
            std::make_pair("message", (*jsonAccountResponse) ["message"])

          )),
          k202Accepted
        ));
      }
      else if(! count)
      {
        callback(createHttpResponse(
          std::move(createJsonResponse(
            std::make_pair("status", k404NotFound),
            std::make_pair("code", "NOT_FOUND"),
            std::make_pair("message", "No ressources are updated")
          )),
          k404NotFound
        ));
      }
      else
      {
        callback(createHttpResponse(
          std::move(createJsonResponse(
            std::make_pair("status", k404NotFound),
            std::make_pair("code", "NOT_FOUND"),
            std::make_pair(
              "message",
              "More than one resource is updated : " + std::to_string(count)
            )
          )),
          k404NotFound
        ));
      }
    }
    else
    {
      callback(createHttpResponse(std::move(*jsonAccountResponse), k404NotFound)
      );
    }
  }
  catch(const DrogonDbException& e)
  {
    callback(createHttpResponse(
      std::move(createJsonResponse(
        std::make_pair("status", k500InternalServerError),
        std::make_pair("code", "INTERNAL_SERVER_ERROR"),
        std::make_pair("message", e.base().what())
      )),
      k500InternalServerError
    ));
  }
  catch([[maybe_unused]] const std::runtime_error& e)
  {
    callback(createHttpResponse(
      std::move(createJsonResponse(
        std::make_pair("status", k401Unauthorized),
        std::make_pair("code", "UNAUTHORIZED"),
        std::make_pair("message", "No json object is found in the request")
      )),
      k401Unauthorized
    ));
  }
}

Task<>
AuthCtrl::confirmSignIn(HttpRequestPtr req, AdviceCallback callback)
{
  // Using statement
  using drogon::famy_utils::createHttpResponse;
  using drogon::famy_utils::createJsonResponse;
  using drogon::famy_utils::getObject;
  using drogon::orm::CompareOperator;
  using drogon::orm::Criteria;
  using drogon::orm::UnexpectedRows;

  try
  {
    const auto& jsonRequestPtr = getObject(req->jsonObject());

    CoroMapper<Auth> mapperAuth(getDbClient());

    auto authFound = co_await mapperAuth.findOne(
      Criteria(
        Auth::Cols::_id,
        CompareOperator::EQ,
        (*jsonRequestPtr) [Auth::Cols::_id].asUInt64()
      ) &&
      Criteria(
        Auth::Cols::_otp,
        CompareOperator::EQ,
        (*jsonRequestPtr) [Auth::Cols::_otp].asString()
      )
    );

    auto jwtPlugin = getJWTPlugin();
    auto emailFound = (*jsonRequestPtr) [Account::Cols::_email].asString();
    auto token = getJWTPlugin()->create(emailFound);

    Auth authToUpdate {authFound};
    authToUpdate.setRefreshToken(
      jwtPlugin->create(emailFound, std::chrono::seconds(25000))
    );

    size_t count = co_await mapperAuth.update(authToUpdate);

    if(count)
    {
      callback(HttpResponse::newHttpJsonResponse(std::move(createJsonResponse(
        std::make_pair("status", k200OK),
        std::make_pair("code", "OK"),
        std::make_pair(
          "message",
          createJsonResponse(std::make_pair("token", token))
        )
      ))));
    }
    else
    {
      callback(createHttpResponse(
        std::move(createJsonResponse(
          std::make_pair("status", k500InternalServerError),
          std::make_pair("code", "INTERNAL_SERVER_ERROR"),
          std::make_pair("message", "no row updated")
        )),
        k500InternalServerError
      ));
    }
  }
  catch(const DrogonDbException& e)
  {
    callback(createHttpResponse(
      std::move(createJsonResponse(
        std::make_pair("status", k500InternalServerError),
        std::make_pair("code", "INTERNAL_SERVER_ERROR"),
        std::make_pair("message", e.base().what())
      )),
      k500InternalServerError
    ));
  }
  catch([[maybe_unused]] const std::runtime_error& e)
  {
    callback(createHttpResponse(
      std::move(createJsonResponse(
        std::make_pair("status", k401Unauthorized),
        std::make_pair("code", "UNAUTHORIZED"),
        std::make_pair("message", "No json object is found in the request")
      )),
      k401Unauthorized
    ));
  }
}

Task<>
getCredentialsFromGoogle(
  HttpRequestPtr req,
  AdviceCallback callback,
  std::string&& code
)
{
  co_return;
}

/*
void AuthCtrl::deleteOne(const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    drogon_model::famy_auth::Auth::PrimaryKeyType&& id)
{

    auto dbClientPtr = *dbClient_();
    auto callbackPtr =
        std::make_shared<std::function<void(const HttpResponsePtr&)>>(
            std::move(callback));
    drogon::orm::Mapper<Auth> mapper(dbClientPtr);
    mapper.deleteByPrimaryKey(
        id,
        [callbackPtr](const size_t count) {
            if (count == 1)
            {
                auto resp = HttpResponse::newHttpResponse();
                resp->setStatusCode(k204NoContent);
                (*callbackPtr)(resp);
            }
            else if (count == 0)
            {
                Json::Value ret;
                ret["error"] = "No resources deleted";
                auto resp = HttpResponse::newHttpJsonResponse(ret);
                resp->setStatusCode(k404NotFound);
                (*callbackPtr)(resp);
            }
            else
            {
                LOG_FATAL << "Delete more than one records: " << count;
                Json::Value ret;
                ret["error"] = "Database error";
                auto resp = HttpResponse::newHttpJsonResponse(ret);
                resp->setStatusCode(k500InternalServerError);
                (*callbackPtr)(resp);
            }
        },
        [callbackPtr](const DrogonDbException& e) {
            LOG_ERROR << e.base().what();
            Json::Value ret;
            ret["error"] = "database error";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k500InternalServerError);
            (*callbackPtr)(resp);
        });

}

void AuthCtrl::get(const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback)
{

    auto dbClientPtr = *dbClient_();
    drogon::orm::Mapper<Auth> mapper(dbClientPtr);
    auto& parameters = req->parameters();
    auto iter = parameters.find("sort");
    if (iter != parameters.end())
    {
        auto sortFields = drogon::utils::splitString(iter->second, ",");
        for (auto& field : sortFields)
        {
            if (field.empty())
                continue;
            if (field[0] == '+')
            {
                field = field.substr(1);
                mapper.orderBy(field, SortOrder::ASC);
            }
            else if (field[0] == '-')
            {
                field = field.substr(1);
                mapper.orderBy(field, SortOrder::DESC);
            }
            else
            {
                mapper.orderBy(field, SortOrder::ASC);
            }
        }
    }
    iter = parameters.find("offset");
    if (iter != parameters.end())
    {
        try {
            auto offset = std::stoll(iter->second);
            mapper.offset(offset);
        }
        catch (...)
        {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }
    }
    iter = parameters.find("limit");
    if (iter != parameters.end())
    {
        try {
            auto limit = std::stoll(iter->second);
            mapper.limit(limit);
        }
        catch (...)
        {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }
    }
    auto callbackPtr =
        std::make_shared<std::function<void(const HttpResponsePtr&)>>(
            std::move(callback));
    auto jsonPtr = req->jsonObject();
    if (jsonPtr && jsonPtr->isMember("filter"))
    {
        try {
            auto criteria = makeCriteria((*jsonPtr)["filter"]);
            mapper.findBy(criteria,
                [req, callbackPtr, this](const std::vector<Auth>& v) {
                    Json::Value ret;
                    ret.resize(0);
                    for (auto& obj : v)
                    {
                        ret.append(makeJson(req, obj));
                    }
                    (*callbackPtr)(HttpResponse::newHttpJsonResponse(ret));
                },
                [callbackPtr](const DrogonDbException& e) {
                    LOG_ERROR << e.base().what();
                    Json::Value ret;
                    ret["error"] = "database error";
                    auto resp = HttpResponse::newHttpJsonResponse(ret);
                    resp->setStatusCode(k500InternalServerError);
                    (*callbackPtr)(resp);
                });
        }
        catch (const std::exception& e)
        {
            LOG_ERROR << e.what();
            Json::Value ret;
            ret["error"] = e.what();
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k400BadRequest);
            (*callbackPtr)(resp);
            return;
        }
    }
    else
    {
        mapper.findAll([req, callbackPtr, this](const std::vector<Auth>& v) {
            Json::Value ret;
            ret.resize(0);
            for (auto& obj : v)
            {
                ret.append(makeJson(req, obj));
            }
            (*callbackPtr)(HttpResponse::newHttpJsonResponse(ret));
            },
            [callbackPtr](const DrogonDbException& e) {
                LOG_ERROR << e.base().what();
                Json::Value ret;
                ret["error"] = "database error";
                auto resp = HttpResponse::newHttpJsonResponse(ret);
                resp->setStatusCode(k500InternalServerError);
                (*callbackPtr)(resp);
            });
    }

}
*/
}   // namespace drogon::famy_auth
