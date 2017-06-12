#ifndef MPM_POINT_GEN_MESH_H_
#define MPM_POINT_GEN_MESH_H_

#include "point.h"
#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

//! \brief Abstract class for handling mesh
template <unsigned Tdim>
class Mesh {

 public:
  //! Read vertices from mesh
  virtual void read_vertices(const std::string& filename) = 0;

  //!
  virtual void read_elements(const std::string& filename) = 0;

  //!
  virtual void compute_material_points() = 0;

  //! Compute initial stresses for material points
  virtual void compute_stresses() = 0;

  //! Return a vector of material points
  std::vector<std::shared_ptr<Point<Tdim>>> write_material_points() {
    return materialpoints_;
  }

  //! Return a vector of stresses
  std::vector<std::array<double, Tdim * 2>> write_stresses() const {
    return stress_;
  }

  //! Container for storing material points
  std::vector<std::shared_ptr<Point<Tdim>>> materialpoints_;

  //! Container for storing stresses
  std::vector<std::array<double, Tdim * 2>> stress_;

 private:
};
#endif  // MPM_POINT_GEN_MESH_H_
