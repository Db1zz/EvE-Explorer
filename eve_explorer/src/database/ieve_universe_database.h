#ifndef EVE_EXPLORER_SRC_DATABASE_IEVE_UNIVERSE_DATABASE_H_
#define EVE_EXPLORER_SRC_DATABASE_IEVE_UNIVERSE_DATABASE_H_

// #include <QtQmlIntegration/qqmlintegration.h>
// #include <QtPlugin>
// #include <QObject>
// #include <QVector>

#include "common_types.h"
#include "solar_system.h"
#include "stargate.h"

// #define IEveUniverseDatabaseIID "com.eve_explorer.database"

namespace eve_explorer::database {

class IEveUniverseDatabase {
 public:
  // IEveUniverseDatabase(QObject* parent = nullptr) : QObject(parent) {}

  virtual bool get_solar_system(const QString& name, types::SolarSystem& result_solar_system) = 0;
  virtual bool get_solar_systems(QVector <types::SolarSystem>& result_solar_systems) = 0;
  virtual bool get_solar_system_stargates(
      types::Id solar_system_id,
      QVector<types::Stargate>& result_stargates) = 0;
};

}  // namespace eve_explorer::database

// Q_DECLARE_INTERFACE(eve_explorer::database::IEveUniverseDatabase, IEveUniverseDatabaseIID)

#endif  // EVE_EXPLORER_SRC_DATABASE_IEVE_UNIVERSE_DATABASE_H_