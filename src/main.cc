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

    //! Material points with initial id of the material points of 0
    std::unique_ptr<MaterialPoints<3>> materialPoints(new MaterialPoints<3>(0));

    //! Read mesh
    mesh->read_mesh(io->mesh_file_name());

    //! Compute material points
    mesh->compute_material_points();

    //! Get materialPoints from mesh, get material properties, compute stress
    materialPoints->add_points(mesh->material_points());
    materialPoints->add_material_properties(io->material_properties_name());
    materialPoints->compute_stress();

    //! Write material points and stresses
    io->write_material_points(materialPoints->points());
    io->write_stresses(materialPoints->stress());

  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}
