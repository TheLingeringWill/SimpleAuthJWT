// NOLINTBEGIN
#pragma once

// 3rdparty includes
#include <drogon/plugins/Plugin.h>

namespace drogon::famy_account::plugin
{

class SMTPMailPlugin : public drogon::Plugin<SMTPMailPlugin>
{
public:
  SMTPMailPlugin() = default;
  /// This method must be called by drogon to initialize and start the plugin.
  /// It must be implemented by the user.
  void
  initAndStart(const Json::Value& config) override;

  /// This method must be called by drogon to shutdown the plugin.
  /// It must be implemented by the user.
  void
  shutdown() override;

  /** Send an email
   * return : An ID of the email.
   */
  std::string
  sendEmail(
    const std::string& to,        // Reciever       E.g. drogon@yahoo.com
    const std::string& subject,   // The email title/subject
    const std::string& content,   // The email content.
    bool isHTML,                  // content type
    const std::function<void(const std::string&)>& cb = {}
  );

private:
  inline static std::string serverHost_;
  inline static unsigned port_;
  inline static std::string sender_;
  inline static std::string login_;
  inline static std::string password_;

  static constexpr const char* serverHostStr_ {"serverHost"};
  static constexpr const char* portStr_ {"port"};
  static constexpr const char* senderStr_ {"sender"};
  static constexpr const char* loginStr_ {"login"};
  static constexpr const char* passwordStr_ {"password"};
};

}   // namespace drogon::famy_account::plugin

// NOLINTEND
