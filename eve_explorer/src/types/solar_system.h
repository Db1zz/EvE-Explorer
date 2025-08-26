#ifndef EVE_EXPLORER_SRC_TYPES_SOLAR_SYSTEM_H_
#define EVE_EXPLORER_SRC_TYPES_SOLAR_SYSTEM_H_

#include <QtQmlIntegration/qqmlintegration.h>
#include <QString>
#include <QVariantList>

#include "common_types.h"
#include "point.h"
#include "stargate.h"

namespace eve_explorer::types {

class SolarSystem {
  Q_GADGET
  Q_PROPERTY(QString name MEMBER name)
  Q_PROPERTY(QString regionName MEMBER regionName)
  Q_PROPERTY(QString constellationName MEMBER constellationName)
  Q_PROPERTY(Point position MEMBER position)
  Q_PROPERTY(SecurityStatus securityStatus MEMBER securityStatus)
  Q_PROPERTY(Id solarSystemId MEMBER solarSystemId)
  Q_PROPERTY(Id regionId MEMBER regionId)
  Q_PROPERTY(Id constellationId MEMBER constellationId)
  Q_PROPERTY(Id factionId MEMBER factionId)
  Q_PROPERTY(Id sunTypeId MEMBER sunTypeId)
  Q_PROPERTY(double systemRadius MEMBER systemRadius)
  QML_VALUE_TYPE(solarSystem)

 public:
  SolarSystem() = default;
  SolarSystem(const SolarSystem& solarSystem);
  SolarSystem& operator=(const SolarSystem& solarSystem);
  bool operator==(const SolarSystem& solarSystem);

  Q_INVOKABLE QVariantList getStargates();
  void setStargates(const QVariantList& stargates);

  QVariantList stargates;
  QString name;
  QString regionName;
  QString constellationName;
  Point position;
  SecurityStatus securityStatus;
  Id solarSystemId;
  Id regionId;
  Id constellationId;
  Id factionId;
  Id sunTypeId;
  double systemRadius;
};

}  // namespace eve_explorer::types

Q_DECLARE_METATYPE(eve_explorer::types::SolarSystem)

#endif  // EVE_EXPLORER_SRC_TYPES_SOLAR_SYSTEM_H_
