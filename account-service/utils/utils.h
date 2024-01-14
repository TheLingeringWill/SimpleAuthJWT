#pragma once

// Thirdparty includes
#include <drogon/HttpAppFramework.h>
#include <drogon/HttpController.h>

namespace drogon::famy_utils
{
inline std::string
loadEnv(const char* path, const char* def = "")
{
  if(auto env_p {std::getenv(path)})
  {
    return std::string(env_p);
  }
  else
  {
    return std::string(def);
  }
}

template<typename T>
requires(std::is_base_of_v<drogon::Plugin<std::decay_t<T>>, std::decay_t<T>>)
inline T*
getPlugin()
{
  return drogon::app().getPlugin<T>();
}

template<typename... T>
inline Json::Value
createJsonResponse(T&&... args)
{
  Json::Value jsonResponse;
  ([&jsonResponse](const auto& value)
   { jsonResponse [value.first] = value.second; }(args),
   ...);
  return jsonResponse;
}

template<typename T>
inline const std::shared_ptr<T>&
getObject(const std::shared_ptr<T>& object)
{
  return object ? object : throw std::runtime_error("No object found");
}

inline drogon::HttpResponsePtr
createHttpResponse(Json::Value&& jsonResponse)
{
  return drogon::HttpResponse::newHttpJsonResponse(std::move(jsonResponse));
}

inline drogon::HttpResponsePtr
createHttpResponse(Json::Value&& jsonResponse, drogon::HttpStatusCode status)
{
  auto httpResponse = createHttpResponse(std::move(jsonResponse));
  httpResponse->setStatusCode(status);
  return httpResponse;
}

inline drogon::HttpRequestPtr
createHttpRequest(Json::Value&& jsonResponse, const std::string& path)
{
  auto httpRequestPtr =
    drogon::HttpRequest::newHttpJsonRequest(std::move(jsonResponse));
  httpRequestPtr->setPath(path);
  return httpRequestPtr;
}

inline drogon::HttpRequestPtr
createHttpRequest(
  Json::Value&& jsonResponse,
  const std::string& path,
  drogon::HttpMethod method
)
{
  auto httpRequestPtr = createHttpRequest(std::move(jsonResponse), path);
  httpRequestPtr->setMethod(method);
  return httpRequestPtr;
}
}   // namespace drogon::famy_utils
