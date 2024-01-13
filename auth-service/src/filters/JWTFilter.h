#pragma once

// 3rdparty includes
#include <drogon/HttpFilter.h>

// Plugin includes
#include "plugins/JWTPlugin.h"

// Project includes
#include "utils.h"

namespace drogon::famy_auth::filter
{
class JWTFilter : public HttpFilter<JWTFilter>
{
  using JWTPlugin = drogon::famy_auth::plugin::JWTPlugin;
  using JWTPluginPtr = JWTPlugin*;

public:
  void
  doFilter(
    const HttpRequestPtr& req,
    FilterCallback&& fcb,
    FilterChainCallback&& fccb
  ) override;

private:
  static JWTPluginPtr
  getJWTPlugin()
  {
    return drogon::famy_utils::getPlugin<JWTPlugin>();
  }

  static constexpr const char* authorizationStr_ {"Authorization"};
  static constexpr uint16_t sizeBearer_ {7};
};

}   // namespace drogon::famy_auth::filter
