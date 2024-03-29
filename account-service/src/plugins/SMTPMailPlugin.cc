// NOLINTBEGIN
// 3rdparty includes
#include <drogon/HttpAppFramework.h>
#include <drogon/utils/Utilities.h>
#include <trantor/net/EventLoopThread.h>
#include <trantor/net/TcpClient.h>

// Project includes
#include "SMTPMailPlugin.h"

namespace drogon::famy_account::plugin
{
struct EMail
{
  enum states
  {
    Init,
    HandShake,
    Tls,
    Auth,
    User,
    Pass,
    Mail,
    Rcpt,
    Data,
    Body,
    Quit,
    Close
  };

  std::string m_from;
  std::string m_to;
  std::string m_subject;
  std::string m_content;
  std::string m_user;
  std::string m_passwd;
  states m_status;
  std::string m_uuid;
  bool m_isHTML {false};
  std::shared_ptr<trantor::TcpClient> m_socket;

  EMail(
    std::string from,
    std::string to,
    std::string subject,
    std::string content,
    std::string user,
    std::string passwd,
    bool isHTML,
    std::shared_ptr<trantor::TcpClient> socket
  ) :
      m_from(std::move(from)),
      m_to(std::move(to)), m_subject(std::move(subject)),
      m_content(std::move(content)), m_user(std::move(user)),
      m_passwd(std::move(passwd)), m_socket(std::move(socket)),
      m_isHTML(isHTML), m_uuid(drogon::utils::getUuid())
  {
    m_status = Init;
  }

  ~EMail() = default;

