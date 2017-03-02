#include <iostream>
#include <memory>

#include "mesh.tcc"

int main(int argc, char** argv) {
  try {
    if (argc != 2) {
      std::cout << "Usage: ./mpm-point-generator /path/to/mesh_file.msh\n";
      throw std::runtime_error("Incorrect number of input arguments");
    }
    std::string filename = argv[1];
    std::unique_ptr<Mesh<4>> mesh(new Mesh<4>());
    mesh->get_vertices(filename);
    mesh->output_vertices();
    mesh->get_elements(filename);
    mesh->output_elements();
  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}
