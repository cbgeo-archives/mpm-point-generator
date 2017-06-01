// Point test
#include <array>
#include <limits>

#include "catch.hpp"
#include "point.h"

//! \brief Check point class
TEST_CASE("Point base is checked in 3D", "[Point][3D]") {

  const unsigned DIM = 3;
  const double tol = pow(10, -12);
  std::vector<std::unique_ptr<Point<DIM>>> vec_points;

  unsigned index = 0;
  std::array<double, DIM> coordinate{0, 0, 0};
  vec_points.emplace_back(new Point<DIM>(index, coordinate));

  index = 4294967295;
  coordinate = {1.7 * pow(10, 308), 1.7 * pow(10, 308), 1.7 * pow(10, 308)};
  vec_points.emplace_back(new Point<DIM>(index, coordinate));

  index = 4294967295;
  coordinate = {-1.7 * pow(10, 308), -1.7 * pow(10, 308), -1.7 * pow(10, 308)};
  vec_points.emplace_back(new Point<DIM>(index, coordinate));

  REQUIRE(vec_points.at(0)->id() == 0);
  REQUIRE(vec_points.at(0)->coordinates().at(0) == Approx(0).epsilon(tol));
  REQUIRE(vec_points.at(0)->coordinates().at(1) == Approx(0).epsilon(tol));
  REQUIRE(vec_points.at(0)->coordinates().at(2) == Approx(0).epsilon(tol));

  REQUIRE(vec_points.at(1)->id() == 4294967295);
  REQUIRE(vec_points.at(1)->coordinates().at(0) ==
          Approx(1.7 * pow(10, 308)).epsilon(tol));
  REQUIRE(vec_points.at(1)->coordinates().at(1) ==
          Approx(1.7 * pow(10, 308)).epsilon(tol));
  REQUIRE(vec_points.at(1)->coordinates().at(2) ==
          Approx(1.7 * pow(10, 308)).epsilon(tol));

  REQUIRE(vec_points.at(2)->id() == 4294967295);
  REQUIRE(vec_points.at(2)->coordinates().at(0) ==
          Approx(-1.7 * pow(10, 308)).epsilon(tol));
  REQUIRE(vec_points.at(2)->coordinates().at(1) ==
          Approx(-1.7 * pow(10, 308)).epsilon(tol));
  REQUIRE(vec_points.at(2)->coordinates().at(2) ==
          Approx(-1.7 * pow(10, 308)).epsilon(tol));
}