#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>

#include "io.h"

#include "json.hpp"

//! \brief Write output file for point
//! \details Get vectors from gmsh.h and output to file here
void write_output_vertices(
    const std::string& outputfilename,
    const std::vector<std::shared_ptr<Point<3>>> vertices,
    const unsigned tot_vertices) {

  std::fstream outputfile;
  outputfile.open(outputfilename, std::ios::out);

  if (outputfile.is_open()) {

    //! Iterate through vector and print
    outputfile << tot_vertices << '\n';

    for (const auto& point : vertices) {
      outputfile << point->coordinates().at(0) << '\t'
                 << point->coordinates().at(1) << '\t'
                 << point->coordinates().at(2) << '\n';
    }
    outputfile.close();
  }

  std::cout << "The output file for soil particles has been generated."
            << "\n";
}

//! \brief Write output file for stress
//! \details Get vectors from gmsh.h and output to file here
void write_output_stress(const std::string& outputfilename) {
  std::cout << "success\n";
}
