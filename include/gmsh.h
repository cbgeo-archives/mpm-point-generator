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
  void output_vertices(const std::string& outputfilename);

  //! Text output
  void output_stresses(const std::string& outputfilename);

 private:
  //! the total number of points generated
  unsigned tot_points_;

  //! Vertices vector
  std::vector<std::shared_ptr<Point<3>>> vertices_;

  //! Elements vector
  std::vector<std::shared_ptr<Point<3>>> elements_;
};

#include "gmsh.tcc"

#endif  // MPM_GMSH_H_
