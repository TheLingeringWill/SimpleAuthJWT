/**
 *
 *  v1_JWTPlugin.cc
 *
 */

#include "JWTPlugin.h"

#include <jwt-cpp/jwt.h>

namespace drogon::famy_account::plugin
{

void
JWTPlugin::initAndStart(const Json::Value& config)
{
  issuer_ = config [issuerStr_].asString();
  audience_ = config [audienceStr_].asString();
  privateKey_ = config [privateKeyStr_].asString();
}

void
JWTPlugin::shutdown()
{
  /// Shutdown the plugin
}

std::string
JWTPlugin::create(const std::string& subject, const TimeType& duration) const
{
  auto time = std::chrono::system_clock::now();

  return jwt::create()
    .set_issuer(issuer_)
    .set_audience(audience_)
    .set_subject(subject)
    .set_issued_at(std::chrono::system_clock::now())
    .set_expires_at(std::chrono::system_clock::now() + duration)
    .sign(jwt::algorithm::hs256(privateKey_));
}

bool
JWTPlugin::verify(const std::string& token) const
{
  bool ret = false;

  try
  {
    auto decodedToken = jwt::decode(token);
    jwt::verify()
      .allow_algorithm(jwt::algorithm::hs256(privateKey_))
      .with_issuer(issuer_)
      .with_audience(audience_)
      .verify(decodedToken);

    ret = true;
  }
  catch(const jwt::error::token_verification_exception& e)
  {
    LOG_DEBUG << e.what();
  }
  catch([[maybe_unused]] const std::runtime_error& e)
  {
    LOG_DEBUG << "MERDE";
  }
  catch(...)
  {
    LOG_DEBUG << "CUL";
  }

  return ret;
}

}   // namespace drogon::famy_account::plugin
