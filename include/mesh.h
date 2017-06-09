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
  //! Read vertices in GMSH
  virtual void read_vertices(const std::string& filename) = 0;

  //! Read elements in GMSH
  virtual void read_elements(const std::string& filename) = 0;

  //! Store element id and vertices coordinates as map
  virtual void store_element_vertices() = 0;

  //! Compute material points from element coordinate map
  virtual void compute_material_points() = 0;

  //! Compute stresses
  virtual void compute_stresses() = 0;

};
#endif  // MPM_POINT_GEN_MESH_H_
