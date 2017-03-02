#ifndef MPM_POINT_GEN_INPUT_H
#define MPM_POINT_GEN_INPUT_H

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <sstream>
#include <vector>

#include "point.h"

//! Class to input coordinates from text file
template <unsigned Tdim>
class Input {

 public:
  //! \brief Read and return vertices
  //! \details returned vector stores vertices read in from gmsh file
  std::vector<std::shared_ptr<Point<Tdim>>> read_vertices(
      const std::string& filename);

  //! \brief Read and return elements
  //! \details returned vector stores vertices read in from gmsh file
  std::vector<std::shared_ptr<Point<Tdim>>> read_elements(
      const std::string& filename);

 private:
};

#endif  // MPM_POINT_GEN_INPUT_H
