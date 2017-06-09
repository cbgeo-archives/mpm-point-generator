#ifndef MPM_MESH_POINT_H_
#define MPM_MESH_POINT_H_

#include <array>

//! \brief Point class to store vertex coordinates & id
//! \tparam Dimension
template <unsigned Tdim>
class Point {
 public:
  //! \brief Constructor with id and coordinates
  Point(unsigned id, const std::array<double, Tdim>& coord,
        const std::array<double, 6>& stress);

  //! Returns the id of the vertex
  unsigned id() const { return id_; }

  //! Returns coordinates of the vertex
  std::array<double, Tdim> coordinates() const { return coordinates_; }

  //! Returns initial stress of the vertex
  std::array<double, 6> stress() const { return stress_; }

 private:
  //! Index
  unsigned id_;

  //! Coordinates
  std::array<double, Tdim> coordinates_;

  //! Stress vector in Voigt Notation
  //! $\sigma_{xx}$ $\sigma_{yy}$ $\sigma_{zz}$ $\tau_{yz}$ $\tau_{zx}$
  //! $\tau_{xy}$
  //! Note that positive is tension
  std::array<double, 6> stress_;
};

#include "point.tcc"

#endif  // MPM_MESH_POINT_H_
