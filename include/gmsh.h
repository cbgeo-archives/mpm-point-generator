#ifndef MPM_GMSH_H_
#define MPM_GMSH_H_

#include <array>
#include <fstream>
#include <iostream>
#include <limits>
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

  //! \brief Read and return elements
  //! \details returned vector stores elements read in from gmsh file
  void read_elements(const std::string& filename);

  //! Text output
  void compute_stresses();

  //! call total number of vertices generated
  unsigned nvertices() const { return nvertices_; }

  //! call the vector containing shared pointer of vertices
  std::vector<std::shared_ptr<Point<3>>> vertices() const { return vertices_; }

  //! call the vector containing elements
  std::vector<std::shared_ptr<Point<3>>> elements() const { return elements_; }

  //! call the vector containing stress
  std::vector<std::array<double, 6>> stress() const { return stress_; }

 private:
  //! the total number of points generated
  unsigned nvertices_;

  //! Vertices vector
  std::vector<std::shared_ptr<Point<3>>> vertices_;

  //! Elements vector
  std::vector<std::shared_ptr<Point<3>>> elements_;

  //! Stress vector in Voigt Notation
  //! id  sig_x  sig_y  sig_z  tau_yz  tau_zx  tau_xy
  std::vector<std::array<double, 6>> stress_;
};

#include "gmsh.tcc"

#endif  // MPM_GMSH_H_
