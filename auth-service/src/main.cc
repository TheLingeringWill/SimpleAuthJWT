#include "utils.h"

#include <drogon/drogon.h>

using namespace drogon;
using namespace famy_utils;

int
main()
{
  app()
    .registerPostHandlingAdvice(
      [](const HttpRequestPtr& req, const HttpResponsePtr& resp)
      { resp->addHeader("Access-Control-Allow-Origin", "*"); }
    )
    .setThreadNum(2)
    .addListener(
      loadEnv("AUTH_SERVICE_HOST", "127.0.0.1"),
      std::stoul(loadEnv("AUTH_SERVICE_PORT", "80"))
    )
    .createDbClient(
      loadEnv("AUTH_DB_TYPE", "postgres"),
      loadEnv("AUTH_DB_HOST", "127.0.0.1"),
      std::stoul(loadEnv("AUTH_DB_PORT", "5432")),
      loadEnv("AUTH_DB_NAME", "famy_auth"),
      loadEnv("AUTH_DB_USER", "postgres"),
      loadEnv("AUTH_DB_PASSWORD", "root"),
      1,
      "",
      loadEnv("AUTH_DB_CLIENT_NAME", "default"),
      true,
      loadEnv("AUTH_DB_ENCODING"),
      -1.0,
      true
    );

  app().addPlugin(
    "drogon::famy_auth::plugin::JWTPlugin",
    {},
    createJsonResponse(
      std::make_pair("issuer", loadEnv("AUTH_TOKEN_ISSUER", "api.famy")),
      std::make_pair("audience", loadEnv("AUTH_TOKEN_AUDIENCE", "famy.com")),
      std::make_pair("privateKey", loadEnv("AUTH_TOKEN_PRIVATE_KEY", "blablaa"))
    )
  );

  app().addPlugin(
    "drogon::famy_auth::plugin::SMTPMailPlugin",
    {},
    createJsonResponse(
      std::make_pair("serverHost", loadEnv("AUTH_SMTP_HOST", "smtp.gmail.com")),
      std::make_pair("port", std::stoul(loadEnv("AUTH_SMTP_PORT", "587"))),
      std::make_pair(
        "sender",
        loadEnv("AUTH_SMTP_SENDER", "jonathan.elbaz92@gmail.com")
      ),
      std::make_pair(
        "login",
        loadEnv("AUTH_SMTP_LOGIN", "jonathan.elbaz92@gmail.com")
      ),
      std::make_pair(
        "password",
        loadEnv("AUTH_SMTP_PASSWORD", "gsissutqnxiolbhq")
      )
    )
  );

  app().run();
}
