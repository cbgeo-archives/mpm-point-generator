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
  //! \param[in] json input file name
  explicit IO(const std::string& json_file) : json_filename_{json_file} {

    //! Check if json file is present
    std::ifstream inputFile(json_filename_);
    inputFile.exceptions(std::ifstream::badbit);

    //! Read json file and store to private variables
    json j;
    inputFile >> j;
    mesh_filename_ = j["mesh_file"].get<std::string>();
    output_directory_ = j["output_directory"].get<std::string>();

    //! Check if mesh file is present
    std::ifstream meshfile;
    meshfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
      meshfile.open(mesh_filename_);
    } catch (const std::ifstream::failure& except) {
      std::cerr << "Exception opening/reading mesh file";
    }
    meshfile.close();

    //! Material point and stresses output file
    material_points_filename_ = output_directory_ + "material_points.txt";
    stress_filename_ = output_directory_ + "initial_stresses.txt";
  }

  //! Write vertices
  void write_point_coordinates(
      const std::vector<std::shared_ptr<Point<Tdim>>>& points);

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
