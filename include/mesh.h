#ifndef MPM_POINT_GEN_MESH_H_
#define MPM_POINT_GEN_MESH_H_

#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <vector>

#include "point.h"

//! \brief Abstract class for handling mesh
template <unsigned Tdim, unsigned Tvertices>
class Mesh {

 public:
  //! \brief constructor for a mesh class
  // Mesh() {
  // };

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

  //! call total number of vertices generated
  virtual unsigned nvertices() const { return 0; }

  //! Return a vector of material points
  virtual std::vector<std::shared_ptr<Point<Tdim>>> material_points() {
    return std::vector<std::shared_ptr<Point<Tdim>>>{};
  }

  //! Return a map of mesh element vertices
  virtual std::map<unsigned, std::array<double, Tdim>> vertices() const {
    return std::map<unsigned, std::array<double, Tdim>>{};
  }

  //! Return a map of element id & vertices id
  virtual std::map<unsigned, std::array<double, Tvertices>> elements() const {
    return std::map<unsigned, std::array<double, Tvertices>>{};
  }

  //! Return a vector of stresses
  virtual std::vector<std::array<double, 6>> stress() const {
    return std::vector<std::array<double, 6>>{};
  }

 protected:
  //! Total number of vertices
  unsigned nvertices_;

  std::vector<std::shared_ptr<Point<Tdim>>> materialpoints_;

  //! Stress vector in Voigt Notation
  //! $\sigma_{xx}$ $\sigma_{yy}$ $\sigma_{zz}$
  //! $\tau_{yz}$ $\tau_{zx}$ $\tau_{xy}$
  std::vector<std::array<double, 6>> stress_;

  //! Map to store id and vertices coordinates
  std::map<unsigned, std::array<double, Tdim>> vertices_;

  //! Map to store element ID and vertices ID
  std::map<unsigned, std::array<double, Tvertices>> elements_;

  std::map<unsigned, std::array<double, Tdim * Tvertices>> elementcoordinates_;
};
#endif  // MPM_POINT_GEN_MESH_H_
