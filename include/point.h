#ifndef MPM_MESH_POINT_H_
#define MPM_MESH_POINT_H_

#include <array>

//! \brief Point class to store vertex coordinates & id
//! \tparam Tdim dimension
template <unsigned Tdim>
class Point {
 public:
  //! Constructor with id and coordinates
  //! \param[in] id index of the vertex
  //! \param[in] coord Coordinates of the point
  //! \param[in] stress Voigt stress of the point
  Point(unsigned id, const std::array<double, Tdim>& coord,
        const std::array<double, Tdim * 2>& stress) {
    id_ = id;
    coordinates_ = coord;
    stress_ = stress;
  }

  //! Return the id of the point
  unsigned id() const { return id_; }

  //! Return coordinates of the point
  std::array<double, Tdim> coordinates() const { return coordinates_; }

  //! Return stresses of the point
  std::array<double, Tdim * 2> stress() const { return stress_; }

 private:
  //! Index
  unsigned id_;
  //! Coordinates
  std::array<double, Tdim> coordinates_;
  //! Stress
  std::array<double, Tdim * 2> stress_;
};

#endif  // MPM_MESH_POINT_H_
