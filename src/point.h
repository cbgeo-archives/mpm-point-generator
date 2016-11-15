
#ifndef Header_h
#define Header_h
#include <array>

class Point {

 public:
  Point(unsigned id, const std::array<double, 2>& coord);

 private:
  unsigned id_;
  std::array<double, 2> coordinates_;
};

#endif /* Header_h */
