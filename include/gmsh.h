#ifndef MPM_POINT_GEN_GMSH_H_
#define MPM_POINT_GEN_GMSH_H_

#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <utility>
#include <vector>

#include <eigen3/Eigen/Dense>

#include "material_points.h"
#include "mesh.h"
#include "json.hpp"

//! Short alias for convenience
using json = nlohmann::json;

//! \brief Generate Material Points from GMSH file
template <unsigned Tdim, unsigned Tvertices>
class GMSH : public Mesh<Tdim, Tvertices> {

 public: 
  //! Read GMSH file
  void read_mesh(const std::string& filename);

  //! Read keyword in GMSH
  void read_keyword(std::ifstream& file, const std::string& keyword);

  //! Read vertices in GMSH
  void read_vertices(std::ifstream& file);

  //! Read elements in GMSH
  void read_elements(std::ifstream& file);

  //! Store element id and vertices coordinates as map
  void store_element_vertices();

  //! Compute material points from element coordinate map
  void compute_material_points();

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
};

#include "gmsh.tcc"

#endif  // MPM_POINT_GEN_GMSH_H_
