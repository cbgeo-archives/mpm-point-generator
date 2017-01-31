#include "point.h"
//! Constructor with id and coordinates
//! \param[in] id index of the point
//! \param[in] coord Coordinates of the point
template <unsigned Pdim>
Point<Pdim>::Point(unsigned id, const std::array<double, Pdim>& coord) : id_{id} {
  coordinates_ = coord;
}
