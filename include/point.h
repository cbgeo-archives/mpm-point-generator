#ifndef MPM_MESH_POINT_H_
#define MPM_MESH_POINT_H_

#include <array>

//! \brief Point class to store vertex coordinates & id
//! \tparam Tdim dimension
template <unsigned Tdim>
class Point {
 public:
  //! \brief Constructor with id and coordinates
  Point(unsigned id, const std::array<double, Tdim>& coord);

  //! Returns the id of the vertex
  unsigned id() const { return id_; }

  //! Returns coordinates of the vertex
  std::array<double, Tdim> coordinates() const { return coordinates_; }

 private:
  //! Index
  unsigned id_;
  //! Coordinates
  std::array<double, Tdim> coordinates_;
};

#include "point.tcc"

#endif  // MPM_MESH_POINT_H_
