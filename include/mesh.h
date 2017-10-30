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

#include "element.h"
#include "material_points.h"

//! Alias for JSON
#include "json.hpp"
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
  virtual void compute_material_points(unsigned ngauss_points) = 0;

  //! Return a vector of coordinates
  std::vector<Eigen::VectorXd> coordinates();

  //! Return a vector of stresses
  std::vector<Eigen::VectorXd> stress();

  //! Return a vector of vertices of the mesh
  std::vector<Eigen::VectorXd> vertices();

  //! Return a vector of vertice number of element
  std::vector<Eigen::VectorXd> elements();

  //! Get material properties from json object
  void assign_material_properties(
      const std::shared_ptr<MaterialProperties>& material);

  //! Compute stress of the material points
  void compute_stresses();

  //! Return the total number of vertices
  unsigned nvertices() const { return nvertices_; }

  //!\retval Map of element volume and id
  std::map<unsigned, double> calculate_volumes();

 protected:
  //! Total number of vertices
  unsigned nvertices_{std::numeric_limits<unsigned>::max()};

  //! Number of pgauss oints per coordinate
  unsigned ngauss_points_{std::numeric_limits<unsigned>::max()};

  //! Map to store id and vertices coordinates
  std::map<unsigned, Eigen::VectorXd> vertices_;

  //! Vector to store element id and vertices id
  std::vector<std::unique_ptr<Element>> elements_;

  //! Map to store element id and vertices coordinates
  std::map<unsigned, Eigen::VectorXd> elementcoordinates_;

  //! Vector of material points
  std::vector<std::unique_ptr<MaterialPoints<Tdim>>> materialpoints_;
};

#include "mesh.tcc"

#endif  // MPM_POINT_GEN_MESH_H_
