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

  //! call total number of vertices generated
  unsigned nvertices() const { return Mesh<Tdim, Tvertices>::nvertices_; }

  //! Return a vector of material points
  std::vector<std::shared_ptr<Point<Tdim>>> material_points() {
    return Mesh<Tdim, Tvertices>::materialpoints_;
  }

  //! Return a map of mesh element vertices
  std::map<unsigned, std::array<double, Tdim>> vertices() const {
    return Mesh<Tdim, Tvertices>::vertices_;
  }

  //! Return a map of element id & vertices id
  std::map<unsigned, std::array<double, Tvertices>> elements() const {
    return Mesh<Tdim, Tvertices>::elements_;
  }

  //! Return a vector of stresses
  std::vector<std::array<double, 6>> stress() const {
    return Mesh<Tdim, Tvertices>::stress_;
  }
};

#include "gmsh.tcc"

#endif  // MPM_POINT_GEN_GMSH_H_
