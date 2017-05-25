#include <iostream>
#include <memory>

#include "GMSH.cc"
#include "IO.h"
#include "input.h"

int main(int argc, char** argv) {
  try {
    if (argc != 3) {
      std::cout << "Usage: ./mpm-point-generator /path/to/mesh_file.msh\n"
                   "Dimenssion 2 or 3 \n";
      throw std::runtime_error("Incorrect number of input arguments");
    }
    //! Get dimension or Tdim
    int dimension = std::atoi(argv[2]);

    //! Store input/output options including directory
    std::string inputfile = argv[1];
    std::string output_point = "/vertexcheck.txt" ;
    std::string output_stress = "/stresscheck.txt";

    std::shared_ptr<IO> filename(new IO(inputfile, output_point, output_stress));

    //! Main functions
    std::unique_ptr<GMSH> mesh(new GMSH());
    mesh->get_vertices(filename->inputfilename());
    mesh->output_vertices();
    if (dimension == 2) {
      mesh->output_stresses();
    } else {
      mesh->output_3d_stresses();
    }

  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}
