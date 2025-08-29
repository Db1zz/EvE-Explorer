#include "solar_system.h"

namespace eve_explorer::types {

SolarSystem::SolarSystem(const SolarSystem& solarSystem) {
  *this = solarSystem;
}

SolarSystem& SolarSystem::operator=(const SolarSystem& solarSystem) {
  if (&solarSystem == this) {
    return *this;
  }
  stargates = solarSystem.stargates;
  name = solarSystem.name;
  regionName = solarSystem.regionName;
  constellationName = solarSystem.constellationName;
  position = solarSystem.position;
  securityStatus = solarSystem.securityStatus;
  solarSystemId = solarSystem.solarSystemId;
  regionId = solarSystem.regionId;
  constellationId = solarSystem.constellationId;
  factionId = solarSystem.factionId;
  sunTypeId = solarSystem.sunTypeId;
  systemRadius = solarSystem.systemRadius;

  return *this;
}

bool SolarSystem::operator==(const SolarSystem& solarSystem) {
  return (name == solarSystem.name);
}

QVariantList SolarSystem::getStargates() {
  return stargates;
}

void SolarSystem::setStargates(const QVariantList& stargates) {
  this->stargates = stargates;
}

}  // namespace eve_explorer::types