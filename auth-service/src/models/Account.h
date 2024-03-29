/**
 *
 *  Account.h
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
namespace famy_account
{

class Account
{
public:
  struct Cols
  {
    static const std::string _id;
    static const std::string _uuid;
    static const std::string _role_id;
    static const std::string _first_name;
    static const std::string _last_name;
    static const std::string _email;
    static const std::string _password;
    static const std::string _is_verified;
    static const std::string _address;
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
  explicit Account(
    const drogon::orm::Row& r,
    const ssize_t indexOffset = 0
  ) noexcept;

  /**
   * @brief constructor
   * @param pJson The json object to construct a new instance.
   */
  explicit Account(const Json::Value& pJson) noexcept(false);

  /**
   * @brief constructor
   * @param pJson The json object to construct a new instance.
   * @param pMasqueradingVector The aliases of table columns.
   */
  Account(
    const Json::Value& pJson,
    const std::vector<std::string>& pMasqueradingVector
  ) noexcept(false);

  Account() = default;

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

  /**  For column uuid  */
  /// Get the value of the column uuid, returns the default value if the column
  /// is null
  const std::string&
  getValueOfUuid() const noexcept;
  /// Return a shared_ptr object pointing to the column const value, or an empty
  /// shared_ptr object if the column is null
  const std::shared_ptr<std::string>&
  getUuid() const noexcept;
  /// Set the value of the column uuid
  void
  setUuid(const std::string& pUuid) noexcept;
  void
  setUuid(std::string&& pUuid) noexcept;

  /**  For column role_id  */
  /// Get the value of the column role_id, returns the default value if the
  /// column is null
  const int64_t&
  getValueOfRoleId() const noexcept;
  /// Return a shared_ptr object pointing to the column const value, or an empty
  /// shared_ptr object if the column is null
  const std::shared_ptr<int64_t>&
  getRoleId() const noexcept;
  /// Set the value of the column role_id
  void
  setRoleId(const int64_t& pRoleId) noexcept;
  void
  setRoleIdToNull() noexcept;

  /**  For column first_name  */
  /// Get the value of the column first_name, returns the default value if the
  /// column is null
  const std::string&
  getValueOfFirstName() const noexcept;
  /// Return a shared_ptr object pointing to the column const value, or an empty
  /// shared_ptr object if the column is null
  const std::shared_ptr<std::string>&
  getFirstName() const noexcept;
  /// Set the value of the column first_name
  void
  setFirstName(const std::string& pFirstName) noexcept;
  void
  setFirstName(std::string&& pFirstName) noexcept;

  /**  For column last_name  */
  /// Get the value of the column last_name, returns the default value if the
  /// column is null
  const std::string&
  getValueOfLastName() const noexcept;
  /// Return a shared_ptr object pointing to the column const value, or an empty
  /// shared_ptr object if the column is null
  const std::shared_ptr<std::string>&
  getLastName() const noexcept;
  /// Set the value of the column last_name
  void
  setLastName(const std::string& pLastName) noexcept;
  void
  setLastName(std::string&& pLastName) noexcept;

  /**  For column email  */
  /// Get the value of the column email, returns the default value if the column
  /// is null
  const std::string&
  getValueOfEmail() const noexcept;
  /// Return a shared_ptr object pointing to the column const value, or an empty
  /// shared_ptr object if the column is null
  const std::shared_ptr<std::string>&
  getEmail() const noexcept;
  /// Set the value of the column email
  void
  setEmail(const std::string& pEmail) noexcept;
  void
  setEmail(std::string&& pEmail) noexcept;

  /**  For column password  */
  /// Get the value of the column password, returns the default value if the
  /// column is null
  const std::string&
  getValueOfPassword() const noexcept;
  /// Return a shared_ptr object pointing to the column const value, or an empty
  /// shared_ptr object if the column is null
  const std::shared_ptr<std::string>&
  getPassword() const noexcept;
  /// Set the value of the column password
  void
  setPassword(const std::string& pPassword) noexcept;
  void
  setPassword(std::string&& pPassword) noexcept;

  /**  For column is_verified  */
  /// Get the value of the column is_verified, returns the default value if the
  /// column is null
  const bool&
  getValueOfIsVerified() const noexcept;
  /// Return a shared_ptr object pointing to the column const value, or an empty
  /// shared_ptr object if the column is null
  const std::shared_ptr<bool>&
  getIsVerified() const noexcept;
  /// Set the value of the column is_verified
  void
  setIsVerified(const bool& pIsVerified) noexcept;

  /**  For column address  */
  /// Get the value of the column address, returns the default value if the
  /// column is null
  const std::string&
  getValueOfAddress() const noexcept;
  /// Return a shared_ptr object pointing to the column const value, or an empty
  /// shared_ptr object if the column is null
  const std::shared_ptr<std::string>&
  getAddress() const noexcept;
  /// Set the value of the column address
  void
  setAddress(const std::string& pAddress) noexcept;
  void
  setAddress(std::string&& pAddress) noexcept;
  void
  setAddressToNull() noexcept;

  static size_t
  getColumnNumber() noexcept
  {
    return 9;
  }

  static const std::string&
  getColumnName(size_t index) noexcept(false);

  Json::Value
  toJson() const;
  Json::Value
  toMasqueradedJson(const std::vector<std::string>& pMasqueradingVector) const;
  /// Relationship interfaces

