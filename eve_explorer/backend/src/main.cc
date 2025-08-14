#include <exception>
#include <iostream>

#include "eve_explorer/colors.h"
#include "eve_explorer/sqlite_eve_universe_database.h"
#include "raylib-cpp.hpp"

#define MAP_SCALE 0.000000000000001

int main() {
  try {
    eve_explorer::backend::database::SQLiteEveUniverseDatabase db(
        "./resources/sde/eve_universe_db.sqlite");

    int window_height = 1440;
    int window_width = 3440;

    std::vector<eve_explorer::backend::types::SolarSystem> systems =
        db.get_solar_systems();

    std::optional<eve_explorer::backend::types::SolarSystem> ss_opt = db.get_solar_system("Jita");
    if (ss_opt) {
      auto& ss = ss_opt.value();
      std::cout << "System: " << ss.name << " Region: " << ss.region_name << " Constellation: " << ss.constellation_name << std::endl;
    }
    raylib::Window window(window_width, window_height, "test");
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    while (!window.ShouldClose()) {
      if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        camera.target.x += 10;
      } else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        camera.target.x -= 10;
      } else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        camera.target.y -= 10;
      } else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        camera.target.y += 10;
      }
      camera.zoom = expf(logf(camera.zoom) + ((float)GetMouseWheelMove() * 0.1f));

      BeginDrawing();
      ClearBackground(RAYWHITE);
      BeginMode2D(camera);

      for (const auto& system : systems) {
        DrawCircle(system.position.x * MAP_SCALE,
                   -system.position.z * MAP_SCALE, 2, DARKGRAY);
      }
      EndMode2D();
      EndDrawing();
    }
  } catch (const sqlite::sqlite_exception& e) {
    std::cerr << "[" << RED400 << "Database" << RESET << "] Error: " << e.what()
              << std::endl;
  }
  return 0;
}