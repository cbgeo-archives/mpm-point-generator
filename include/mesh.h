#ifndef MPM_POINT_GEN_MESH_H_
#define MPM_POINT_GEN_MESH_H_

#include <Eigen/Dense>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <vector>

#include "point.h"

//! \brief Abstract class for handling mesh
//! \tparam Tdim Dimension of the mesh
//! \tparam Tvertices Number of vertices in an element
template <unsigned Tdim, unsigned Tvertices>
class Mesh {

 public:
  //! Read vertices from mesh
  virtual void read_mesh(const std::string& filename) = 0;

  //! Compute material point location
  virtual void compute_material_points() = 0;

  //! Compute initial stresses for material points
  virtual void compute_stresses() = 0;

  //! Get vector of stresses
  std::vector<Eigen::VectorXd> stress() {

    std::vector<Eigen::VectorXd> stress;
    //! Loop through the points to get the stresses
    for (const auto& materialpoint : materialpoints_) {
      stress.emplace_back(materialpoint->stress());
    }

    return stress;
  }

  //! Return a vector of material points
  std::vector<std::shared_ptr<Point<Tdim>>> material_points() {
    return materialpoints_;
  }

  //! Return a map of mesh element vertices
  std::map<unsigned, std::array<unsigned, Tdim>> vertices() const {
    return vertices_;
  }

  //! Return a map of element id & vertices id
  std::map<unsigned, std::array<unsigned, Tvertices>> elements() const {
    return elements_;
  }

  //! Return the total number of vertices
  unsigned nvertices() const { return nvertices_; }

 protected:
  //! Total number of vertices
  unsigned nvertices_;

  //! Map to store id and vertices coordinates
  std::map<unsigned, std::array<double, Tdim>> vertices_;

  //! Map to store element ID and vertices ID
  std::map<unsigned, std::array<double, Tvertices>> elements_;

  //! Map to store element ID and vertices coordinates
  std::map<unsigned, std::array<double, Tdim * Tvertices>> elementcoordinates_;

  //! Container for storing material points
  std::vector<std::shared_ptr<Point<Tdim>>> materialpoints_;
};
#endif  // MPM_POINT_GEN_MESH_H_
