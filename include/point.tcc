#include "point.h"
//! \brief Constructor with id and coordinates
//! \param[in] id index of the vertex
//! \param[in] coord Coordinates of the point
//! \param[in] stress initial stress of the point
template <unsigned Tdim>
Point<Tdim>::Point(unsigned id, const std::array<double, Tdim>& coord,
                   const std::array<double, 6>& stress) {
  id_ = id;
  coordinates_ = coord;
  stress_ = stress;
}
