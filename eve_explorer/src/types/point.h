#ifndef EVE_EXPLORER_SRC_TYPES_POINT_H_
#define EVE_EXPLORER_SRC_TYPES_POINT_H_

#include <QtQmlIntegration/qqmlintegration.h>

#include <QObject>

namespace eve_explorer::types {
class Point {
  Q_GADGET
  Q_PROPERTY(double x MEMBER x)
  Q_PROPERTY(double y MEMBER y)
  Q_PROPERTY(double z MEMBER z)
  QML_VALUE_TYPE(point3d)

 public:
  Point() = default;
  Point(const Point& point);
  Point(double x, double y, double z);
  Point& operator=(const Point& point);
  bool operator==(const Point& point);

 public:
  double x;
  double y;
  double z;
};

}  // namespace eve_explorer::types

Q_DECLARE_METATYPE(eve_explorer::types::Point)

#endif  // EVE_EXPLORER_SRC_TYPES_POINT_H_
