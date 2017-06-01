// Point test
#include <array>
#include <limits>

#include "catch.hpp"
#include "point.h"

//! \brief Check that Point will store right values
//! \details Write arbritrary index and coordinate and store them

TEST_CASE("Point base is checked in 2D and 3D", "[Point][2D][3D]") {

  //! test for 3d
  const unsigned Tdim_3d = 3;
  unsigned index_3d = 0;
  const std::array<double, Tdim_3d> coordinate_3d{0, 0, 0};
  std::unique_ptr<Point<Tdim_3d>> node_3d(
      new Point<Tdim_3d>(index_3d, coordinate_3d));

  REQUIRE(node_3d->id() == 0);
  REQUIRE(node_3d->coordinates().at(0) == 0);
  REQUIRE(node_3d->coordinates().at(1) == 0);
  REQUIRE(node_3d->coordinates().at(2) == 0);

  //! test for 2d
  const unsigned Tdim_2d = 2;
  unsigned index_2d = 1;
  const std::array<double, Tdim_2d> coordinate_2d{1, 1};
  std::unique_ptr<Point<Tdim_2d>> node_2d(
      new Point<Tdim_2d>(index_2d, coordinate_2d));

  REQUIRE(node_2d->id() == 1);
  REQUIRE(node_2d->coordinates().at(0) == 1);
  REQUIRE(node_2d->coordinates().at(1) == 1);
}