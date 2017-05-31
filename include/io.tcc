#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "gmsh.h"
#include "point.h"

#include "json.hpp"

//! \brief Write output file for point
//! \details Get vectors from gmsh.h and output to file here
void IO::write_output_vertices(
    const std::string& outputfilename,
    const std::vector<std::shared_ptr<Point<3>>>& vertices,
    const unsigned tot_vertices) {

  //! Open file to write output
  std::fstream outputfile;
  outputfile.open(outputfilename, std::ios::out);
  if (outputfile.is_open()) {

    //! Write the total number of vertices generated
    outputfile << tot_vertices << "\n";

    //! Write the coordinates of the vertices generated
    //! [X] [Y] [Z]
    //! Note that for 2D, z values are 0
    //! For 1D, both y and z values are 0
    for (auto const& point : vertices) {
      for (double coordinate : point->coordinates()) {
        outputfile << coordinate << "\t";
      }
      outputfile << "\n";
    }
    outputfile.close();
  }

  std::cout << "The output file for soil particles has been generated."
            << "\n";
}

//! \brief Write output file for stress
//! \details Get vectors from gmsh.h and output to file here
//! \brief Write output file for stress
void IO::write_output_stress(
    const std::string& outputfilename,
    const std::vector<std::shared_ptr<Point<3>>>& stress,
    const unsigned tot_points) {
  

}
