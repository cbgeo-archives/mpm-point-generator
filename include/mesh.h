#ifndef MPM_MESH_H_
#define MPM_MESH_H_
#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "point.h"

//! \brief Template class to read gmsh file
//! \details Stores id and coordinates in vector
//! \tparam Tdim Element Type
template <unsigned Tdim>
class Mesh {

 public:
  //! Read from file
  void get_vertices(const std::string& filename);

  //! Text output to check contents of vertices vector match input
  void output_vertices();

  //! Read from file
  void get_elements(const std::string& filename);

  //! Text output to check contents of element vector match input
  void output_elements();

 private:
  //! Vertices vector
  std::vector<std::shared_ptr<Point<3>>> vertex_;

  //! Element vector
  std::vector<std::shared_ptr<Point<Tdim>>> element_;
};
#endif  // MPM_MESH_H_
