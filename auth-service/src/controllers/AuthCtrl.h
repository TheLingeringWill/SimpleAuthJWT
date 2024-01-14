#pragma once

// 3rdparty includes
#include <drogon/HttpController.h>

// Model includes
#include "models/Account.h"
#include "models/Auth.h"

// Plugin includes
#include "plugins/JWTPlugin.h"
#include "plugins/SMTPMailPlugin.h"

// Project includes
#include "ServiceCtrl.h"

namespace drogon::famy_auth
{

/**
 * Authentification http controller class, the class manager for user
 * authentification
 */
class AuthCtrl : public drogon::famy_utils::ServiceCtrl<AuthCtrl>
{
  using Auth = drogon_model::famy_auth::Auth;

  using Account = drogon_model::famy_account::Account;

  using JWTPlugin = plugin::JWTPlugin;

  using JWTPluginPtr = JWTPlugin*;

  using SMTPMailPlugin = plugin::SMTPMailPlugin;

  using SMTPMailPluginPtr = SMTPMailPlugin*;

public:
  METHOD_LIST_BEGIN

  ADD_METHOD_TO(
    AuthCtrl::signUp,
    "/v1/auth/sign-up",
    Post,
    Options,
    "drogon::famy_auth::filter::SignUpFilter"
  );

  ADD_METHOD_TO(
    AuthCtrl::confirmSignUp,
    "/v1/auth/sign-up/confirm/{1}",
    Get,
    Options,
    "drogon::famy_auth::filter::JWTFilter"
  );

  ADD_METHOD_TO(
    AuthCtrl::signIn,
    "/v1/auth/sign-in",
    Put,
    Options,
    "drogon::famy_auth::filter::SignInFilter"
  );

  ADD_METHOD_TO(
    AuthCtrl::confirmSignIn,
    "/v1/auth/sign-in/confirm",
    Put,
    Options,
    "drogon::famy_auth::filter::ConfirmOtpFilter"
  );

  METHOD_LIST_END

  /**
   *
   * Method handler for sign-up account, non blocked function
   *
   * @detail
   * Verify if account data on account service to see if user has been
   * registered. If it's new user, send an email with JWT token to proceed
   * authentification.
   *
   * @param[out] req The http request
   * @param[out] callback The Handler for the request and response generator
   *
   */
  Task<>
  signUp(HttpRequestPtr req, AdviceCallback callback);

  /**
   *
   * Method handler for the confirmation of sign-up account, non blocked
   * function
   *
   * @detail
   * After receiving the link confirmation email from signUp handler, user
   * should be verified. Account service is interroged to update the line
   * is_verified to be true for user account data.
   *
   * @param[out] req The http request
   * @param[out] callback The Handler for the request and response generator
   *
   */
  Task<>
  confirmSignUp(
    HttpRequestPtr req,
    AdviceCallback callback,
    std::string&& token
  );

  /**
   *
   * Method handler for sign-in account, non blocked function
   *
   * @detail
   * Use Account service to see if the user data has been registered and send
   * otp in email.
   *
   * @param[out] req The http request
   * @param[out] callback The Handler for the request and response generator
   *
   */
  Task<>
  signIn(HttpRequestPtr req, AdviceCallback callback);

  /**
   *
   * Method handler for the confirmation of sign-in account, non blocked
   * function
   *
   * @detail
   * Confirm otp password sended by email from user and get token access to famy
   * The refresh token is also generated but registered on database
   *
   * @param[out] req The http request
   * @param[out] callback The Handler for the request and response generator
   *
   */
  Task<>
  confirmSignIn(HttpRequestPtr req, AdviceCallback callback);

  Task<>
  getCredentialsFromGoogle(
    HttpRequestPtr req,
    AdviceCallback callback,
    std::string&& code
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

  JWTPluginPtr
  getJWTPlugin() const
  {
    return drogon::famy_utils::getPlugin<JWTPlugin>();
  }

  SMTPMailPluginPtr
  getSMTPMailPlugin() const
  {
    return drogon::famy_utils::getPlugin<SMTPMailPlugin>();
  }

  static constexpr const char* dbClientName_ {"default"};

  HttpClientPtr proxyAccountHandler_ {drogon::HttpClient::newHttpClient(
    drogon::famy_utils::loadEnv("ACCOUNT_HOST_NAME_URL", "http://localhost:81")
  )};
};

}   // namespace drogon::famy_auth
