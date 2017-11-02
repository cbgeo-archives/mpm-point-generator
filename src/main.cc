#include <iostream>
#include <memory>

//! TCLAP for Input Argument Parsing
#include "tclap/CmdLine.h"

#include "gmsh.h"
#include "io.h"

int main(int argc, char** argv) {
  try {

    //! IO
    std::unique_ptr<IO> io(new IO(argc, argv));

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
    io->write_volumes(mesh->calculate_volumes());

    //! Write .vtk output files for viewing
    mesh->write_vtk_stresses(io->output_file("initial_stresses", ".vtk"));
    mesh->write_vtk_mesh(io->output_file("mesh", ".vtk"));

  } catch (TCLAP::ArgException& except) {  // catch any exceptions
    std::cerr << "Unhandled command line argument" << except.error()
              << except.argId();
  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}
