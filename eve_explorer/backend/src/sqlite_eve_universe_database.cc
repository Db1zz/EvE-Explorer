#include "eve_explorer/sqlite_eve_universe_database.h"

#include <string>

namespace eve_explorer::backend::database {
SQLiteEveUniverseDatabase::SQLiteEveUniverseDatabase(
    const std::string& data_base_path)
    : data_base_path_(data_base_path), db_(data_base_path) {
}

SQLiteEveUniverseDatabase::~SQLiteEveUniverseDatabase() {}

std::optional<types::SolarSystem> SQLiteEveUniverseDatabase::get_solar_system(
    types::Id id) {
  std::optional<types::SolarSystem> solar_system;
  std::optional<BaseInfo> optional_base_info = query_base_info(id);

  if (optional_base_info) {
    BaseInfo& base_info = optional_base_info.value();
    solar_system =
        types::SolarSystem{.id = base_info.id,
                           .name = base_info.name,
                           .position = base_info.position,
                           .security_status = base_info.security_status};
  }
  return solar_system;
}

std::optional<types::SolarSystem> SQLiteEveUniverseDatabase::get_solar_system(
    const std::string& name) {
  std::optional<types::SolarSystem> solar_system;
  std::optional<BaseInfo> optional_base_info = query_base_info(name);

  if (optional_base_info) {
    BaseInfo& base_info = optional_base_info.value();
    solar_system = types::SolarSystem{.id = base_info.id,
                                      .name = base_info.name,
                                      .position = base_info.position,
                                      .security_status = base_info.security_status};
  }
  return solar_system;
}

std::vector<types::SolarSystem> SQLiteEveUniverseDatabase::get_solar_systems() {
    std::vector<types::SolarSystem> systems;

    db_ << "SELECT solarSystemID, solarSystemName, security, x, y, z FROM mapSolarSystems;"
        >> [&](types::Id id, std::string name, types::SecurityStatus ss, double x, double y, double z){
          types::SolarSystem solar_system;
          solar_system.id = id;
          solar_system.name = name;
          solar_system.security_status = ss;
          solar_system.position.x = x;
          solar_system.position.y = y;
          solar_system.position.z = z;

          systems.push_back(std::move(solar_system));
    };
    return systems;
}

std::optional<SQLiteEveUniverseDatabase::BaseInfo> SQLiteEveUniverseDatabase::
    query_base_info(const std::string& name) {
  std::optional<BaseInfo> base_info;

  db_ << "SELECT solarSystemName, solarSystemID, security FROM mapSolarSystems "
         "WHERE "
         "solarSystemName = ?;"
      << name >>
      [&](std::string name, types::Id id,
          types::SecurityStatus security_status) {
        base_info = BaseInfo{
            .name = name, .id = id, .security_status = security_status};
      };
  return base_info;
}

std::optional<SQLiteEveUniverseDatabase::BaseInfo>
SQLiteEveUniverseDatabase::query_base_info(types::Id id) {
  std::optional<BaseInfo> base_info;

  db_ << "SELECT solarSystemID, solarSystemName, security FROM mapSolarSystems "
         "WHERE solarSystemID = ?;"
      << id >>
      [&](types::Id id, std::string name,
          types::SecurityStatus security_status) {
        base_info =
            BaseInfo{.name = name, .id = id, .security_status = security_status};
      };
  return base_info;
}

}  // namespace eve_explorer::database