#ifndef EVE_EXPLORER_BACKEND_INCLUDE_EVE_EXPLORER_SQLITE_EVE_UNIVERSE_DATABASE_H_
#define EVE_EXPLORER_BACKEND_INCLUDE_EVE_EXPLORER_SQLITE_EVE_UNIVERSE_DATABASE_H_

#include <sqlite_modern_cpp.h>

#include <string_view>

#include "eve_explorer/ieve_universe_database.h"
#include "eve_explorer/solar_system.h"

namespace eve_explorer::backend::database {
class SQLiteEveUniverseDatabase : public IEveUniverseDatabase {
 public:
  SQLiteEveUniverseDatabase(const std::string& data_base_path);
  ~SQLiteEveUniverseDatabase();

  std::optional<types::SolarSystem> get_solar_system(types::Id id) override;
  std::optional<types::SolarSystem> get_solar_system(const std::string& name) override;
  std::vector<types::SolarSystem> get_solar_systems() override;
    
 private:
  struct BaseInfo {
    std::string name;
    types::Id id;
    types::SecurityStatus security_status;
    types::Point position;
  };

  struct StargatesInfo {
    // TODO
  };

  struct PlanetsInfo {
    // TODO
  };

  struct StationsInfo {
    // TODO
  };
  std::optional<BaseInfo> query_base_info(const std::string& name);
  std::optional<BaseInfo> query_base_info(types::Id id);

  std::string data_base_path_;
  sqlite::database db_;
};
}  // namespace eve_explorer::backend::database

#endif  // EVE_EXPLORER_BACKEND_INCLUDE_EVE_EXPLORER_SQLITE_EVE_UNIVERSE_DATABASE_H_