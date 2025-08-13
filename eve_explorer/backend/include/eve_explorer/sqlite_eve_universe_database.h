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

  std::optional<types::SolarSystem> get_solar_system(const std::string& name) override;
  std::vector<types::SolarSystem> get_solar_systems() override;
    
 private:
  std::string data_base_path_;
  sqlite::database db_;
};
}  // namespace eve_explorer::backend::database

#endif  // EVE_EXPLORER_BACKEND_INCLUDE_EVE_EXPLORER_SQLITE_EVE_UNIVERSE_DATABASE_H_