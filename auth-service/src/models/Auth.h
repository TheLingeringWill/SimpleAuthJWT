/**
 *
 *  Auth.h
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */
// NOLINTBEGIN
#pragma once
#include <drogon/orm/Field.h>
#include <drogon/orm/Mapper.h>
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/SqlBinder.h>
#ifdef __cpp_impl_coroutine
  #include <drogon/orm/CoroMapper.h>
#endif
#include <iostream>
#include <json/json.h>
#include <memory>
#include <stdint.h>
#include <string>
#include <trantor/utils/Date.h>
#include <trantor/utils/Logger.h>
#include <tuple>
#include <vector>

namespace drogon
{
namespace orm
{
class DbClient;
using DbClientPtr = std::shared_ptr<DbClient>;
}   // namespace orm
}   // namespace drogon

namespace drogon_model
{
namespace famy_auth
{

class Auth
{
public:
  struct Cols
  {
    static const std::string _id;
    static const std::string _verify_token;
    static const std::string _refresh_token;
    static const std::string _otp;
  };

  const static int primaryKeyNumber;
  const static std::string tableName;
  const static bool hasPrimaryKey;
  const static std::string primaryKeyName;
  using PrimaryKeyType = int64_t;
  const PrimaryKeyType&
  getPrimaryKey() const;

  /**
   * @brief constructor
   * @param r One row of records in the SQL query result.
   * @param indexOffset Set the offset to -1 to access all columns by column
   * names, otherwise access all columns by offsets.
   * @note If the SQL is not a style of 'select * from table_name ...' (select
   * all columns by an asterisk), please set the offset to -1.
   */
  explicit Auth(
    const drogon::orm::Row& r,
    const ssize_t indexOffset = 0
  ) noexcept;

  /**
   * @brief constructor
   * @param pJson The json object to construct a new instance.
   */
  explicit Auth(const Json::Value& pJson) noexcept(false);

  /**
   * @brief constructor
   * @param pJson The json object to construct a new instance.
   * @param pMasqueradingVector The aliases of table columns.
   */
  Auth(
    const Json::Value& pJson,
    const std::vector<std::string>& pMasqueradingVector
  ) noexcept(false);

  Auth() = default;

  void
  updateByJson(const Json::Value& pJson) noexcept(false);
  void
  updateByMasqueradedJson(
    const Json::Value& pJson,
    const std::vector<std::string>& pMasqueradingVector
  ) noexcept(false);
  static bool
  validateJsonForCreation(const Json::Value& pJson, std::string& err);
  static bool
  validateMasqueradedJsonForCreation(
    const Json::Value&,
    const std::vector<std::string>& pMasqueradingVector,
    std::string& err
  );
  static bool
  validateJsonForUpdate(const Json::Value& pJson, std::string& err);
  static bool
  validateMasqueradedJsonForUpdate(
    const Json::Value&,
    const std::vector<std::string>& pMasqueradingVector,
    std::string& err
  );
  static bool
  validJsonOfField(
    size_t index,
    const std::string& fieldName,
    const Json::Value& pJson,
    std::string& err,
    bool isForCreation
  );

  /**  For column id  */
  /// Get the value of the column id, returns the default value if the column is
  /// null
  const int64_t&
  getValueOfId() const noexcept;
  /// Return a shared_ptr object pointing to the column const value, or an empty
  /// shared_ptr object if the column is null
  const std::shared_ptr<int64_t>&
  getId() const noexcept;
  /// Set the value of the column id
  void
  setId(const int64_t& pId) noexcept;

  /**  For column verify_token  */
  /// Get the value of the column verify_token, returns the default value if the
  /// column is null
  const std::string&
  getValueOfVerifyToken() const noexcept;
  /// Return a shared_ptr object pointing to the column const value, or an empty
  /// shared_ptr object if the column is null
  const std::shared_ptr<std::string>&
  getVerifyToken() const noexcept;
  /// Set the value of the column verify_token
  void
  setVerifyToken(const std::string& pVerifyToken) noexcept;
  void
  setVerifyToken(std::string&& pVerifyToken) noexcept;
  void
  setVerifyTokenToNull() noexcept;

  /**  For column refresh_token  */
  /// Get the value of the column refresh_token, returns the default value if
  /// the column is null
  const std::string&
  getValueOfRefreshToken() const noexcept;
  /// Return a shared_ptr object pointing to the column const value, or an empty
  /// shared_ptr object if the column is null
  const std::shared_ptr<std::string>&
  getRefreshToken() const noexcept;
  /// Set the value of the column refresh_token
  void
  setRefreshToken(const std::string& pRefreshToken) noexcept;
  void
  setRefreshToken(std::string&& pRefreshToken) noexcept;
  void
  setRefreshTokenToNull() noexcept;

