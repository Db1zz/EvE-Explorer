#include "stargate.h"

namespace eve_explorer::types {
Stargate::Stargate(const Stargate& stargate) {
  *this = stargate;
}

Stargate& Stargate::operator=(const Stargate& stargate) {
  if (&stargate == this) {
    return *this;
  }
  name = stargate.name;
  solarSystemPosition = stargate.solarSystemPosition;
  destinationSolarSystemPosition =
      stargate.destinationSolarSystemPosition;
  stargateId = stargate.stargateId;
  solarSystemId = stargate.solarSystemId;
  destinationStargateId = stargate.destinationStargateId;

  return *this;
}

bool Stargate::operator==(const Stargate& stargate) {
	if (&stargate == this) {
		return true;
	}

	return (
		name == stargate.name &&
		solarSystemPosition == stargate.solarSystemPosition &&
		destinationSolarSystemPosition == stargate.destinationSolarSystemPosition &&
		stargateId == stargate.stargateId &&
		solarSystemId  == stargate.solarSystemId &&
		destinationStargateId == stargate.destinationStargateId
	);
}

}  // namespace eve_explorer::types
