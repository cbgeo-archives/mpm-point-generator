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
using Json = nlohmann::json;

//! \brief Abstract class for handling mesh
//! \tparam Tdim Dimension of the mesh
//! \tparam Tvertices Number of vertices in an element
template <unsigned Tdim, unsigned Tvertices>
class Mesh {

 public:
  //! Read vertices from mesh
  virtual void read_mesh(const std::string& filename) = 0;

  //! Compute material point location
  virtual void generate_material_points(unsigned ngauss_points) = 0;

  //! Get material properties from json object
  void assign_material_properties(
      std::vector<std::unique_ptr<MaterialProperties>> material);

  //! Compute stress of the material points
  void compute_stresses();

  //! Return the total number of vertices
  unsigned nvertices() const { return nvertices_; }

  //! Write coordinates
  void write_coordinates(boost::filesystem::path coordinates_filename);

  //! Write stresses
  void write_stresses(boost::filesystem::path stresses_filename);

  //! Write initial element volumes
  void write_volumes(boost::filesystem::path volumes_filename);

  //! Write .vtk files for point
  void write_vtk_points(boost::filesystem::path mesh_vtk_filename);

  //! Write .vtk files for initial stresses (include coordinates as well)
  void write_vtk_stresses(boost::filesystem::path stress_vtk_filename);

  //! Write .vtk files for mesh
  void write_vtk_mesh(boost::filesystem::path mesh_vtk_filename);

  //! Return begin iterator of material points_
  typename std::vector<std::unique_ptr<MaterialPoints<Tdim>>>::const_iterator
      material_points_begin() const {
    return materialpoints_.begin();
  }

  //! Return end iterator of material points_
  typename std::vector<std::unique_ptr<MaterialPoints<Tdim>>>::const_iterator
      material_points_end() const {
    return materialpoints_.end();
  }

 protected:
  //! Total number of vertices
  unsigned nvertices_{std::numeric_limits<unsigned>::max()};

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
