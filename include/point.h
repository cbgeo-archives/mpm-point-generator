#ifndef MPM_MESH_POINT_H_
#define MPM_MESH_POINT_H_

#include <array>

//! \brief Point class to store coordinates
template <unsigned Pdim>
class Point {
public:
  //! Constructor with id and coordinates
  Point(unsigned id, const std::array<double, Pdim> &coord);

  //! Returns the id of the point
  unsigned id() const { return id_; }

  //! Returns coordinates of the point
  std::array<double, Pdim> coordinates() const { return coordinates_; }

private:
  //! Index of the material point
  unsigned id_;
  //! Coordinates
  std::array<double, Pdim> coordinates_;
};

#endif // MPM_MESH_POINT_H_
