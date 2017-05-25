
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "mesh.h"
#include "point.h"
#include "initStress.h"

//! \brief class to read gmsh file, child of Mesh class
//! \details Stores id and coordinates in a vector

class GMSH : public Mesh {

 public:
  //! Read from file
  void get_vertices(const std::string& filename);

  //! Text output
  void output_vertices();

  //! Text output
  void output_stresses();

 private:
  //! Vertices vector
  std::vector<std::shared_ptr<Point<3>>> vertices_;

  //! stress_ is the array of stresses in Voigt Notation
  //! sig_x  sig_y  sig_z  tau_yz  tau_zx  tau_xy
  std::vector<std::unique_ptr<InitStress>> stresses_;
};
