#include "eve_explorer/sqlite_eve_universe_database.h"

#include <string>

namespace eve_explorer::database {

SQLiteEveUniverseDatabase::SQLiteEveUniverseDatabase(
    const std::string& data_base_path)
    : data_base_path_(data_base_path), db_(data_base_path) {}

SQLiteEveUniverseDatabase::~SQLiteEveUniverseDatabase() {}

std::optional<types::SolarSystem> SQLiteEveUniverseDatabase::get_solar_system(
    const std::string& name) {
  std::optional<types::SolarSystem> solar_system_opt;

  db_ << R"(
            SELECT ms.solarSystemName, 
                   mr.regionName,
                   mc.constellationName,
                   ms.x, ms.y, ms.z,
                   ms.security,
                   ms.solarSystemID,
                   ms.regionID,
                   ms.constellationID,
                   ms.factionID,
                   ms.sunTypeID,
                   ms.radius
            FROM mapSolarSystems ms
            JOIN mapConstellations mc
              ON ms.constellationID = mc.constellationID
            JOIN mapRegions mr
              ON mc.regionID = mr.regionID
            WHERE ms.solarSystemName = ?;
        )"
      << name >>
      SolarSystemPopulator(&solar_system_opt);
  if (solar_system_opt) {
    solar_system_opt.value().stargates =
        get_solar_system_stargates(solar_system_opt.value().solar_system_id);
  }
  return solar_system_opt;
}

std::vector<types::SolarSystem> SQLiteEveUniverseDatabase::get_solar_systems() {
  std::vector<types::SolarSystem> systems;

  db_ << R"(
            SELECT ms.solarSystemName, 
                   mr.regionName,
                   mc.constellationName,
                   ms.x, ms.y, ms.z,
                   ms.security,
                   ms.solarSystemID,
                   ms.regionID,
                   ms.constellationID,
                   ms.factionID,
                   ms.sunTypeID,
                   ms.radius
            FROM mapSolarSystems ms
            JOIN mapConstellations mc
              ON ms.constellationID = mc.constellationID
            JOIN mapRegions mr
              ON mc.regionID = mr.regionID
            WHERE ms.constellationID = mc.constellationID;
        )" >>
      SolarSystemPopulator(&systems);
  return systems;
}

/*
  starGateID -> solarSystemID -> solarSystemPos
  destionationStarGateID -> destinationSolarSystemID ->
  destinationSolarSystemPos
*/
std::vector<types::Stargate>
SQLiteEveUniverseDatabase::get_solar_system_stargates(
    types::Id solar_system_id) {
  std::vector<types::Stargate> stargates;

  db_ << R"(
            SELECT md.itemID,
                   md.solarSystemID,
                   md.x, md.y, md.z,
                   md.itemName,
                   mj.destinationID
            FROM mapDenormalize md
            JOIN mapJumps mj
              ON md.itemID = mj.stargateID
           WHERE md.solarSystemID = ?;
       )"
      << solar_system_id >>
      [&](types::Id item_id, types::Id solar_system_id, double x, double y,
          double z, std::string item_name, types::Id destination_id) {
        stargates.push_back(types::Stargate{
            .name = item_name,
            .destination_solar_system_position = types::Point(x, y, z),
            .solar_system_id = solar_system_id,
            .stargate_id = item_id,
            .destination_stargate_id = destination_id});
      };

  return stargates;
}

void SQLiteEveUniverseDatabase::SolarSystemPopulator::operator()(
    std::string name, std::string region_name, std::string constellation_name,
    double x, double y, double z, types::SecurityStatus security_status,
    types::Id solar_system_id, types::Id region_id, types::Id constellation_id,
    types::Id faction_id, types::Id sun_type_id, double system_radius) {
  types::SolarSystem solar_system =
      types::SolarSystem{.name = name,
                         .region_name = region_name,
                         .constellation_name = constellation_name,
                         .position = types::Point(x, y, z),
                         .security_status = security_status,
                         .solar_system_id = solar_system_id,
                         .region_id = region_id,
                         .faction_id = faction_id,
                         .sun_type_id = sun_type_id,
                         .system_radius = system_radius};
  if (name.empty()) {
    return;
  } else if (solar_systems) {
    solar_systems->push_back(std::move(solar_system));
  } else {
    solar_system_opt->emplace(std::move(solar_system));
  }
}

}  // namespace eve_explorer::database