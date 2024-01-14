#pragma once

// Standard library includes
#include <exception>

// 3rdparty includes
#include <drogon/HttpController.h>
#include <drogon/orm/RestfulController.h>

// Model includes
#include "models/Account.h"

// Project includes
#include "ServiceCtrl.h"

namespace drogon::famy_account
{
class AccountCtrl :
    public drogon::famy_utils::ServiceCtrl<AccountCtrl>,
    public RestfulController
{
  using Account = drogon_model::famy_account::Account;

public:
  METHOD_LIST_BEGIN

  ADD_METHOD_TO(AccountCtrl::getOne, "/v1/account/verify?", Post, Options);

  ADD_METHOD_TO(
    AccountCtrl::getAccountByLoginData,
    "/v1/account/sign-in",
    Get,
    Options,
    "drogon::famy_account::filter::SignInFilter"
  );

  ADD_METHOD_TO(AccountCtrl::updateOne, "/v1/account/{1}", Put, Options);

  ADD_METHOD_TO(AccountCtrl::deleteOne, "/v1/account/{1}", Delete, Options);

  ADD_METHOD_TO(AccountCtrl::get, "/v1/account", Get, Options);

  ADD_METHOD_TO(
    AccountCtrl::create,
    "/v1/account",
    Post,
    Options,
    "drogon::famy_account::filter::SignUpFilter"
  );

  METHOD_LIST_END

  AccountCtrl();

  Task<>
  getOne(HttpRequestPtr req, AdviceCallback callback);

  Task<>
  getAccountByLoginData(HttpRequestPtr req, AdviceCallback callback);

  Task<>
  updateOne(
    HttpRequestPtr req,
    AdviceCallback callback,
    Account::PrimaryKeyType&& id
  );

  Task<>
  create(HttpRequestPtr req, AdviceCallback callback);

  void
  deleteOne(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback,
    Account::PrimaryKeyType&& id
  );

  void
  get(
    const HttpRequestPtr& req,
    std::function<void(const HttpResponsePtr&)>&& callback
  );

private:
  DbClientPtr
  getDbClient() override
  {
    DbClientPtr dbClient = getDbClientThreadStorage();

    if(! dbClient)
    {
      dbClient = drogon::app().getFastDbClient(dbClientName_);
    }

    return dbClient;
  }

  static constexpr const char* dbClientName_ {"default"};
};

}   // namespace drogon::famy_account
