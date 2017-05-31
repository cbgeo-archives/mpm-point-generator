#ifndef MPM_POINT_GEN_MESH_H_
#define MPM_POINT_GEN_MESH_H_

#include <array>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <vector>

//! \brief Abstract class for handling mesh
class Mesh {

 public:
  //! Read vertices from mesh
  virtual void read_vertices(const std::string& filename) = 0;

  //! Compute initial stresses for material points
  virtual void compute_stresses() = 0;
};
#endif  // MPM_POINT_GEN_MESH_H_
