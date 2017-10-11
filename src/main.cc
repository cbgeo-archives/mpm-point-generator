#include <iostream>
#include <memory>

#include "gauss_points.h"
#include "gmsh.h"
#include "io.h"

int main(int argc, char** argv) {
  try {
    //! Check the number of arguments
    if (argc != 3) {
      std::cout << "Usage: ./mpm_point_generator /path/ json_file\n";
      throw std::runtime_error("Incorrect number of input arguments");
    }

    //! IO
    std::unique_ptr<IO<3>> io(new IO<3>(argv[1], argv[2]));

    //! Mesh
    std::unique_ptr<Mesh<3, 8>> mesh(new GMSH<3, 8>());

    //! MaterialProperties
    std::shared_ptr<MaterialProperties> material =
        std::make_shared<MaterialProperties>(io->material_properties());

    //! Read mesh
    mesh->read_mesh(io->mesh_file_name());

    //! Compute material points and stresses
    mesh->compute_material_points(io->ngauss_points());
    mesh->assign_material_properties(material);
    mesh->compute_stresses();

    //! Write material points and stresses
    io->write_coordinates(mesh->coordinates());
    io->write_stresses(mesh->stress());

  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}
