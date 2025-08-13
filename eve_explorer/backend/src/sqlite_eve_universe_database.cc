#include "eve_explorer/sqlite_eve_universe_database.h"

#include <string>

namespace eve_explorer::backend::database {
SQLiteEveUniverseDatabase::SQLiteEveUniverseDatabase(
    const std::string& data_base_path)
    : data_base_path_(data_base_path), db_(data_base_path) {}

SQLiteEveUniverseDatabase::~SQLiteEveUniverseDatabase() {}

std::optional<types::SolarSystem> SQLiteEveUniverseDatabase::get_solar_system(
    const std::string& name) {
  std::optional<types::SolarSystem> solar_system_opt;
  db_ << R"(
            SELECT ms.solarSystemID, ms.solarSystemName, ms.security, ms.x, ms.y, ms.z,
                  ms.regionID, ms.constellationID, ms.factionID, ms.sunTypeID, ms.radius,
                  mc.constellationName, mr.regionName
            FROM mapSolarSystems ms
            JOIN mapConstellations mc
              ON ms.constellationID = mc.constellationID
            JOIN mapRegions mr
              ON mc.regionID = mr.regionID
            WHERE ms.solarSystemName = ?;
        )"
      << name >>
      [&](types::Id solar_system_id, std::string name,
          types::SecurityStatus security_status, double x, double y, double z,
          types::Id region_id, types::Id constellation_id, types::Id faction_id,
          types::Id sun_type_id, double system_radius,
          std::string constellation_name, std::string region_name) {
        solar_system_opt =
            types::SolarSystem{.name = name,
                               .region_name = region_name,
                               .constellation_name = constellation_name,
                               .position = types::Point(x, y, z),
                               .security_status = security_status,
                               .solar_system_id = solar_system_id,
                               .region_id = region_id,
                               .constellation_id = constellation_id,
                               .faction_id = faction_id,
                               .sun_type_id = sun_type_id,
                               .system_radius = system_radius};
      };
  return solar_system_opt;
}

std::vector<types::SolarSystem> SQLiteEveUniverseDatabase::get_solar_systems() {
  std::vector<types::SolarSystem> systems;

  db_ << R"(
            SELECT solarSystemID, solarSystemName, security, x, y, z
            FROM mapSolarSystems)" >>
      [&](types::Id id, std::string name, types::SecurityStatus ss, double x,
          double y, double z) {
        types::SolarSystem solar_system;
        solar_system.solar_system_id = id;
        solar_system.name = name;
        solar_system.security_status = ss;
        solar_system.position = types::Point(x, y, z);

        systems.push_back(std::move(solar_system));
      };
  return systems;
}
}  // namespace eve_explorer::backend::database