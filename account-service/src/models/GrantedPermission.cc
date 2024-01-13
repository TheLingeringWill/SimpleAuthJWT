/**
 *
 *  GrantedPermission.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */
// NOLINTBEGIN
#include "GrantedPermission.h"

#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::famy_account;

const std::string GrantedPermission::Cols::_role_id = "role_id";
const std::string GrantedPermission::Cols::_permission_id = "permission_id";
const std::string GrantedPermission::primaryKeyName = "";
const bool GrantedPermission::hasPrimaryKey = false;
const std::string GrantedPermission::tableName = "granted_permission";

const std::vector<typename GrantedPermission::MetaData>
  GrantedPermission::metaData_ = {
    {      "role_id", "int64_t", "bigint", 8, 0, 0, 0},
    {"permission_id", "int64_t", "bigint", 8, 0, 0, 0}
};

const std::string&
GrantedPermission::getColumnName(size_t index) noexcept(false)
{
  assert(index < metaData_.size());
  return metaData_ [index].colName_;
}

GrantedPermission::GrantedPermission(
  const Row& r,
  const ssize_t indexOffset
) noexcept
{
  if(indexOffset < 0)
  {
    if(! r ["role_id"].isNull())
    {
      roleId_ = std::make_shared<int64_t>(r ["role_id"].as<int64_t>());
    }
    if(! r ["permission_id"].isNull())
    {
      permissionId_ =
        std::make_shared<int64_t>(r ["permission_id"].as<int64_t>());
    }
  }
  else
  {
    size_t offset = (size_t)indexOffset;
    if(offset + 2 > r.size())
    {
      LOG_FATAL << "Invalid SQL result for this model";
      return;
    }
    size_t index;
    index = offset + 0;
    if(! r [index].isNull())
    {
      roleId_ = std::make_shared<int64_t>(r [index].as<int64_t>());
    }
    index = offset + 1;
    if(! r [index].isNull())
    {
      permissionId_ = std::make_shared<int64_t>(r [index].as<int64_t>());
    }
  }
}

GrantedPermission::GrantedPermission(
  const Json::Value& pJson,
  const std::vector<std::string>& pMasqueradingVector
) noexcept(false)
{
  if(pMasqueradingVector.size() != 2)
  {
    LOG_ERROR << "Bad masquerading vector";
    return;
  }
  if(! pMasqueradingVector [0].empty() && pJson.isMember(pMasqueradingVector [0]))
  {
    dirtyFlag_ [0] = true;
    if(! pJson [pMasqueradingVector [0]].isNull())
    {
      roleId_ = std::make_shared<int64_t>(
        (int64_t)pJson [pMasqueradingVector [0]].asInt64()
      );
    }
  }
  if(! pMasqueradingVector [1].empty() && pJson.isMember(pMasqueradingVector [1]))
  {
    dirtyFlag_ [1] = true;
    if(! pJson [pMasqueradingVector [1]].isNull())
    {
      permissionId_ = std::make_shared<int64_t>(
        (int64_t)pJson [pMasqueradingVector [1]].asInt64()
      );
    }
  }
}

GrantedPermission::GrantedPermission(const Json::Value& pJson) noexcept(false)
{
  if(pJson.isMember("role_id"))
  {
    dirtyFlag_ [0] = true;
    if(! pJson ["role_id"].isNull())
    {
      roleId_ = std::make_shared<int64_t>((int64_t)pJson ["role_id"].asInt64());
    }
  }
  if(pJson.isMember("permission_id"))
  {
    dirtyFlag_ [1] = true;
    if(! pJson ["permission_id"].isNull())
    {
      permissionId_ =
        std::make_shared<int64_t>((int64_t)pJson ["permission_id"].asInt64());
    }
  }
}

void
GrantedPermission::updateByMasqueradedJson(
  const Json::Value& pJson,
  const std::vector<std::string>& pMasqueradingVector
) noexcept(false)
{
  if(pMasqueradingVector.size() != 2)
  {
    LOG_ERROR << "Bad masquerading vector";
    return;
  }
  if(! pMasqueradingVector [0].empty() && pJson.isMember(pMasqueradingVector [0]))
  {
    dirtyFlag_ [0] = true;
    if(! pJson [pMasqueradingVector [0]].isNull())
    {
      roleId_ = std::make_shared<int64_t>(
        (int64_t)pJson [pMasqueradingVector [0]].asInt64()
      );
    }
  }
  if(! pMasqueradingVector [1].empty() && pJson.isMember(pMasqueradingVector [1]))
  {
    dirtyFlag_ [1] = true;
    if(! pJson [pMasqueradingVector [1]].isNull())
    {
      permissionId_ = std::make_shared<int64_t>(
        (int64_t)pJson [pMasqueradingVector [1]].asInt64()
      );
    }
  }
}

