// Point test
#include <array>
#include <limits>

#include "catch.hpp"
#include "point.h"

//! \brief Check that Point will store right values
//! \details Write arbritrary index and coordinate and store them

TEST_CASE("Point base is checked in 3D", "[Point][3D]") {

  const unsigned Tdim = 3;
  unsigned index = 0;
  const std::array<double, Tdim> coordinate{0, 0, 0};
  auto node = std::unique_ptr<Point<Tdim>>(new Point<Tdim>(index, coordinate));

  REQUIRE(node->id() == 0);
  REQUIRE(node->coordinates().at(0) == 0);
  REQUIRE(node->coordinates().at(1) == 0);
  REQUIRE(node->coordinates().at(2) == 0);
}