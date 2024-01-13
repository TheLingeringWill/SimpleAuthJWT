#pragma once

// 3rdparty includes
#include <drogon/HttpController.h>
#include <drogon/orm/CoroMapper.h>

// Project includes
#include "utils.h"

namespace drogon::famy_utils
{
template<typename T, bool autoCreation = true>
class ServiceCtrl : public drogon::HttpController<T, autoCreation>
{
  using IOThreadStorage = drogon::IOThreadStorage<drogon::orm::DbClientPtr>;

protected:
  template<typename U>
  using CoroMapper = drogon::orm::CoroMapper<U>;

  using DbClientPtr = IOThreadStorage::ValueType;

  using DrogonDbException = drogon::orm::DrogonDbException;

  virtual DbClientPtr
  getDbClient() = 0;

  [[nodiscard]]
  DbClientPtr
  getDbClientThreadStorage() const noexcept
  {
    return *dbClientThreadStorage_;
  }

private:
  IOThreadStorage dbClientThreadStorage_;
};

}   // namespace drogon::famy_utils
