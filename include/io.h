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

#include "tclap/CmdLine.h"
//! Alias for JSON
#include "json.hpp"
using json = nlohmann::json;

#include "material_points.h"
#include "mesh.h"

//! \brief Input/Output handler
class IO {
 public:
  //! Constructor with argc and argv
  IO(int argc, char** argv);

  //! Return the number of points per coordinate
  unsigned ngauss_points() const { return ngauss_points_; }

  //! Return json object for material properties
  json material_properties() const { return json_material_properties_; }

  //! Return mesh file name
  std::string mesh_file_name() const { return mesh_filename_; }

  //! Create output file names
  boost::filesystem::path output_file(const std::string& attribute,
                                      const std::string& file_extension);

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