void
GrantedPermission::updateByJson(const Json::Value& pJson) noexcept(false)
{
  if(pJson.isMember("role_id"))
  {
    dirtyFlag_ [0] = true;
    if(! pJson ["role_id"].isNull())
    {
      roleId_ = std::make_shared<int64_t>((int64_t)pJson ["role_id"].asInt64());
    }
  }
  if(pJson.isMember("permission_id"))
  {
    dirtyFlag_ [1] = true;
    if(! pJson ["permission_id"].isNull())
    {
      permissionId_ =
        std::make_shared<int64_t>((int64_t)pJson ["permission_id"].asInt64());
    }
  }
}

const int64_t&
GrantedPermission::getValueOfRoleId() const noexcept
{
  const static int64_t defaultValue = int64_t();
  if(roleId_)
  {
    return *roleId_;
  }
  return defaultValue;
}

const std::shared_ptr<int64_t>&
GrantedPermission::getRoleId() const noexcept
{
  return roleId_;
}

void
GrantedPermission::setRoleId(const int64_t& pRoleId) noexcept
{
  roleId_ = std::make_shared<int64_t>(pRoleId);
  dirtyFlag_ [0] = true;
}

void
GrantedPermission::setRoleIdToNull() noexcept
{
  roleId_.reset();
  dirtyFlag_ [0] = true;
}

const int64_t&
GrantedPermission::getValueOfPermissionId() const noexcept
{
  const static int64_t defaultValue = int64_t();
  if(permissionId_)
  {
    return *permissionId_;
  }
  return defaultValue;
}

const std::shared_ptr<int64_t>&
GrantedPermission::getPermissionId() const noexcept
{
  return permissionId_;
}

void
GrantedPermission::setPermissionId(const int64_t& pPermissionId) noexcept
{
  permissionId_ = std::make_shared<int64_t>(pPermissionId);
  dirtyFlag_ [1] = true;
}

void
GrantedPermission::setPermissionIdToNull() noexcept
{
  permissionId_.reset();
  dirtyFlag_ [1] = true;
}

void
GrantedPermission::updateId(const uint64_t id)
{
}

const std::vector<std::string>&
GrantedPermission::insertColumns() noexcept
{
  static const std::vector<std::string> inCols = {"role_id", "permission_id"};
  return inCols;
}

void
GrantedPermission::outputArgs(drogon::orm::internal::SqlBinder& binder) const
{
  if(dirtyFlag_ [0])
  {
    if(getRoleId())
    {
      binder << getValueOfRoleId();
    }
    else
    {
      binder << nullptr;
    }
  }
  if(dirtyFlag_ [1])
  {
    if(getPermissionId())
    {
      binder << getValueOfPermissionId();
    }
    else
    {
      binder << nullptr;
    }
  }
}

const std::vector<std::string>
GrantedPermission::updateColumns() const
{
  std::vector<std::string> ret;
  if(dirtyFlag_ [0])
  {
    ret.push_back(getColumnName(0));
  }
  if(dirtyFlag_ [1])
  {
    ret.push_back(getColumnName(1));
  }
  return ret;
}

void
GrantedPermission::updateArgs(drogon::orm::internal::SqlBinder& binder) const
{
  if(dirtyFlag_ [0])
  {
    if(getRoleId())
    {
      binder << getValueOfRoleId();
    }
    else
    {
      binder << nullptr;
    }
  }
  if(dirtyFlag_ [1])
  {
    if(getPermissionId())
    {
      binder << getValueOfPermissionId();
    }
    else
    {
      binder << nullptr;
    }
  }
}

Json::Value
GrantedPermission::toJson() const
{
  Json::Value ret;
  if(getRoleId())
  {
    ret ["role_id"] = (Json::Int64)getValueOfRoleId();
  }
  else
  {
    ret ["role_id"] = Json::Value();
  }
  if(getPermissionId())
  {
    ret ["permission_id"] = (Json::Int64)getValueOfPermissionId();
  }
  else
  {
    ret ["permission_id"] = Json::Value();
  }
  return ret;
}

