#include <iostream>
#include <memory>

#include "gmsh.h"
#include "io.h"

int main(int argc, char** argv) {
  try {
    if (argc != 3) {
      std::cout << "Usage: ./mpm-point-generator /path/to/path_file.txt\n"
                   "Dimension 2 or 3\n";
      throw std::runtime_error("Incorrect number of input arguments");
    }
    //! Get Tdim
    int Tdim = std::atoi(argv[2]);

    //! Get path file location including directory
    const std::string pathfile_name = argv[1];

    //! Store them into an IO class
    std::unique_ptr<IO> file(new IO(pathfile_name));

    //! Main functions
    std::unique_ptr<GMSH> mesh(new GMSH());
    mesh->get_vertices(file->inputfilename());
    mesh->output_vertices(file->outputfilename_point());
    mesh->output_stresses(file->outputfilename_stress());

  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}
