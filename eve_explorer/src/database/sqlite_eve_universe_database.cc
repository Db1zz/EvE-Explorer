#include "sqlite_eve_universe_database.h"

#include <string>

namespace eve_explorer::database {

SQLiteEveUniverseDatabase::SQLiteEveUniverseDatabase(
    const QString& pathToDatabase)
    : pathToDatabase_(pathToDatabase) {
  setNewDatabase(pathToDatabase);
}

SQLiteEveUniverseDatabase::SQLiteEveUniverseDatabase(QObject* parent)
    : QObject(parent), db_(nullptr) {}

SQLiteEveUniverseDatabase::~SQLiteEveUniverseDatabase() {
  if (db_ != nullptr) {
    delete db_;
  }
}

void SQLiteEveUniverseDatabase::setNewDatabase(const QString& pathToDatabase) {
  pathToDatabase_ = pathToDatabase;
  db_ = new sqlite::database(pathToDatabase.toStdString());
}

void SQLiteEveUniverseDatabase::setDatabasePath(const QString& pathToDatabase) {
  if (db_) {
    delete db_;
  }
  setNewDatabase(pathToDatabase);
}

QString SQLiteEveUniverseDatabase::getDatabasePath(void) {
  return pathToDatabase_;
}

types::SolarSystem SQLiteEveUniverseDatabase::getSolarSystem(
    const QString& name) {
  types::SolarSystem solarSystem;

  *db_ << R"(
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
      SolarSystemPopulator(&solarSystem);
  if (!solarSystem.name.isEmpty()) {
    solarSystem.stargates =
        std::move(getSolarSystemStargates(solarSystem.solarSystemId));
  }
  return solarSystem;
}

QVariantList SQLiteEveUniverseDatabase::getSolarSystems() {
  QVariantList solarSystems;
  *db_ << R"(
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
      SolarSystemPopulator(&solarSystems);
  return solarSystems;
}

/*
  starGateID -> solarSystemID -> solarSystemPos
  destionationStarGateID -> destinationSolarSystemID ->
  destinationSolarSystemPos
*/
QVector<types::Stargate> SQLiteEveUniverseDatabase::getSolarSystemStargates(
    types::Id solarSystemId) {
  QVector<types::Stargate> stargates;

  *db_ << R"(
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
       << solarSystemId >>
      [&](types::Id itemId, types::Id solarSystemId, double x, double y,
          double z, std::string itemName, types::Id destinationId) {
        types::Stargate newStargate;
        newStargate.name = itemName.c_str(),
        newStargate.destinationSolarSystemPosition = types::Point(x, y, z),
        newStargate.solarSystemId = solarSystemId,
        newStargate.stargateId = itemId,
        newStargate.destinationStargateId = destinationId;
        stargates.push_back(newStargate);
      };

  return stargates;
}

void SQLiteEveUniverseDatabase::SolarSystemPopulator::operator()(
    std::string name, std::string regionName, std::string constellationName,
    double x, double y, double z, types::SecurityStatus securityStatus,
    types::Id solarSystemId, types::Id regionId, types::Id constellationId,
    types::Id factionId, types::Id sunTypeId, double systemRadius) {
  types::SolarSystem newSolarSystem;
  newSolarSystem.name = name.c_str();
  newSolarSystem.regionName = regionName.c_str();
  newSolarSystem.constellationName = constellationName.c_str();
  newSolarSystem.position = types::Point(x, y, z);
  newSolarSystem.securityStatus = securityStatus;
  newSolarSystem.solarSystemId = solarSystemId;
  newSolarSystem.regionId = regionId;
  newSolarSystem.constellationId = constellationId;
  newSolarSystem.factionId = factionId;
  newSolarSystem.sunTypeId = sunTypeId;
  newSolarSystem.systemRadius = systemRadius;
  if (name.empty()) {
    return;
  } else if (solarSystems) {
    solarSystems->push_back(QVariant::fromValue(std::move(newSolarSystem)));
  } else {
    *this->solarSystem = std::move(newSolarSystem);
  }
}

}  // namespace eve_explorer::database