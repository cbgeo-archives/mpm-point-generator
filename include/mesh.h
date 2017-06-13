#ifndef MPM_POINT_GEN_MESH_H_
#define MPM_POINT_GEN_MESH_H_

#include "point.h"
#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <map>
#include <sstream>
#include <vector>

//! \brief Abstract class for handling mesh
template <unsigned Tdim, unsigned Tvertices>
class Mesh {

 public:
  //! Read vertices from mesh
  virtual void read_vertices(const std::string& filename) = 0;

  //!
  virtual void read_elements(const std::string& filename) = 0;

  //!
  virtual void compute_material_points() = 0;

  //! Compute initial stresses for material points
  virtual void compute_stresses() = 0;

  //! Return a vector of material points
  std::vector<std::shared_ptr<Point<Tdim>>> material_points() {
    return materialpoints_;
  }

  //! Return a vector of stresses
  std::vector<std::array<double, Tdim * 2>> stresses() const {
    return stress_;
  }


    //! Return a map of mesh element vertices
    std::map<unsigned , std::array<unsigned, Tdim>> vertices() const {
        return vertices_;
    }

    //! Return a map of element id & vertices id
    std::map<unsigned, std::array<unsigned, Tvertices>> elements() const {
        return elements_;
    }

protected:

    //! Stress vector in Voigt Notation
    //! $\sigma_{xx}$ $\sigma_{yy}$ $\sigma_{zz}$ $\tau_{yz}$ $\tau_{zx}$
    //! $\tau_{xy}$
    std::vector<std::array<double, Tdim * 2>> stress_;

    //! Map to store id and vertices coordinates
    std::map<double, std::array<double, Tdim>> vertices_;

    //! Map to store element ID and vertices ID
    std::map<double, std::array<double, Tvertices>> elements_;

    //! Map to store element ID and vertices coordinates
    std::map<double, std::array<double, Tdim * Tvertices>> elementcoordinates_;

  //! Container for storing material points
  std::vector<std::shared_ptr<Point<Tdim>>> materialpoints_;

};
#endif  // MPM_POINT_GEN_MESH_H_
