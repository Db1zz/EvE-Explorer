#include <iostream>
#include <exception>

#include "eve_explorer/sqlite_eve_universe_database.h"
#include "eve_explorer/colors.h"

#include <sstream>

int main() {
  try {
    eve_explorer::backend::database::SQLiteEveUniverseDatabase db(
        "./resources/sde/eve_sde_db.sqlite");
    auto ssopt = db.get_solar_system("Jita");
    if (ssopt) {
      eve_explorer::backend::types::SolarSystem ss = ssopt.value();
      std::cout << ss.name << std::endl;
    }
  } catch (const sqlite::sqlite_exception& e) {
    std::cerr << "[" << RED400 << "Database" << RESET << "] Error: " << e.what() << std::endl;
  }
  return 0;
}