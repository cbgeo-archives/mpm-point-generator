#include "point.h"
//! Constructor with id and coordinates
//! \param[in] id index of the point
//! \param[in] coord Coordinates of the point
Point::Point(unsigned id, const std::array<double, 2>& coord) : id_{id} {
  coordinates_ = coord;
}