Json::Value
GrantedPermission::toMasqueradedJson(
  const std::vector<std::string>& pMasqueradingVector
) const
{
  Json::Value ret;
  if(pMasqueradingVector.size() == 2)
  {
    if(! pMasqueradingVector [0].empty())
    {
      if(getRoleId())
      {
        ret [pMasqueradingVector [0]] = (Json::Int64)getValueOfRoleId();
      }
      else
      {
        ret [pMasqueradingVector [0]] = Json::Value();
      }
    }
    if(! pMasqueradingVector [1].empty())
    {
      if(getPermissionId())
      {
        ret [pMasqueradingVector [1]] = (Json::Int64)getValueOfPermissionId();
      }
      else
      {
        ret [pMasqueradingVector [1]] = Json::Value();
      }
    }
    return ret;
  }
  LOG_ERROR << "Masquerade failed";
  if(getRoleId())
  {
    ret ["role_id"] = (Json::Int64)getValueOfRoleId();
  }
  else
  {
    ret ["role_id"] = Json::Value();
  }
  if(getPermissionId())
  {
    ret ["permission_id"] = (Json::Int64)getValueOfPermissionId();
  }
  else
  {
    ret ["permission_id"] = Json::Value();
  }
  return ret;
}

bool
GrantedPermission::validateJsonForCreation(
  const Json::Value& pJson,
  std::string& err
)
{
  if(pJson.isMember("role_id"))
  {
    if(! validJsonOfField(0, "role_id", pJson ["role_id"], err, true))
    {
      return false;
    }
  }
  if(pJson.isMember("permission_id"))
  {
    if(! validJsonOfField(
         1,
         "permission_id",
         pJson ["permission_id"],
         err,
         true
       ))
    {
      return false;
    }
  }
  return true;
}

bool
GrantedPermission::validateMasqueradedJsonForCreation(
  const Json::Value& pJson,
  const std::vector<std::string>& pMasqueradingVector,
  std::string& err
)
{
  if(pMasqueradingVector.size() != 2)
  {
    err = "Bad masquerading vector";
    return false;
  }
  try
  {
    if(! pMasqueradingVector [0].empty())
    {
      if(pJson.isMember(pMasqueradingVector [0]))
      {
        if(! validJsonOfField(
             0,
             pMasqueradingVector [0],
             pJson [pMasqueradingVector [0]],
             err,
             true
           ))
        {
          return false;
        }
      }
    }
    if(! pMasqueradingVector [1].empty())
    {
      if(pJson.isMember(pMasqueradingVector [1]))
      {
        if(! validJsonOfField(
             1,
             pMasqueradingVector [1],
             pJson [pMasqueradingVector [1]],
             err,
             true
           ))
        {
          return false;
        }
      }
    }
  }
  catch(const Json::LogicError& e)
  {
    err = e.what();
    return false;
  }
  return true;
}

bool
GrantedPermission::validateJsonForUpdate(
  const Json::Value& pJson,
  std::string& err
)
{
  if(pJson.isMember("role_id"))
  {
    if(! validJsonOfField(0, "role_id", pJson ["role_id"], err, false))
    {
      return false;
    }
  }
  if(pJson.isMember("permission_id"))
  {
    if(! validJsonOfField(
         1,
         "permission_id",
         pJson ["permission_id"],
         err,
         false
       ))
    {
      return false;
    }
  }
  return true;
}

bool
GrantedPermission::validateMasqueradedJsonForUpdate(
  const Json::Value& pJson,
  const std::vector<std::string>& pMasqueradingVector,
  std::string& err
)
{
  if(pMasqueradingVector.size() != 2)
  {
    err = "Bad masquerading vector";
    return false;
  }
  try
  {
    if(! pMasqueradingVector [0].empty() && pJson.isMember(pMasqueradingVector [0]))
    {
      if(! validJsonOfField(
           0,
           pMasqueradingVector [0],
           pJson [pMasqueradingVector [0]],
           err,
           false
         ))
      {
        return false;
      }
    }
    if(! pMasqueradingVector [1].empty() && pJson.isMember(pMasqueradingVector [1]))
    {
      if(! validJsonOfField(
           1,
           pMasqueradingVector [1],
           pJson [pMasqueradingVector [1]],
           err,
           false
         ))
      {
        return false;
      }
    }
  }
  catch(const Json::LogicError& e)
  {
    err = e.what();
    return false;
  }
  return true;
}

bool
GrantedPermission::validJsonOfField(
  size_t index,
  const std::string& fieldName,
  const Json::Value& pJson,
  std::string& err,
  bool isForCreation
)
{
  switch(index)
  {
    case 0:
      if(pJson.isNull())
      {
        return true;
      }
      if(! pJson.isInt64())
      {
        err = "Type error in the " + fieldName + " field";
        return false;
      }
      break;
    case 1:
      if(pJson.isNull())
      {
        return true;
      }
      if(! pJson.isInt64())
      {
        err = "Type error in the " + fieldName + " field";
        return false;
      }
      break;
    default:
      err = "Internal error in the server";
      return false;
  }
  return true;
}

// NOLINTEND