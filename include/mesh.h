#ifndef MPM_POINT_GEN_MESH_H_
#define MPM_POINT_GEN_MESH_H_

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <utility>
#include <sstream>
#include <vector>

#include <eigen3/Eigen/Dense>

#include "point.h"
#include "points.h"

//! \brief Abstract class for handling mesh
//! \tparam Tdim Dimension of the mesh
//! \tparam Tvertices Number of vertices in an element
template <unsigned Tdim, unsigned Tvertices>
class Mesh {

 public:
  //! Read vertices from mesh
  virtual void read_mesh(const std::string& filename) = 0;

  //! Compute material point location
  virtual void compute_material_points(const double density, const double k0) = 0;

  //! Get vector of stresses
  std::vector<Eigen::VectorXd> stress() {

    std::vector<Eigen::VectorXd> stress;
    //! Loop through the points to get the stresses
    for (const auto& materialpoint : materialpoints_.get_points()) {
      stress.emplace_back(materialpoint.first->stress());
    }

    return stress;
  }

  //! Return a vector of material points
  Points<Tdim> material_points() {
    return materialpoints_;
  }

  //! Return the total number of vertices
  unsigned nvertices() const { return nvertices_; }

 protected:
  //! Total number of vertices
  unsigned nvertices_;

  //! Map to store id and vertices coordinates
  std::map<unsigned, Eigen::VectorXd> vertices_;

  //! Map to store element ID and vertices ID
  std::map<unsigned, Eigen::VectorXd> elements_;

  //! Map to store element ID and vertices coordinates
  std::map<unsigned, Eigen::VectorXd> elementcoordinates_;

  //! Container for storing material points
  Points<Tdim> materialpoints_;
};
#endif  // MPM_POINT_GEN_MESH_H_
