#ifndef MPM_POINT_GEN_IO_H_
#define MPM_POINT_GEN_IO_H_

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

#include <eigen3/Eigen/Dense>

#include "json.hpp"
#include "material_points.h"
#include "mesh.h"

//! Short alias for convenience
using json = nlohmann::json;

//! \brief Input/Output handler
//! \tparam Tdim dimension
template <unsigned Tdim>
class IO {
 public:
  //! Constructor with json input file
  //! Get mesh_filename and output_directory
  //! \param[in] json input file name
  explicit IO(const std::string& json_file);

  //! Write vertices
  void write_point_coordinates(const std::vector<Eigen::VectorXd>& coordinates);

  //! Write stresses
  void write_stresses(const std::vector<Eigen::VectorXd>& stresses);

  //! Return input json file for material properties
  std::string json_filename() const { return json_filename_; }

  //! Return mesh file name
  std::string mesh_file_name() const { return mesh_filename_; }

 private:
  //! Input json file
  std::string json_filename_;

  //! Input mesh file name
  std::string mesh_filename_;

  //! Output directory
  std::string output_directory_;

  //! File name of vertices
  std::string material_points_filename_;

  //! Filename of material point stresses
  std::string stress_filename_;
};

#include "io.tcc"

#endif  // MPM_POINT_GEN_IO_H_
