#include "point.h"

#include <QDebug>

namespace eve_explorer::types {

Point::Point(const Point& point) : x(point.x), y(point.y), z(point.z) {}

Point::Point(double x, double y, double z) : x(x), y(y), z(z) {}

Point& Point::operator=(const Point& point) {
  if (&point == this) {
    return *this;
  }
  x = point.x;
  y = point.y;
  z = point.z;
  return *this;
}

bool Point::operator==(const Point& point) {
  return (x == point.x && y == point.y && z == point.z);
}

}  // namespace eve_explorer::types
