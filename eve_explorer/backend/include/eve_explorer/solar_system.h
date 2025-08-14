#ifndef EVE_EXPLORER_INCLUDE_EVE_EXPLORER_SOLAR_SYSTEM_H_
#define EVE_EXPLORER_INCLUDE_EVE_EXPLORER_SOLAR_SYSTEM_H_

#include <string>

#include "eve_explorer/common_types.h"
#include "eve_explorer/point.h"

namespace eve_explorer::backend::types {
struct SolarSystem {
  std::string name;
  std::string region_name;
  std::string constellation_name;
  Point position;
  SecurityStatus security_status;
  Id solar_system_id;
  Id region_id;
  Id constellation_id;
  Id faction_id;
  Id sun_type_id;
  double system_radius;
// Planets
//   Moons
//   Belts
// Sun
// Stargates
};
}  // namespace eve_explorer::backend::types
#endif  // EVE_EXPLORER_INCLUDE_EVE_EXPLORER_SOLAR_SYSTEM_H_