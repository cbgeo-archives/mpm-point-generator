#ifndef MPM_POINT_GEN_IO_H_
#define MPM_POINT_GEN_IO_H_

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <utility>
#include <vector>

#include <eigen3/Eigen/Dense>

#include "material_points.h"
#include "mesh.h"

#include "json.hpp"

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
    material_properties_filename_ =
        j["material_properties_file"].get<std::string>();
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

    //! Check if material_properties file is present
    std::ifstream materialPropertiesfile;
    materialPropertiesfile.exceptions(std::ifstream::failbit |
                                      std::ifstream::badbit);
    try {
      materialPropertiesfile.open(material_properties_filename_);
    } catch (const std::ifstream::failure& except) {
      std::cerr << "Exception opening/reading material properties file";
    }
    materialPropertiesfile.close();

    //! Material point and stresses output file
    material_points_filename_ = output_directory_ + "material_points.txt";
    stress_filename_ = output_directory_ + "initial_stresses.txt";
  }

  //! Write vertices
  void write_material_points(
      const std::vector<std::shared_ptr<Point<Tdim>>>& materialpoints);

  //! Write stresses
  void write_stresses(const std::vector<Eigen::VectorXd>& stresses);

  //! Return mesh file name
  std::string mesh_file_name() const { return mesh_filename_; }

  //! Return material properties file name
  std::string material_properties_name() const {
    return material_properties_filename_;
  }

 private:
  //! Input json file
  std::string json_filename_;

  //! Input mesh file name
  std::string mesh_filename_;

  //! Input material properties file name
  std::string material_properties_filename_;

  //! Output directory
  std::string output_directory_;

  //! File name of vertices
  std::string material_points_filename_;

  //! Filename of material point stresses
  std::string stress_filename_;
};

#include "io.tcc"

#endif  // MPM_POINT_GEN_IO_H_
