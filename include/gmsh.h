#ifndef MPM_POINT_GEN_GMSH_H_
#define MPM_POINT_GEN_GMSH_H_

#include <array>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <vector>

#include <Eigen/Dense>

#include "mesh.h"
#include "point.h"

//! \brief Generate Material Points from GMSH file
template <unsigned Tdim, unsigned Tvertices>
class GMSH : public Mesh<Tdim, Tvertices> {

 public:
  //! Read GMSH file
  void read_mesh(const std::string& filename);
  
  //! Read vertices in GMSH
  void read_vertices(const std::string& filename);

  //! Read elements in GMSH
  void read_elements(const std::string& filename);

  //! Store element id and vertices coordinates as map
  void store_element_vertices();

  //! Compute material points from element coordinate map
  void compute_material_points();

  //! Compute stresses
  void compute_stresses();

 private:
  //! Total number of vertices
  using Mesh<Tdim, Tvertices>::nvertices_;
  //! Map of vertex id to its coordinates
  using Mesh<Tdim, Tvertices>::vertices_;
  //! Map of elemnt id to its vertices
  using Mesh<Tdim, Tvertices>::elements_;
  //! Map of element ids to vertices coordinates
  using Mesh<Tdim, Tvertices>::elementcoordinates_;
  //! Vector of material points
  using Mesh<Tdim, Tvertices>::materialpoints_;
  //! Vector of material point stresses
  using Mesh<Tdim, Tvertices>::stress_;
};

#include "gmsh.tcc"

#endif  // MPM_POINT_GEN_GMSH_H_
