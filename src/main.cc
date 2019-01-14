#include <iostream>
#include <memory>
#include <vector>

//! TCLAP for Input Argument Parsing
#include "tclap/CmdLine.h"

#include "gmsh.h"
#include "io.h"

int main(int argc, char** argv) {
  try {

    //! IO
    std::unique_ptr<IO> io(new IO(argc, argv));

    //! MaterialProperties
    std::vector<std::unique_ptr<MaterialProperties>> material;

    for (unsigned i = 0; i < io->material_properties().size(); i++) {
      material.emplace_back(
          std::make_unique<MaterialProperties>(io->material_properties()[i]));
    }

    switch (io->dimension()) {

      case 2: {
        const unsigned Tdim = 2;
        const unsigned Tvertices = 4;

        //! Mesh
        std::unique_ptr<Mesh<Tdim, Tvertices>> mesh(new GMSH<Tdim, Tvertices>);

        //! Read mesh
        mesh->read_mesh(io->mesh_file_name());

        //! Compute material points and stresses
        mesh->generate_material_points(io->ngauss_points());
        mesh->assign_material_properties(std::move(material));
        mesh->compute_stresses();

        //! Write material points and stresses
        mesh->write_coordinates(io->output_file("material_points", ".txt"));
        mesh->write_stresses(io->output_file("initial_stresses", ".txt"));
        mesh->write_volumes(io->output_file("volumes", ".txt"));

        //! Write .vtk output files for viewing
        mesh->write_vtk_points(io->output_file("points", ".vtk"));
        mesh->write_vtk_stresses(io->output_file("initial_stresses", ".vtk"));
        mesh->write_vtk_mesh(io->output_file("mesh", ".vtk"));

        break;
      }

      case 3: {
        const unsigned Tdim = 3;
        const unsigned Tvertices = 8;

        //! Mesh
        std::unique_ptr<Mesh<Tdim, Tvertices>> mesh(new GMSH<Tdim, Tvertices>);

        //! Read mesh
        mesh->read_mesh(io->mesh_file_name());

        //! Compute material points and stresses
        mesh->generate_material_points(io->ngauss_points());
        mesh->assign_material_properties(std::move(material));
        mesh->compute_stresses();

        //! Write material points and stresses
        mesh->write_coordinates(io->output_file("material_points", ".txt"));
        mesh->write_stresses(io->output_file("initial_stresses", ".txt"));
        mesh->write_volumes(io->output_file("volumes", ".txt"));

        //! Write .vtk output files for viewing
        mesh->write_vtk_points(io->output_file("points", ".vtk"));
        mesh->write_vtk_stresses(io->output_file("initial_stresses", ".vtk"));
        mesh->write_vtk_mesh(io->output_file("mesh", ".vtk"));

        break;
      }

      default: {
        std::cout << "Dimension is not specified correctly\n";
        break;
      }
    }

  } catch (TCLAP::ArgException& except) {  // catch any exceptions
    std::cerr << "Unhandled command line argument" << except.error()
              << except.argId();
  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}
