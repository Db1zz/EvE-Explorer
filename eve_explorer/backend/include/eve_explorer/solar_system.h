#ifndef EVE_EXPLORER_INCLUDE_EVE_EXPLORER_SOLAR_SYSTEM_H_
#define EVE_EXPLORER_INCLUDE_EVE_EXPLORER_SOLAR_SYSTEM_H_

#include <string>

#include "eve_explorer/common_types.h"
#include "eve_explorer/point.h"

namespace eve_explorer::backend::types {
struct SolarSystem {
  Id id;
  std::string name;
  SecurityStatus security_status;
  Point position;
  // Planets
  //   Moons
  //   Belts
  // Sun
  // Stargates
  // std::string region_name;
  // std::string constellation_name;
};
}  // namespace eve_explorer::backend::types

#endif  // EVE_EXPLORER_INCLUDE_EVE_EXPLORER_SOLAR_SYSTEM_H_