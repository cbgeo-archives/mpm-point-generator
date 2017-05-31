#include <iostream>
#include <memory>

#include "gmsh.h"
#include "io.h"

int main(int argc, char** argv) {
  try {
    //! Check the number of arguments
    if (argc != 2) {
      std::cout << "Usage: ./mpm-point-generator /path/to/meshfile.msh\n";
      throw std::runtime_error("Incorrect number of input arguments");
    }

    //! IO handler
    std::unique_ptr<IO> io(new IO(argv[1]));

    //! Mesh handler
    std::unique_ptr<GMSH> mesh(new GMSH());

    //! Read mesh and compute stresses
    mesh->read_vertices(io->mesh_file_name());
    mesh->compute_stresses();

    //! Write vertices and stresses
    io->write_vertices(mesh->vertices());
    io->write_stresses(mesh->stress());

  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}
