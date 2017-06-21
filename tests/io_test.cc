// IO test
#include <array>
#include <limits>

#include "catch.hpp"
#include "point.h"
#include "io.h"

//! \brief Check that IO will store right values
TEST_CASE("IO is checked in 3D", "[IO][3D]") {

  //! 3D Test of IO Class
  const unsigned DIM = 3;
  auto io = std::unique_ptr<IO<DIM>> (new IO<DIM>("../bin/test_3d.msh"));
  REQUIRE(io->mesh_file_name() == "../bin/test_3d.msh");
}