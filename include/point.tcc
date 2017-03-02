#include "point.h"
//! \brief Constructor with id and coordinates
//! \param[in] id index of the vertex
//! \param[in] coord Coordinates of the point
template <unsigned Tdim>
Point<Tdim>::Point(unsigned id, const std::array<double, Tdim>& coord)
    : id_{id} {
  coordinates_ = coord;
}
