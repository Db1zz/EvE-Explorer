#include <iostream>
#include <exception>

#include "eve_explorer/sqlite_eve_universe_database.h"
#include "eve_explorer/colors.h"

#include "raylib-cpp.hpp"

int main() {
  try {
    eve_explorer::backend::database::SQLiteEveUniverseDatabase db(
        "./resources/sde/eve_universe_db.sqlite");

    int window_height = 1024;
    int window_width = 1920;

    raylib::Window window(window_height, window_height, "test");
    while (!window.ShouldClose()) {
      BeginDrawing();
      DrawText("ohayo!", 190, 200, 20, LIGHTGRAY);
      EndDrawing();
    }
  } catch (const sqlite::sqlite_exception& e) {
    std::cerr << "[" << RED400 << "Database" << RESET << "] Error: " << e.what() << std::endl;
  }
  return 0;
}