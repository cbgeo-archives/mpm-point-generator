#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "regression_global.h"

std::string filename;

int main(int argc, char** argv) {

  try {
    //! Check the number of arguments
    if (argc != 2) {
      std::cout << "Usage: ./mpm_point_generator_regression_test "
                   "/path/to/meshfile.msh\n";
      throw std::runtime_error("Incorrect number of input arguments");
    }

    //! Pass the argument of the file
    filename = argv[1];

    int result = Catch::Session().run();

    return (result < 0xff ? result : 0xff);

  } catch (std::exception& except) {
    std::cout << "Caught exception: " << except.what() << '\n';
  }
}