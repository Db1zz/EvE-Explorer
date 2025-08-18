#ifndef EVE_EXPLORER_INCLUDE_EVE_EXPLORER_SOLAR_POINT_H_
#define EVE_EXPLORER_INCLUDE_EVE_EXPLORER_SOLAR_POINT_H_

namespace eve_explorer::types {
struct Point {
  double x;
  double y;
  double z;

  Point() = default;
  Point(double x, double y, double z) : x(x), y(y), z(z) {}
};
}  // namespace eve_explorer::types

#endif  // EVE_EXPLORER_INCLUDE_EVE_EXPLORER_SOLAR_POINT_H_