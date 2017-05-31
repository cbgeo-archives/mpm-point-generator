#include <iostream>
#include <memory>

#include "gmsh.h"
#include "io.h"

int main(int argc, char** argv) {
  try {
    if (argc != 2) {
      std::cout << "Usage: ./mpm-point-generator /path/to/path_file.json\n";
      throw std::runtime_error("Incorrect number of input arguments");
    }

    //! Get path file location including directory
    //! Store them into an IO class
    std::unique_ptr<IO> file(new IO(argv[1]));

    //! Main functions
    std::unique_ptr<GMSH> mesh(new GMSH());
    mesh->get_vertices(file->inputfilename());
    file->write_output_vertices(mesh->vertices(), mesh->nvertices());
    mesh->compute_stresses();
    file->write_output_stresses(mesh->stress(), mesh->nvertices());

  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}
