#include <iostream>
#include <memory>

//! TCLAP for Input Argument Parsing
#include "tclap/CmdLine.h"

#include "gmsh.h"
#include "io.h"

int main(int argc, char** argv) {
  try {
    // Set title
    TCLAP::CmdLine cmd("Material Point Generator (CB-Geo)", ' ', "0.0.1");

    // Define dimension
    /*TCLAP::ValueArg<unsigned int> dim_arg(
        "d", "dimension", "Problem dimension", true, 3, "Dimension");
    cmd.add(dim_arg);*/

    // Define working directory
    TCLAP::ValueArg<std::string> cwd_arg("f", "working_dir",
                                         "Current working folder", true, "",
                                         "Working_folder");
    cmd.add(cwd_arg);

    // Define input file
    TCLAP::ValueArg<std::string> input_arg("i", "input_file",
                                           "Input JSON file [cube.json]", false,
                                           "cube.json", "input_file");
    cmd.add(input_arg);

    // Parse arguments
    cmd.parse(argc, argv);

    // Dimension
    // dimension_ = dim_arg.getValue();

    // Set working directory
    auto working_dir = cwd_arg.getValue();

    // Set input file if the optional argument is not empty
    auto input_file = input_arg.getValue();

    //! IO
    std::unique_ptr<IO<3>> io(new IO<3>(working_dir, input_file));

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
    io->write_vtk_stresses(mesh->coordinates(), mesh->stress());
    io->write_vtk_mesh(mesh->vertices(), mesh->elements());

  } catch (TCLAP::ArgException& except) {  // catch any exceptions
    std::cerr << "Unhandled command line argument" << except.error()
              << except.argId();
  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}
