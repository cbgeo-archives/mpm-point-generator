#ifndef MPM_MESH_H_
#define MPM_MESH_H_
#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

//! \brief Abstract class for reading files for mesh
class Mesh {

 public:
  //! Read from file
  virtual void get_vertices(const std::string& filename) = 0;

  //! Text output
  virtual void output_vertices() = 0;

  //! Text output
  virtual void output_stresses() = 0;

};
#endif  // MPM_MESH_H_
