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
class GMSH : public Mesh {

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
  unsigned nvertices() const { return nvertices_; }

  //! Return a vector of material points
  std::vector<std::shared_ptr<Point<Tdim>>> material_points() {
    return materialpoints_;
  }

  //! Return a map of mesh element vertices
  std::map<double, std::array<unsigned, Tdim>> vertices() const {
    return vertices_;
  }

  //! Return a map of element id & vertices id
  std::map<double, std::array<unsigned, Tvertices>> elements() const {
    return elements_;
  }

  //! Return a vector of stresses
  std::vector<std::array<double, 6>> stress() const { return stress_; }

 private:
  //! Total number of vertices
  unsigned nvertices_;

  std::vector<std::shared_ptr<Point<Tdim>>> materialpoints_;

  //! Stress vector in Voigt Notation
  //! $\sigma_{xx}$ $\sigma_{yy}$ $\sigma_{zz}$ $\tau_{yz}$ $\tau_{zx}$
  //! $\tau_{xy}$
  std::vector<std::array<double, 6>> stress_;

  //! Map to store id and vertices coordinates
  std::map<double, std::array<double, Tdim>> vertices_;

  //! Map to store element ID and vertices ID
  std::map<double, std::array<double, Tvertices>> elements_;
  std::map<double, std::array<double, Tdim * Tvertices>> elementcoordinates_;
};

#include "gmsh.tcc"

#endif  // MPM_POINT_GEN_GMSH_H_