private:
  friend drogon::orm::Mapper<Account>;
#ifdef __cpp_impl_coroutine
  friend drogon::orm::CoroMapper<Account>;
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
  std::shared_ptr<std::string> uuid_;
  std::shared_ptr<int64_t> roleId_;
  std::shared_ptr<std::string> firstName_;
  std::shared_ptr<std::string> lastName_;
  std::shared_ptr<std::string> email_;
  std::shared_ptr<std::string> password_;
  std::shared_ptr<bool> isVerified_;
  std::shared_ptr<std::string> address_;

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
  bool dirtyFlag_ [9] = {false};

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
    sql += "uuid,";
    ++parametersCount;
    if(! dirtyFlag_ [1])
    {
      needSelection = true;
    }
    if(dirtyFlag_ [2])
    {
      sql += "role_id,";
      ++parametersCount;
    }
    if(dirtyFlag_ [3])
    {
      sql += "first_name,";
      ++parametersCount;
    }
    if(dirtyFlag_ [4])
    {
      sql += "last_name,";
      ++parametersCount;
    }
    if(dirtyFlag_ [5])
    {
      sql += "email,";
      ++parametersCount;
    }
    if(dirtyFlag_ [6])
    {
      sql += "password,";
      ++parametersCount;
    }
    sql += "is_verified,";
    ++parametersCount;
    if(! dirtyFlag_ [7])
    {
      needSelection = true;
    }
    if(dirtyFlag_ [8])
    {
      sql += "address,";
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
    else
    {
      sql += "default,";
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
    if(dirtyFlag_ [4])
    {
      n = sprintf(placeholderStr, "$%d,", placeholder++);
      sql.append(placeholderStr, n);
    }
    if(dirtyFlag_ [5])
    {
      n = sprintf(placeholderStr, "$%d,", placeholder++);
      sql.append(placeholderStr, n);
    }
    if(dirtyFlag_ [6])
    {
      n = sprintf(placeholderStr, "$%d,", placeholder++);
      sql.append(placeholderStr, n);
    }
    if(dirtyFlag_ [7])
    {
      n = sprintf(placeholderStr, "$%d,", placeholder++);
      sql.append(placeholderStr, n);
    }
    else
    {
      sql += "default,";
    }
    if(dirtyFlag_ [8])
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
}   // namespace famy_account
}   // namespace drogon_model

// NOLINTEND