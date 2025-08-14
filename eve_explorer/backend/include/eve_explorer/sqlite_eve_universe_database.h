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

  std::optional<types::SolarSystem> get_solar_system(
      const std::string& name) override;
  std::vector<types::SolarSystem> get_solar_systems() override;

 private:
  struct SolarSystemPopulator {
    std::vector<types::SolarSystem>* solar_systems;
    std::optional<types::SolarSystem>* solar_system_opt;

    SolarSystemPopulator(std::vector<types::SolarSystem>* solar_systems)
        : solar_systems(solar_systems), solar_system_opt(nullptr) {}
    SolarSystemPopulator(std::optional<types::SolarSystem>* solar_system_opt)
        : solar_system_opt(solar_system_opt), solar_systems(nullptr) {}

    void operator()(std::string name, std::string region_name,
                    std::string constellation_name, double x, double y,
                    double z, types::SecurityStatus security_status,
                    types::Id solar_system_id, types::Id region_id,
                    types::Id constellation_id, types::Id faction_id,
                    types::Id sun_type_id, double system_radius);
  };

  std::string data_base_path_;
  sqlite::database db_;
};
}  // namespace eve_explorer::backend::database

#endif  // EVE_EXPLORER_BACKEND_INCLUDE_EVE_EXPLORER_SQLITE_EVE_UNIVERSE_DATABASE_H_