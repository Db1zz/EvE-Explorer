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
      SolarSystemPopulator(&solarSystem, *this);
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
      SolarSystemPopulator(&solarSystems, *this);
  return solarSystems;
}

QVariantList SQLiteEveUniverseDatabase::getSolarSystemStargates(
    types::Id solarSystemId) const {
  QVariantList stargates;
  *db_ << R"(
            SELECT md.itemID,
                   md.solarSystemID,
                   md.x AS gateX,
                   md.y AS gateY,
                   md.z AS gateZ,
                   md.itemName,
                   mj.destinationID,
                   ms.x AS systemX,
                   ms.y AS systemY,
                   ms.z AS systemZ,
                   ms2.x AS destX,
                   ms2.y AS destY,
                   ms2.z AS destZ
            FROM mapDenormalize md
            JOIN mapJumps mj
              ON md.itemID = mj.stargateID
            JOIN mapSolarSystems ms
              ON ms.solarSystemID = md.solarSystemID
            JOIN mapDenormalize md2
              ON md2.itemID = mj.destinationID
            JOIN mapSolarSystems ms2
              ON ms2.solarSystemID = md2.solarSystemID
           WHERE ms.solarSystemID = ?;  
       )"
       << solarSystemId >>
      [&](types::Id itemId, types::Id solarSystemId, double gateX, double gateY,
          double gateZ, std::string itemName, types::Id destinationId,
          double systemX, double systemY, double systemZ, double destX,
          double destY, double destZ) {
        types::Stargate newStargate;
        newStargate.name = itemName.c_str(),
        newStargate.position = types::Point(gateX, gateY, gateZ),
        newStargate.solarSystemId = solarSystemId,
        newStargate.stargateId = itemId,
        newStargate.destinationStargateId = destinationId,
        newStargate.solarSystemPosition =
            types::Point(systemX, systemY, systemZ),
        newStargate.destinationSolarSystemPosition =
            types::Point(destX, destY, destZ);
        stargates.push_back(QVariant::fromValue(std::move(newStargate)));
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
  newSolarSystem.stargates = database.getSolarSystemStargates(solarSystemId);
  if (name.empty()) {
    return;
  } else if (solarSystems) {
    solarSystems->push_back(QVariant::fromValue(std::move(newSolarSystem)));
  } else {
    *this->solarSystem = std::move(newSolarSystem);
  }
}

}  // namespace eve_explorer::database