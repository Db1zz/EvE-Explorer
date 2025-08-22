#ifndef EVE_EXPLORER_SRC_TYPES_STARGATE_H_
#define EVE_EXPLORER_SRC_TYPES_STARGATE_H_

#include <QtQmlIntegration/qqmlintegration.h>
#include <QObject>
#include <QString>

#include "point.h"
#include "common_types.h"

namespace eve_explorer::types {
class Point;

class Stargate {
  Q_GADGET
  Q_PROPERTY(QString name MEMBER name)
  Q_PROPERTY(Point solarSystemPosition MEMBER solarSystemPosition)
  Q_PROPERTY(Point destinationSolarSystemPosition MEMBER
                 destinationSolarSystemPosition)
  Q_PROPERTY(Id stargateId MEMBER stargateId)
  Q_PROPERTY(Id solarSystemId MEMBER solarSystemId)
  Q_PROPERTY(Id destinationStargateId MEMBER destinationStargateId)
  QML_VALUE_TYPE(stargate)

 public:
  Stargate() = default;
  Stargate(const Stargate& stargate);
  Stargate& operator=(const Stargate& stargate);
  bool operator==(const Stargate& stargate);

  QString name;
  Point solarSystemPosition;
  Point destinationSolarSystemPosition;
  Id stargateId;
  Id solarSystemId;
  Id destinationStargateId;
};
}  // namespace eve_explorer::types

Q_DECLARE_METATYPE(eve_explorer::types::Stargate)

#endif  // EVE_EXPLORER_SRC_TYPES_STARGATE_H_