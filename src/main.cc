#include <iostream>
#include <memory>
#include <vector>

#include "gmsh.h"
#include "io.h"

int main(int argc, char** argv) {
  try {
    if (argc != 3) {
      std::cout << "Usage: ./mpm-point-generator /path/to/path_file.txt\n"
                   "Dimension 2 or 3\n";
      throw std::runtime_error("Incorrect number of input arguments");
    }
    //! Get ndimension
    const unsigned ndimension = std::atoi(argv[2]);

    //! Get path file location including directory
    const std::string pathfile_name = argv[1];

    //! Store them into an IO class
    std::unique_ptr<IO> file(new IO(pathfile_name));

    //! Main functions
    std::unique_ptr<GMSH> mesh(new GMSH());
    mesh->get_vertices(file->inputfilename());
    // std::cout << file->outputfilename_vertex() << "\n";
    // std::cout << file->outputfilename_stress() << "\n";
    // std::cout << mesh->vertices().at(0)->id() << "\n";
    // std::cout << mesh->tot_points() << "\n";

    file->write_output_vertices(file->outputfilename_vertex(), mesh->vertices(),
                                mesh->tot_vertices());
    // file->write_output_stress(file->outputfilename_stress());

    mesh->output_stresses(file->outputfilename_stress());

  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}
