#ifndef MPM_POINT_GEN_MESH_H_
#define MPM_POINT_GEN_MESH_H_

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

#include <boost/filesystem.hpp>
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

  //! Get material properties from json object
  void assign_material_properties(
      const std::shared_ptr<MaterialProperties>& material);

  //! Compute stress of the material points
  void compute_stresses();

  //! Return the total number of vertices
  unsigned nvertices() const { return nvertices_; }

  //! Return a vector of coordinates
  std::vector<Eigen::VectorXd> coordinates();

  //! Return a vector of stresses
  std::vector<Eigen::VectorXd> stress();

  //! Write coordinates
  void write_coordinates(boost::filesystem::path coordinates_filename);

  //! Write stresses
  void write_stresses(boost::filesystem::path stresses_filename);

  //! Write initial element volumes
  void write_volumes(boost::filesystem::path volumes_filename);

  //! Write .vtk files for initial stresses (include coordinates as well)
  void write_vtk_stresses(boost::filesystem::path stress_vtk_filename);

  //! Write .vtk files for mesh
  void write_vtk_mesh(boost::filesystem::path mesh_vtk_filename);

 protected:
  //! Total number of vertices
  unsigned nvertices_{std::numeric_limits<unsigned>::max()};

  //! Number of pgauss oints per coordinate
  unsigned ngauss_points_{std::numeric_limits<unsigned>::max()};

  //! Total number of material points generated
  unsigned npoints_{0};

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
