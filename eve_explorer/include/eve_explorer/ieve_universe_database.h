#ifndef EVE_EXPLORER_BACKEND_INCLUDE_EVE_EXPLORER_IEVE_UNIVERSE_DATABASE_H_
#define EVE_EXPLORER_BACKEND_INCLUDE_EVE_EXPLORER_IEVE_UNIVERSE_DATABASE_H_

#include <optional>
#include <string>

#include "eve_explorer/common_types.h"
#include "eve_explorer/solar_system.h"

namespace eve_explorer::database {
class IEveUniverseDatabase {
 public:
  virtual ~IEveUniverseDatabase() = default;

  virtual std::optional<types::SolarSystem> get_solar_system(
      const std::string& name) = 0;
  virtual std::vector<types::SolarSystem> get_solar_systems() = 0;
  virtual std::vector<types::Stargate> get_solar_system_stargates(
      types::Id solar_system_id) = 0;
};
}  // namespace eve_explorer::database

#endif  // EVE_EXPLORER_BACKEND_INCLUDE_EVE_EXPLORER_IEVE_UNIVERSE_DATABASE_H_