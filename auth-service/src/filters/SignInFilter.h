#pragma once

// 3rdparty includes
#include <drogon/HttpFilter.h>

// Plugin includes
#include "plugins/JWTPlugin.h"

// Model includes
#include "models/Account.h"

namespace drogon::famy_auth::filter
{
class SignInFilter : public HttpFilter<SignInFilter>
{
  using Account = drogon_model::famy_account::Account;

public:
  void
  doFilter(
    const HttpRequestPtr& req,
    FilterCallback&& fcb,
    FilterChainCallback&& fccb
  ) override;

  static constexpr size_t mandatoryLineNumber {2};
};

}   // namespace drogon::famy_auth::filter
