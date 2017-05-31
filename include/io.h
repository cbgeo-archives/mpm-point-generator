#ifndef MPM_POINT_GEN_IO_H_
#define MPM_POINT_GEN_IO_H_

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "mesh.h"
#include "point.h"

//! \brief Input/Output handler
class IO {
 public:
  //! Constructor with input file
  //! \param[in] mesh_file Input mesh file name
  explicit IO(const std::string& mesh_file)
      : mesh_file_name_{mesh_file} {
    //! Material point and stresses
    outputfilename_vertex_ = "material_points.txt";
    outputfilename_stress_ = "initial_stresses.txt";
  }

  //! Write vertices
  void write_vertices(const std::vector<std::shared_ptr<Point<3>>>& vertices);

  //! Write stresses
  void write_stresses(const std::vector<std::array<double, 6>>& stress);

  //! Return mesh file name
  std::string mesh_file_name() const { return mesh_file_name_; }

 private:
  //! Input mesh file name
  std::string mesh_file_name_;

  //! File name of vertices
  std::string outputfilename_vertex_;

  //! Filename of material point stresses
  std::string outputfilename_stress_;
};

#include "io.tcc"

#endif  // MPM_POINT_GEN_IO_H_
