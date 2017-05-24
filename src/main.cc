#include <iostream>
#include <memory>

#include "gmsh.h"

int main(int argc, char** argv) {
  try {
    if (argc != 3) {
      std::cout << "Usage: ./mpm-point-generator /path/to/mesh_file.msh\t"
                   "Dimension 2 or 3\n";
      throw std::runtime_error("Incorrect number of input arguments");
    }

    int dimension = std::atoi(argv[2]);
    std::string filename = argv[1];

    std::unique_ptr<GMSH> mesh(new GMSH());
    mesh->get_vertices(filename);
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
