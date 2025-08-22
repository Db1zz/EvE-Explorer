#ifndef EVE_EXPLORER_SRC_DATABASE_SQLITE_EVE_UNIVERSE_DATABASE_H_
#define EVE_EXPLORER_SRC_DATABASE_SQLITE_EVE_UNIVERSE_DATABASE_H_

#include <QtQmlIntegration/qqmlintegration.h>
#include <sqlite_modern_cpp.h>

#include <QObject>
#include <QString>
#include <QVariant>

#include "ieve_universe_database.h"

namespace eve_explorer::database {
class SQLiteEveUniverseDatabase : public QObject {
  Q_OBJECT

 public:
  SQLiteEveUniverseDatabase(const QString& pathToDatabase);
  SQLiteEveUniverseDatabase(QObject* parent = nullptr);
  ~SQLiteEveUniverseDatabase();

  // QML Functions
  void setDatabasePath(const QString& pathToDatabase);
  QString getDatabasePath(void);
  void setNewDatabase(const QString& pathToDatabase);

  // QML Slots
 public slots:

  Q_INVOKABLE types::SolarSystem getSolarSystem(const QString& name);
  Q_INVOKABLE QVariantList getSolarSystems();
  Q_INVOKABLE QVector<types::Stargate> getSolarSystemStargates(types::Id solarSystemId);

 private:
  struct SolarSystemPopulator {
    QVariantList* solarSystems;
    types::SolarSystem* solarSystem;

    SolarSystemPopulator(QVariantList* solarSystems)
        : solarSystems(solarSystems), solarSystem(nullptr) {}
    SolarSystemPopulator(types::SolarSystem* solarSystem)
        : solarSystems(nullptr), solarSystem(solarSystem) {}

    void operator()(std::string name, std::string regionName,
                    std::string constellationName, double x, double y,
                    double z, types::SecurityStatus securityStatus,
                    types::Id solarSystemId, types::Id regionId,
                    types::Id constellationId, types::Id factionId,
                    types::Id sunTypeId, double systemRadius);
  };

  // QVariantList* SystemsCache_;
  QString pathToDatabase_;
  sqlite::database* db_;
};
}  // namespace eve_explorer::database

#endif  // EVE_EXPLORER_SRC_DATABASE_SQLITE_EVE_UNIVERSE_DATABASE_H_