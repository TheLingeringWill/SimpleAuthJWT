#pragma once

#include <drogon/plugins/Plugin.h>

namespace drogon::famy_account::plugin
{
class JWTPlugin : public drogon::Plugin<JWTPlugin>
{
public:
  using TimeType = std::chrono::seconds;

  JWTPlugin() = default;
  /// This method must be called by drogon to initialize and start the plugin.
  /// It must be implemented by the user.
  void
  initAndStart(const Json::Value& config) override;

  /// This method must be called by drogon to shutdown the plugin.
  /// It must be implemented by the user.
  void
  shutdown() override;

  [[nodiscard]]
  std::string
  create(
    const std::string& subject,
    const TimeType& duration = TimeType(defaultDurationTime_)
  ) const;

  [[nodiscard]]
  bool
  verify(const std::string& token) const;

private:
  std::string issuer_;
  std::string audience_;
  std::string privateKey_;

  static constexpr const char* issuerStr_ {"issuer"};
  static constexpr const char* audienceStr_ {"audience"};
  static constexpr const char* privateKeyStr_ {"private_key"};
  static constexpr const char* idStr_ {"id"};

  static constexpr uint16_t defaultDurationTime_ {3600};
};

}   // namespace drogon::famy_account::plugin