  /**  For column otp  */
  /// Get the value of the column otp, returns the default value if the column
  /// is null
  const std::string&
  getValueOfOtp() const noexcept;
  /// Return a shared_ptr object pointing to the column const value, or an empty
  /// shared_ptr object if the column is null
  const std::shared_ptr<std::string>&
  getOtp() const noexcept;
  /// Set the value of the column otp
  void
  setOtp(const std::string& pOtp) noexcept;
  void
  setOtp(std::string&& pOtp) noexcept;
  void
  setOtpToNull() noexcept;

  static size_t
  getColumnNumber() noexcept
  {
    return 4;
  }

  static const std::string&
  getColumnName(size_t index) noexcept(false);

  Json::Value
  toJson() const;
  Json::Value
  toMasqueradedJson(const std::vector<std::string>& pMasqueradingVector) const;
  /// Relationship interfaces

private:
  friend drogon::orm::Mapper<Auth>;
#ifdef __cpp_impl_coroutine
  friend drogon::orm::CoroMapper<Auth>;
#endif
  static const std::vector<std::string>&
  insertColumns() noexcept;
  void
  outputArgs(drogon::orm::internal::SqlBinder& binder) const;
  const std::vector<std::string>
  updateColumns() const;
  void
  updateArgs(drogon::orm::internal::SqlBinder& binder) const;
  /// For mysql or sqlite3
  void
  updateId(const uint64_t id);
  std::shared_ptr<int64_t> id_;
  std::shared_ptr<std::string> verifyToken_;
  std::shared_ptr<std::string> refreshToken_;
  std::shared_ptr<std::string> otp_;

  struct MetaData
  {
    const std::string colName_;
    const std::string colType_;
    const std::string colDatabaseType_;
    const ssize_t colLength_;
    const bool isAutoVal_;
    const bool isPrimaryKey_;
    const bool notNull_;
  };

  static const std::vector<MetaData> metaData_;
  bool dirtyFlag_ [4] = {false};

public:
  static const std::string&
  sqlForFindingByPrimaryKey()
  {
    static const std::string sql =
      "select * from " + tableName + " where id = $1";
    return sql;
  }

  static const std::string&
  sqlForDeletingByPrimaryKey()
  {
    static const std::string sql =
      "delete from " + tableName + " where id = $1";
    return sql;
  }

  std::string
  sqlForInserting(bool& needSelection) const
  {
    std::string sql = "insert into " + tableName + " (";
    size_t parametersCount = 0;
    needSelection = false;
    if(dirtyFlag_ [0])
    {
      sql += "id,";
      ++parametersCount;
    }
    if(dirtyFlag_ [1])
    {
      sql += "verify_token,";
      ++parametersCount;
    }
    if(dirtyFlag_ [2])
    {
      sql += "refresh_token,";
      ++parametersCount;
    }
    if(dirtyFlag_ [3])
    {
      sql += "otp,";
      ++parametersCount;
    }
    if(parametersCount > 0)
    {
      sql [sql.length() - 1] = ')';
      sql += " values (";
    }
    else
    {
      sql += ") values (";
    }

    int placeholder = 1;
    char placeholderStr [64];
    size_t n = 0;
    if(dirtyFlag_ [0])
    {
      n = sprintf(placeholderStr, "$%d,", placeholder++);
      sql.append(placeholderStr, n);
    }
    if(dirtyFlag_ [1])
    {
      n = sprintf(placeholderStr, "$%d,", placeholder++);
      sql.append(placeholderStr, n);
    }
    if(dirtyFlag_ [2])
    {
      n = sprintf(placeholderStr, "$%d,", placeholder++);
      sql.append(placeholderStr, n);
    }
    if(dirtyFlag_ [3])
    {
      n = sprintf(placeholderStr, "$%d,", placeholder++);
      sql.append(placeholderStr, n);
    }
    if(parametersCount > 0)
    {
      sql.resize(sql.length() - 1);
    }
    if(needSelection)
    {
      sql.append(") returning *");
    }
    else
    {
      sql.append(1, ')');
    }
    LOG_TRACE << sql;
    return sql;
  }
};
}   // namespace famy_auth
}   // namespace drogon_model

// NOLINTEND