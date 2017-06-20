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
    std::unique_ptr<IO<3>> io(new IO<3>(argv[1]));

    //! Mesh handler
    std::unique_ptr<Mesh<3, 4>> mesh(new GMSH<3, 4>());

    //! Read mesh
    mesh->read_mesh(io->mesh_file_name());

    //! Compute material points & stresses
    mesh->compute_material_points();
    mesh->compute_stresses();

    //! Write material points and stresses
    io->write_material_points(mesh->material_points());
    io->write_stresses(mesh->stress());

  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}
