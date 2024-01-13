
// Standard library includes
#include <string>

// 3rdparty includes
#include <drogon/drogon.h>
#include <drogon/orm/Exception.h>

// Controller includes
#include "AccountCtrl.h"

// Project includes
#include "utils.h"

namespace drogon::famy_account
{
Task<>
AccountCtrl::getOne(HttpRequestPtr req, AdviceCallback callback)
{
  using drogon::orm::UnexpectedRows;
  using Criteria = drogon::orm::Criteria;
  using CompareOperator = drogon::orm::CompareOperator;
  using drogon::famy_utils::createHttpResponse;
  using drogon::famy_utils::createJsonResponse;

  CoroMapper<Account> mapper(getDbClient());
  try
  {
    auto accountFound = co_await mapper.findOne(Criteria(
      Account::Cols::_email,
      CompareOperator::EQ,
      req->parameters().at(Account::Cols::_email)
    ));

    callback(createHttpResponse(std::move(createJsonResponse(
      std::make_pair("status", k200OK),
      std::make_pair("code", "OK"),
      std::make_pair(
        "message",
        createJsonResponse(std::make_pair("account", accountFound.toJson()))
      )
    ))));
  }
  catch(const DrogonDbException& e)
  {
    if(dynamic_cast<const UnexpectedRows*>(&e.base()))
    {
      callback(createHttpResponse(
        std::move(createJsonResponse(
          std::make_pair("status", k404NotFound),
          std::make_pair("code", "NOT_FOUND"),
          std::make_pair("message", "The ressource has not been found")
        )),
        k404NotFound
      ));
    }
    else
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
  }
}

Task<>
AccountCtrl::getAccountByLoginData(HttpRequestPtr req, AdviceCallback callback)
{
  // Using statements
  using Criteria = drogon::orm::Criteria;
  using CompareOperator = drogon::orm::CompareOperator;
  using drogon::famy_utils::createHttpResponse;
  using drogon::famy_utils::createJsonResponse;
  using drogon::famy_utils::getObject;

  try
  {
    const auto& jsonRequestPtr = getObject(req->jsonObject());

    CoroMapper<Account> mapper(getDbClient());

    auto accountFound = co_await mapper.findOne(
      Criteria(
        Account::Cols::_email,
        CompareOperator::EQ,
        (*jsonRequestPtr) [Account::Cols::_email].asString()
      ) &&
      Criteria(
        Account::Cols::_password,
        CompareOperator::EQ,
        (*jsonRequestPtr) [Account::Cols::_password].asString()
      )
    );

    callback(createHttpResponse(std::move(createJsonResponse(
      std::make_pair("status", k200OK),
      std::make_pair("code", "OK"),
      std::make_pair(
        "message",
        createJsonResponse(std::make_pair("account", accountFound.toJson()))
      )
    ))));
  }
  catch([[maybe_unused]] const DrogonDbException& e)
  {
    callback(createHttpResponse(
      std::move(createJsonResponse(
        std::make_pair("status", k404NotFound),
        std::make_pair("code", "NOT_FOUND"),
        std::make_pair("message", "Account has not been registered")
      )),
      k404NotFound
    ));
  }
  catch([[maybe_unused]] const std::runtime_error& e)
  {
    callback(createHttpResponse(
      std::move(createJsonResponse(
        std::make_pair("status", k404NotFound),
        std::make_pair("code", "NOT_FOUND"),
        std::make_pair("message", "No json object is found in the request")
      )),
      k404NotFound
    ));
  }
}

Task<>
AccountCtrl::updateOne(
  HttpRequestPtr req,
  AdviceCallback callback,
  Account::PrimaryKeyType&& id
)
{
  // using statement
  using drogon::famy_utils::createHttpResponse;
  using drogon::famy_utils::createJsonResponse;
  using drogon::famy_utils::getObject;

  try
  {
    Account accountToUpdate = Account(*(getObject(req->jsonObject())));

    CoroMapper<Account> mapper(getDbClient());

    auto count = co_await mapper.update(accountToUpdate);

    if(count)
    {
      auto accountUpdated = co_await mapper.findByPrimaryKey(id);

      callback(createHttpResponse(
        std::move(createJsonResponse(
          std::make_pair("status", k202Accepted),
          std::make_pair("code", "ACCEPTED"),
          std::make_pair(
            "message",
            createJsonResponse(
              std::make_pair("account", accountUpdated.toJson())
            )
          )
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
          std::make_pair("message", "No ressource has been updated")
        )),
        k404NotFound
      ));
    }
    else
    {
      callback(createHttpResponse(
        std::move(createJsonResponse(
          std::make_pair("status", k500InternalServerError),
          std::make_pair("code", "INTERNAL_SERVER_ERRROR"),
          std::make_pair(
            "message",
            "More than one ressource is updated : " + std::to_string(count)
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
        std::make_pair("status", k404NotFound),
        std::make_pair("code", "NOT_FOUND"),
        std::make_pair("message", "No json object is found in the request")
      )),
      k404NotFound
    ));
  }
}

// Generated by drogon
void
AccountCtrl::deleteOne(
  const HttpRequestPtr& req,
  std::function<void(const HttpResponsePtr&)>&& callback,
  Account::PrimaryKeyType&& id
)
{
  auto dbClientPtr = getDbClient();
  auto callbackPtr =
    std::make_shared<std::function<void(const HttpResponsePtr&)>>(
      std::move(callback)
    );
  drogon::orm::Mapper<Account> mapper(dbClientPtr);
  mapper.deleteByPrimaryKey(
    id,
    [callbackPtr](const size_t count)
    {
      if(count == 1)
      {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k204NoContent);
        (*callbackPtr)(resp);
      }
      else if(count == 0)
      {
        Json::Value ret;
        ret ["error"] = "No resources deleted";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k404NotFound);
        (*callbackPtr)(resp);
      }
      else
      {
        LOG_FATAL << "Delete more than one records: " << count;
        Json::Value ret;
        ret ["error"] = "Database error";
        auto resp = HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k500InternalServerError);
        (*callbackPtr)(resp);
      }
    },
    [callbackPtr](const DrogonDbException& e)
    {
      LOG_ERROR << e.base().what();
      Json::Value ret;
      ret ["error"] = "database error";
      auto resp = HttpResponse::newHttpJsonResponse(ret);
      resp->setStatusCode(k500InternalServerError);
      (*callbackPtr)(resp);
    }
  );
}

