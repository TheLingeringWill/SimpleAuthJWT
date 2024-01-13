
// Filter includes
#include "JWTFilter.h"

namespace drogon::famy_account::filter
{
void
JWTFilter::doFilter(
  const HttpRequestPtr& req,
  FilterCallback&& fcb,
  FilterChainCallback&& fccb
)
{
  // using statements
  using drogon::famy_utils::createHttpResponse;
  using drogon::famy_utils::createJsonResponse;

  if(const auto& token = req->getHeader(authorizationStr_);
     token.length() < sizeBearer_)
  {
    fcb(createHttpResponse(
      std::move(createJsonResponse(
        std::make_pair("code", "UNAUTHORIZED"),
        std::make_pair("message", "Authorization bearer token")
      )),
      k401Unauthorized
    ));
  }
  else if(const auto& tokenExtracted = token.substr(sizeBearer_);
          ! getJWTPlugin()->verify(tokenExtracted))
  {
    fcb(createHttpResponse(
      std::move(createJsonResponse(
        std::make_pair("code", "NOT_ACCEPTABLE"),
        std::make_pair("message", "Token has not been accepted")
      )),
      k406NotAcceptable
    ));
  }
  else
  {
    req->getAttributes()->insert("token", tokenExtracted);
    fccb();
  }
}

}   // namespace drogon::famy_account::filter
