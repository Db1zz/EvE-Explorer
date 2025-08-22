#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QString>

#include "database/sqlite_eve_universe_database.h"
#include "types/point.h"
#include "types/solar_system.h"
#include "types/stargate.h"

int main(int argc, char** argv) {
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  eve_explorer::database::SQLiteEveUniverseDatabase database(
      "./resources/sde/eve_universe_db.sqlite");

  QVariantList systems = database.getSolarSystems();

  engine.rootContext()->setContextProperty("database", &database);
  engine.rootContext()->setContextProperty("solarSystems", systems);
  engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
  if (engine.rootObjects().isEmpty()) {
    return -1;
  }
  return app.exec();
}
