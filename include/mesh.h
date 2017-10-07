#ifndef MPM_POINT_GEN_MESH_H_
#define MPM_POINT_GEN_MESH_H_

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

#include <eigen3/Eigen/Dense>

#include "json.hpp"
#include "material_points.h"

//! Short alias for convenience
using json = nlohmann::json;

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

  //! Return a vector of coordinates
  std::vector<Eigen::VectorXd> coordinates();

  //! Return a vector of stresses
  std::vector<Eigen::VectorXd> stress();

  //! Get material properties from json object
  void add_material_properties(const json& jsonfile);

  //! Compute stress of the material points
  void compute_stress();

  //! Return the total number of vertices
  unsigned nvertices() const { return nvertices_; }

 protected:
  //! Total number of vertices
  unsigned nvertices_;

  //! Number of materials being used
  unsigned nmaterials_;

  //! Map to store id and vertices coordinates
  std::map<unsigned, Eigen::VectorXd> vertices_;

  //! Map to store element ID and vertices ID
  std::map<unsigned, Eigen::VectorXd> elements_;

  //! Map to store element ID and vertices coordinates
  std::map<unsigned, Eigen::VectorXd> elementcoordinates_;

  //! Container for storing material points
  std::vector<std::shared_ptr<MaterialPoints<Tdim>>> materialpoints_;
};

#include "mesh.tcc"

#endif  // MPM_POINT_GEN_MESH_H_
