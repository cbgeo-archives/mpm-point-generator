#ifndef MPM_GMSH_H_
#define MPM_GMSH_H_

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "mesh.h"
#include "point.h"

//! \brief class to read gmsh file, child of Mesh class
//! \details Stores id and coordinates in a vector

class GMSH : public Mesh {

 public:
  //! Read from file
  void get_vertices(const std::string& filename);

  //! Text output
  void output_vertices();

  //! Text output
  void output_stresses();

  void output_3d_stresses();

 private:
  //! Vertices vector
  std::vector<std::shared_ptr<Point<3>>> vertices_;
};

#include "gmsh.tcc"

#endif  // MPM_GMSH_H_
