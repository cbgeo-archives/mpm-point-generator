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

    //! MaterialProperties
    std::shared_ptr<MaterialProperties> material =
        std::make_shared<MaterialProperties>(io->material_properties());

    // const unsigned Tdim = io->dimension();
    // const unsigned Tvertices = io->nvertices();

    const unsigned Tdim = 2;
    const unsigned Tvertices = 4;

    //! Mesh
    std::unique_ptr<Mesh<Tdim, Tvertices>> mesh(new GMSH<Tdim, Tvertices>);

    //! Read mesh
    mesh->read_mesh(io->mesh_file_name(), io->element_type());

    //! Compute material points and stresses
    mesh->compute_material_points(io->ngauss_points(), io->element_type());
    mesh->assign_material_properties(material);
    mesh->compute_stresses();

    //! Write material points and stresses
    mesh->write_coordinates(io->output_file("material_points", ".txt"));
    mesh->write_stresses(io->output_file("initial_stresses", ".txt"));
    mesh->write_volumes(io->output_file("volumes", ".txt"));

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
