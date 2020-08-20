#ifndef SIR_POINT_HPP
#define SIR_POINT_HPP

namespace SIR {
struct Point {
  int x;
  int y;
};

inline bool operator==(Point const &l, Point const &r) {
  return l.x == r.x && l.y == r.y;
}

inline bool operator!=(Point const &l, Point const &r) { return !(l == r); }

} // namespace SIR

#endif
