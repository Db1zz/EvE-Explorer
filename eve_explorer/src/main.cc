// #include <exception>
// #include <iostream>

// #include "eve_explorer/colors.h"

// #define MAP_SCALE 0.00000000000001
// #define CAMERA_MOVEMENT_STEP 60

// int main() {
//   try {
//     eve_explorer::database::SQLiteEveUniverseDatabase db(
//         "./resources/sde/eve_universe_db.sqlite");
//     std::vector<eve_explorer::types::SolarSystem> systems =
//         db.get_solar_systems();

//   } catch (const sqlite::sqlite_exception& e) {
//     std::cerr << "[" << RED400 << "Database" << RESET << "] Error: " <<
//     e.what()
//               << std::endl;
//   }
//   return 0;

// }

#include <QtQmlIntegration/qqmlintegration.h>

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QString>

#include "eve_explorer/sqlite_eve_universe_database.h"
#include "eve_explorer_qml_integration/vector_integration.h"

int main(int argc, char** argv) {
  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return app.exec();
}