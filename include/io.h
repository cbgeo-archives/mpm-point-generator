#ifndef MPM_POINT_GEN_IO_H_
#define MPM_POINT_GEN_IO_H_

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

#include "tclap/CmdLine.h"
#include <boost/filesystem.hpp>
#include <eigen3/Eigen/Dense>

#include "material_points.h"
#include "mesh.h"

//! Alias for JSON
#include "json.hpp"
using json = nlohmann::json;

//! \brief Input/Output handler
class IO {
 public:
  //! Constructor with json input file
  //! Get mesh_filename and output_directory
  //! \param[in] input directory
  //! \param[in] json input file name
  explicit IO(int arg_c, char** arg_v);

  //! Write coordinates
  void write_coordinates(const std::vector<Eigen::VectorXd>& coordinates);

  //! Write stresses
  void write_stresses(const std::vector<Eigen::VectorXd>& stresses);

  //! Return the number of points per coordinate
  unsigned ngauss_points() const { return ngauss_points_; }

  //! Return json object for material properties
  json material_properties() const { return json_material_properties_; }

  //! Return mesh file name
  std::string mesh_file_name() const { return mesh_filename_; }

  //! Create output file names
  boost::filesystem::path output_file(const std::string& attribute,
                                      const std::string& file_extension);

  //! Write initial element volumes
  void write_volumes(const std::map<unsigned, double>& volumes);

 private:
  //! Input directory
  std::string working_dir_;

  //! Input json object
  json json_;

  //! Material properties json object
  json json_material_properties_;

  //! Input mesh file name
  std::string mesh_filename_;

  //! Number of gauss points per coordinate
  unsigned ngauss_points_{0};
};
#endif  // MPM_POINT_GEN_IO_H_
