#include <iostream>
#include <memory>

#include "gmsh.h"
#include "io.h"
#include "material_points.h"

int main(int argc, char** argv) {
  try {
    //! Check the number of arguments
    if (argc != 2) {
      std::cout << "Usage: ./mpm-point-generator /path/to/json_file\n";
      throw std::runtime_error("Incorrect number of input arguments");
    }

    //! IO handler
    std::unique_ptr<IO<3>> io(new IO<3>(argv[1]));

    //! Mesh handler
    std::unique_ptr<Mesh<3, 8>> mesh(new GMSH<3, 8>());

    //! Read mesh
    mesh->read_mesh(io->mesh_file_name());

    //! Compute material points and stress
    mesh->compute_material_points();
    mesh->material_points().at(0)->add_material_properties(io->json_filename());
    mesh->material_points().at(0)->compute_stress();

    //! Write material points and stresses
    io->write_point_coordinates(mesh->material_points().at(0)->coordinates());
    io->write_stresses(mesh->material_points().at(0)->stress());

  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}