  static std::unordered_map<std::string, std::shared_ptr<EMail>>
    m_emails;   // Container for processing emails
};

std::unordered_map<std::string, std::shared_ptr<EMail>> EMail::m_emails;

void
SMTPMailPlugin::initAndStart(const Json::Value& config)
{
  serverHost_ = config [serverHostStr_].asString();
  port_ = config [portStr_].asUInt();
  sender_ = config [senderStr_].asString();
  login_ = config [loginStr_].asString();
  password_ = config [passwordStr_].asString();
}

void
SMTPMailPlugin::shutdown()
{
}

void
messagesHandle(
  const trantor::TcpConnectionPtr& connPtr,
  trantor::MsgBuffer* msg,
  const std::shared_ptr<EMail>& email,
  const std::function<void(const std::string& msg)>& cb
)
{
  std::string receivedMsg;
  while(msg->readableBytes() > 0)
  {
    std::string buf(msg->peek(), msg->readableBytes());
    receivedMsg.append(buf);
    //        LOG_INFO << buf;
    msg->retrieveAll();
  }
  LOG_TRACE << "receive: " << receivedMsg;
  std::string responseCode(receivedMsg.begin(), receivedMsg.begin() + 3);
  //    std::string responseMsg(receivedMsg.begin() + 4, receivedMsg.end());

  if(email->m_status == EMail::Init && responseCode == "220")
  {
    std::string outMsg;
    trantor::MsgBuffer out;

    outMsg.append("EHLO smtpclient.qw");
    outMsg.append("\r\n");

    out.append(outMsg.data(), outMsg.size());

    connPtr->send(std::move(out));

    email->m_status = EMail::HandShake;
  }
  else if(email->m_status == EMail::HandShake && responseCode == "220")
  {
    std::string outMsg;
    trantor::MsgBuffer out;

    outMsg.append("EHLO smtpclient.qw");
    outMsg.append("\r\n");

    out.append(outMsg.data(), outMsg.size());

    auto policy = trantor::TLSPolicy::defaultClientPolicy();
    policy->setValidate(false);
    connPtr->startEncryption(
      policy,
      false,
      [out](const trantor::TcpConnectionPtr& connPtr)
      {
        // LOG_TRACE << "SSL established";
        connPtr->send(out);
      }
    );

    email->m_status = EMail::Auth;
  }
  else if(email->m_status == EMail::HandShake && responseCode == "250")
  {
    std::string outMsg;
    trantor::MsgBuffer out;

    outMsg.append("STARTTLS");
    outMsg.append("\r\n");

    out.append(outMsg.data(), outMsg.size());

    connPtr->send(std::move(out));

    email->m_status = EMail::HandShake;
  }
  else if(email->m_status == EMail::Auth && responseCode == "250")
  {
    trantor::MsgBuffer out;
    std::string outMsg;

    outMsg.append("AUTH LOGIN");
    outMsg.append("\r\n");

    out.append(outMsg.data(), outMsg.size());

    connPtr->send(std::move(out));

    email->m_status = EMail::User;
  }
  else if(email->m_status == EMail::User && responseCode == "334")
  {
    trantor::MsgBuffer out;
    std::string outMsg;

    std::string secret(email->m_user);

    // outMsg.append(base64_encode(reinterpret_cast<const unsigned
    // char*>(secret.c_str()), secret.length()));
    outMsg.append(drogon::utils::base64Encode(
      reinterpret_cast<const unsigned char*>(secret.c_str()),
      static_cast<unsigned>(secret.length())
    ));

    outMsg.append("\r\n");

    out.append(outMsg.data(), outMsg.size());

    connPtr->send(std::move(out));

    email->m_status = EMail::Pass;
  }
  else if(email->m_status == EMail::Pass && responseCode == "334")
  {
    trantor::MsgBuffer out;
    std::string outMsg;

    std::string secret(email->m_passwd);

    outMsg.append(drogon::utils::base64Encode(
      reinterpret_cast<const unsigned char*>(secret.c_str()),
      static_cast<unsigned>(secret.length())
    ));
    outMsg.append("\r\n");

    out.append(outMsg.data(), outMsg.size());

    connPtr->send(std::move(out));

    email->m_status = EMail::Mail;
  }
  else if(email->m_status == EMail::Mail && responseCode == "235")
  {
    trantor::MsgBuffer out;
    std::string outMsg;

    outMsg.append("MAIL FROM:<");
    outMsg.append(email->m_from);
    outMsg.append(">\r\n");

    out.append(outMsg.data(), outMsg.size());

    connPtr->send(std::move(out));

    email->m_status = EMail::Rcpt;
  }
  else if(email->m_status == EMail::Rcpt && responseCode == "250")
  {
    trantor::MsgBuffer out;
    std::string outMsg;

    outMsg.append("RCPT TO:<");
    outMsg.append(email->m_to);
    outMsg.append(">\r\n");

    out.append(outMsg.data(), outMsg.size());

    connPtr->send(std::move(out));

    email->m_status = EMail::Data;
  }
  else if(email->m_status == EMail::Data && responseCode == "250")
  {
    trantor::MsgBuffer out;
    std::string outMsg;

    outMsg.append("DATA");
    outMsg.append("\r\n");

    out.append(outMsg.data(), outMsg.size());

    connPtr->send(std::move(out));

    email->m_status = EMail::Body;
  }
  else if(email->m_status == EMail::Body && responseCode == "354")
  {
    trantor::MsgBuffer out;
    std::string outMsg;

    outMsg.append("To: " + email->m_to + "\r\n");
    outMsg.append("From: " + email->m_from + "\r\n");
    if(email->m_isHTML)
    {
      outMsg.append("Content-Type: text/html;\r\n");
    }
    outMsg.append("Subject: " + email->m_subject + "\r\n\r\n");

    outMsg.append(email->m_content);
    outMsg.append("\r\n.\r\n");

    out.append(outMsg.data(), outMsg.size());

    connPtr->send(std::move(out));

    email->m_status = EMail::Quit;
  }
  else if(email->m_status == EMail::Quit && responseCode == "250")
  {
    trantor::MsgBuffer out;
    std::string outMsg;

    outMsg.append("QUIT");
    outMsg.append("\r\n");

    out.append(outMsg.data(), outMsg.size());

    connPtr->send(std::move(out));

    email->m_status = EMail::Close;
  }
  else if(email->m_status == EMail::Close)
  {
    /*Callback here for succeed delivery is probable*/
    cb("EMail sent. ID : " + email->m_uuid);
    return;
  }
  else
  {
    email->m_status = EMail::Close;
    /*Callback here for notification is probable*/
    cb(receivedMsg);
  }
}

std::string
SMTPMailPlugin::sendEmail(
  const std::string& to,
  const std::string& subject,
  const std::string& content,
  bool isHTML,
  const std::function<void(const std::string&)>& cb
)
{
  static const std::string& mailServer = serverHost_;
  const unsigned port = port_;
  static const std::string& from = sender_;
  static const std::string& user = login_;
  static const std::string& passwd = password_;

  if(to.empty() || subject.empty())
  {
    LOG_WARN << "Invalid input(s) - "
             << "\nServer : " << mailServer << "\nPort : " << port
             << "\nfrom : " << from << "\nto : " << to
             << "\nsubject : " << subject << "\nuser : " << user
             << "\npasswd : " << passwd;
    return {};
  }

  static auto hasLineBreak = [](const std::string& msg)
  {
    if(std::string::npos != msg.find_first_of("\n") || std::string::npos != msg.find_first_of("\r"))
    {
      return true;
    }
    return false;
  };

  if(hasLineBreak(from))
  {
    LOG_WARN << "Invalid \"FROM\" data : " << from;
    return {};
  }
  if(hasLineBreak(to))
  {
    LOG_WARN << "Invalid \"TO\" data : " << to;
    return {};
  }
  if(hasLineBreak(subject))
  {
    LOG_WARN << "Invalid \"SUBJECT\" data : " << subject.data();
    return {};
  }

  LOG_TRACE << "New TcpClient : " << mailServer << ":" << port;

  // Create the email
  auto email = std::make_shared<
    EMail>(from, to, subject, content, user, passwd, isHTML, nullptr);

  auto resolver = app().getResolver();
  resolver->resolve(
    mailServer,
    [email, port, cb](const trantor::InetAddress& addr)
    {
      constexpr size_t defaultLoopIdA = 10;
      constexpr size_t defaultLoopIdB = 9;
      auto loopA = app().getIOLoop(defaultLoopIdA);
      auto loopB = app().getIOLoop(defaultLoopIdB);

      if(loopA == loopB)
      {
        LOG_WARN << "Please provide at least 2 threads for this plugin";
        return;
      }

      auto loop = loopA->isInLoopThread() ? loopB : loopA;

      assert(loop);   // Should never be null
      trantor::InetAddress addr_(addr.toIp(), port, false);
      auto tcpSocket =
        std::make_shared<trantor::TcpClient>(loop, addr_, "SMTPMail");

      email->m_socket = tcpSocket;

      std::weak_ptr<EMail> email_wptr = email;

      EMail::m_emails.emplace(
        email->m_uuid,
        email
      );   // Assuming there is no uuid collision
      tcpSocket->setConnectionCallback(
        [email_wptr](const trantor::TcpConnectionPtr& connPtr)
        {
          auto email_ptr = email_wptr.lock();
          if(! email_ptr)
          {
            LOG_WARN << "EMail pointer gone";
            return;
          }
          if(connPtr->connected())
          {
            // send request;
            LOG_TRACE << "Connection established!";
          }
          else
          {
            LOG_TRACE << "Connection disconnect";
            EMail::m_emails.erase(email_ptr->m_uuid
            );   // Remove the email in list
            // thisPtr->onError(std::string("ReqResult::NetworkFailure"));
          }
        }
      );
      tcpSocket->setConnectionErrorCallback(
        [email_wptr]()
        {
          auto email_ptr = email_wptr.lock();
          if(! email_ptr)
          {
            LOG_ERROR << "EMail pointer gone";
            return;
          }
          // can't connect to server
          LOG_ERROR << "Bad Server address";
          EMail::m_emails.erase(email_ptr->m_uuid
          );   // Remove the email in list
          // thisPtr->onError(std::string("ReqResult::BadServerAddress"));
        }
      );
      auto cb_(
        cb ? cb
           : [](const std::string& msg)
          { LOG_INFO << "Default email callback : " << msg; }
      );
      tcpSocket->setMessageCallback(
        [email_wptr,
         cb_](const trantor::TcpConnectionPtr& connPtr, trantor::MsgBuffer* msg)
        {
          auto email_ptr = email_wptr.lock();
          if(! email_ptr)
          {
            LOG_ERROR << "EMail pointer gone";
            return;
          }
          // email->m_socket->disconnect();
          messagesHandle(connPtr, msg, email_ptr, cb_);
        }
      );
      tcpSocket->connect();   // Start trying to send the email
    }
  );
  return email->m_uuid;
}

}   // namespace drogon::famy_account::plugin

// NOLINTEND
