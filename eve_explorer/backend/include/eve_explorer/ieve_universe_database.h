#ifndef EVE_EXPLORER_BACKEND_INCLUDE_EVE_EXPLORER_IEVE_UNIVERSE_DATABASE_H_
#define EVE_EXPLORER_BACKEND_INCLUDE_EVE_EXPLORER_IEVE_UNIVERSE_DATABASE_H_

#include <optional>
#include <string>

#include "eve_explorer/solar_system.h"

namespace eve_explorer::backend::database {
class IEveUniverseDatabase {
 public:
  virtual ~IEveUniverseDatabase() = default;

  virtual std::optional<types::SolarSystem> get_solar_system(types::Id id) = 0;
  virtual std::optional<types::SolarSystem> get_solar_system(const std::string& name) = 0;
};
}  // namespace eve_explorer::database

#endif  // EVE_EXPLORER_BACKEND_INCLUDE_EVE_EXPLORER_IEVE_UNIVERSE_DATABASE_H_