#ifndef EVE_EXPLORER_INCLUDE_EVE_EXPLORER_STARGATE_H_
#define EVE_EXPLORER_INCLUDE_EVE_EXPLORER_STARGATE_H_

#include <string>

#include "eve_explorer/common_types.h"
#include "eve_explorer/point.h"

namespace eve_explorer::types {
struct Stargate {
  std::string name;
  Point solar_system_position;
  Point destination_solar_system_position;
  Id stargate_id;
  Id solar_system_id;
  Id destination_stargate_id;
};
}  // namespace eve_explorer::types

#endif  // EVE_EXPLORER_INCLUDE_EVE_EXPLORER_STARGATE_H_