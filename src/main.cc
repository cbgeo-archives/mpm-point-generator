#include <iostream>
#include <memory>

#include "mesh.tcc"

int main(int argc, char** argv) {
  try {
    if (argc != 3) {
      std::cout << "Usage: ./mpm-point-generator /path/to/mesh_file.msh\n"
              "Dimenssion 2 or 3\n";
      throw std::runtime_error("Incorrect number of input arguments");
    }

      int dimension = std::atoi(argv[2]);
      std::string filename = argv[1];

          std::cout << "Tetra Points Selected \n";
          std::unique_ptr<Mesh<4>> mesh(new Mesh<4>());
          mesh->get_vertices(filename);
          mesh->output_vertices();
          mesh->get_elements(filename);
          // mesh->output_elements(); // not needed for vertices output
          if (dimension == 2) {
              mesh->output_stresses();
          } else {
              mesh->output_3d_stresses();
          }


  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}