// Generated by drogon
void
AccountCtrl::get(
  const HttpRequestPtr& req,
  std::function<void(const HttpResponsePtr&)>&& callback
)
{
  using SortOrder = drogon::orm::SortOrder;

  auto dbClientPtr = getDbClient();
  drogon::orm::Mapper<Account> mapper(dbClientPtr);
  auto& parameters = req->parameters();
  auto iter = parameters.find("sort");
  if(iter != parameters.end())
  {
    auto sortFields = drogon::utils::splitString(iter->second, ",");
    for(auto& field : sortFields)
    {
      if(field.empty())
      {
        continue;
      }
      if(field [0] == '+')
      {
        field = field.substr(1);
        mapper.orderBy(field, SortOrder::ASC);
      }
      else if(field [0] == '-')
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
  if(iter != parameters.end())
  {
    try
    {
      auto offset = std::stoll(iter->second);
      mapper.offset(offset);
    }
    catch(...)
    {
      auto resp = HttpResponse::newHttpResponse();
      resp->setStatusCode(k400BadRequest);
      callback(resp);
      return;
    }
  }
  iter = parameters.find("limit");
  if(iter != parameters.end())
  {
    try
    {
      auto limit = std::stoll(iter->second);
      mapper.limit(limit);
    }
    catch(...)
    {
      auto resp = HttpResponse::newHttpResponse();
      resp->setStatusCode(k400BadRequest);
      callback(resp);
      return;
    }
  }
  auto callbackPtr =
    std::make_shared<std::function<void(const HttpResponsePtr&)>>(
      std::move(callback)
    );
  auto jsonPtr = req->jsonObject();
  if(jsonPtr && jsonPtr->isMember("filter"))
  {
    try
    {
      auto criteria = makeCriteria((*jsonPtr) ["filter"]);
      mapper.findBy(
        criteria,
        [req, callbackPtr, this](const std::vector<Account>& v)
        {
          Json::Value ret;
          ret.resize(0);
          for(auto& obj : v)
          {
            ret.append(makeJson(req, obj));
          }
          (*callbackPtr)(HttpResponse::newHttpJsonResponse(ret));
        },
        [callbackPtr](const DrogonDbException& e)
        {
          LOG_ERROR << e.base().what();
          Json::Value ret;
          ret ["error"] = "database error";
          auto resp = HttpResponse::newHttpJsonResponse(ret);
          resp->setStatusCode(k500InternalServerError);
          (*callbackPtr)(resp);
        }
      );
    }
    catch(const std::exception& e)
    {
      LOG_ERROR << e.what();
      Json::Value ret;
      ret ["error"] = e.what();
      auto resp = HttpResponse::newHttpJsonResponse(ret);
      resp->setStatusCode(k400BadRequest);
      (*callbackPtr)(resp);
      return;
    }
  }
  else
  {
    mapper.findAll(
      [req, callbackPtr, this](const std::vector<Account>& v)
      {
        Json::Value ret;
        ret.resize(0);
        for(auto& obj : v)
        {
          ret.append(makeJson(req, obj));
        }
        auto resp = HttpResponse::newHttpJsonResponse(std::move(ret));
        (*callbackPtr)(resp);
      },
      [callbackPtr](const DrogonDbException& e)
      {
        LOG_ERROR << e.base().what();
        Json::Value ret;
        ret ["error"] = "database error";
        auto resp = HttpResponse::newHttpJsonResponse(ret);

        resp->setStatusCode(k500InternalServerError);
        (*callbackPtr)(resp);
      }
    );
  }
}

Task<>
AccountCtrl::create(HttpRequestPtr req, AdviceCallback callback)
{
  // using statement
  using drogon::famy_utils::createHttpResponse;
  using drogon::famy_utils::createJsonResponse;
  using drogon::famy_utils::getObject;
  using drogon::orm::CompareOperator;
  using drogon::orm::Criteria;
  using drogon::orm::UnexpectedRows;

  try
  {
    const auto& jsonRequestPtr = getObject(req->jsonObject());

    CoroMapper<Account> mapper(getDbClient());

    const auto& emailFromRequest =
      (*jsonRequestPtr) [Account::Cols::_email].asString();

    auto accountsFound = co_await mapper.findBy(
      Criteria(Account::Cols::_email, CompareOperator::EQ, emailFromRequest)
    );
    // std::cout << accountsFound.front().toJson() << std::endl;
    if(accountsFound.size() > 1)
    {
      throw UnexpectedRows(
        "Found more than one account with the following email : " +
        emailFromRequest
      );
    }
    else if(accountsFound.empty())
    {
      auto accountInserted = co_await mapper.insert(Account(*jsonRequestPtr));
      callback(createHttpResponse(
        std::move(createJsonResponse(
          std::make_pair("status", k201Created),
          std::make_pair("code", "CREATED"),
          std::make_pair(
            "message",
            createJsonResponse(
              std::make_pair(Account::tableName, accountInserted.toJson())
            )
          )
        )),
        k201Created
      ));
    }
    else
    {
      auto [frontAccount, statusCodeDesc] = std::make_pair(
        accountsFound.front(),
        accountsFound.front().getValueOfIsVerified()
          ? std::make_pair("FORBIDDEN", k403Forbidden)
          : std::make_pair("ACCEPTED", k202Accepted)
      );
      callback(createHttpResponse(
        std::move(createJsonResponse(
          std::make_pair("status", statusCodeDesc.second),
          std::make_pair("code", statusCodeDesc.first),
          std::make_pair(
            "message",
            createJsonResponse(
              std::make_pair(Account::tableName, frontAccount.toJson())
            )
          )
        )),
        statusCodeDesc.second
      ));
    }
  }
  catch(const DrogonDbException& err)
  {
    callback(createHttpResponse(
      std::move(createJsonResponse(
        std::make_pair("status", k400BadRequest),
        std::make_pair("code", "BAD_REQUEST"),
        std::make_pair("message", err.base().what())
      )),
      k400BadRequest
    ));
  }
  catch([[maybe_unused]] const std::runtime_error& e)
  {
    callback(createHttpResponse(
      std::move(createJsonResponse(
        std::make_pair("status", k404NotFound),
        std::make_pair("code", "NOT_FOUND"),
        std::make_pair("message", "No json object is found in the request")
      )),
      k404NotFound
    ));
  }
  catch(...)
  {
    callback(createHttpResponse(
      std::move(createJsonResponse(
        std::make_pair("status", k500InternalServerError),
        std::make_pair("code", "INTERNAL_SERVER_ERROR"),
        std::make_pair("message", "database error")
      )),
      k500InternalServerError
    ));
  }
}

/*
void AccountCtrlBase::update(const HttpRequestPtr &req,
                             std::function<void(const HttpResponsePtr &)>
&&callback)
{

}*/

AccountCtrl::AccountCtrl() :
    RestfulController(
      {"id",
       "uuid",
       "role_id"
       "first_name",
       "last_name",
       "email",
       "password",
       "is_verified",
       "address"}
    )
{
  /**
   * The items in the vector are aliases of column names in the table.
   * if one item is set to an empty string, the related column is not sent
   * to clients.
   */
  enableMasquerading({
    "id",     // the alias for the id column.
    "uuid",   // the alias for the uuid column.
    "role_id",
    "first_name",    // the alias for the first_name column.
    "last_name",     // the alias for the last_name column.
    "email",         // the alias for the email column.
    "password",      // the alias for the password column.
    "is_verified",   // the alias for the is_verified column.
    "address"        // the alias for the address column.
  });
}
}   // namespace drogon::famy_account
