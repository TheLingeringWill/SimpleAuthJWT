
#pragma once

// 3rdparty includes
#include <drogon/HttpFilter.h>

// Plugin includes
#include "plugins/JWTPlugin.h"

// Model includes
#include "models/Account.h"
#include "models/Auth.h"

namespace drogon::famy_auth::filter
{
class ConfirmOtpFilter : public HttpFilter<ConfirmOtpFilter>
{
  using Account = drogon_model::famy_account::Account;
  using Auth = drogon_model::famy_auth::Auth;

public:
  void
  doFilter(
    const HttpRequestPtr& req,
    FilterCallback&& fcb,
    FilterChainCallback&& fccb
  ) override;

  static constexpr size_t mandatoryLineNumber {3};
};

}   // namespace drogon::famy_auth::filter
