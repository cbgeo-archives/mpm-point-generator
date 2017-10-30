#ifndef MPM_POINT_GEN_IO_H_
#define MPM_POINT_GEN_IO_H_

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

#include <boost/filesystem.hpp>
#include <eigen3/Eigen/Dense>

#include "material_points.h"
#include "mesh.h"

//! Alias for JSON
#include "json.hpp"
using json = nlohmann::json;

//! \brief Input/Output handler
//! \tparam Tdim dimension
template <unsigned Tdim>
class IO {
 public:
  //! Constructor with json input file
  //! Get mesh_filename and output_directory
  //! \param[in] input directory
  //! \param[in] json input file name
  explicit IO(const std::string& file_directory, const std::string& json_file);

  //! Write coordinates
  void write_coordinates(const std::vector<Eigen::VectorXd>& coordinates);

  //! Write stresses
  void write_stresses(const std::vector<Eigen::VectorXd>& stresses);

  //! Return the number of points per coordinate
  unsigned ngauss_points() const { return ngauss_points_; }

  //! Return json object for material properties
  json material_properties() const { return json_["material_properties"]; }

  //! Return mesh file name
  std::string mesh_file_name() const { return mesh_filename_; }

  //! Create output file names
  boost::filesystem::path output_file(const std::string& attribute,
                                      const std::string& file_extension);

  //! Write initial element volumes
  void write_volumes(const std::map<unsigned, double>& volumes);

  //! Write .vtk files for initial stresses (include coordinates as well)
  void write_vtk_stresses(const std::vector<Eigen::VectorXd>& coordinates,
                          const std::vector<Eigen::VectorXd>& stresses);

  //! Write .vtk files for mesh
  void write_vtk_mesh(const std::vector<Eigen::VectorXd>& vertices,
                      const std::vector<Eigen::VectorXd>& elements);

 private:
  //! Input directory
  std::string file_directory_;

  //! Input json path file name
  std::string json_filename_;

  //! Input json object
  json json_;

  //! Input mesh file name
  std::string mesh_filename_;

  //! File name of material points
  boost::filesystem::path material_points_filename_;

  //! Filename of material point stresses
  boost::filesystem::path stress_filename_;

  //! Filename of material point volumes
  boost::filesystem::path volume_filename_;

  //! .vtk filename of material point stresses
  boost::filesystem::path stress_vtk_filename_;

  //! .vtk filename of Mesh
  boost::filesystem::path mesh_vtk_filename_;

  //! Number of gauss points per coordinate
  unsigned ngauss_points_{0};
};

#include "io.tcc"

#endif  // MPM_POINT_GEN_IO_H_
