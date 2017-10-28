// GMSH test
#include <array>
#include <limits>

#include <eigen3/Eigen/Dense>

#include "catch.hpp"
#include "element.h"

//! \brief Check that IO will store right values
TEST_CASE("GMSH is checked in 3D", "[GMSH][3D]") {

  const double tolerance = 1.E-12;

  double test = 0;
  const unsigned id = 0;

  SECTION("Check volume of hexahedron") {

    std::vector<Eigen::Vector3d> coordinates;
    Eigen::VectorXd vertices(8);

    vertices << 0, 0, 0, 0, 0, 0, 0, 0;

    Element element(id, vertices);

    Eigen::Vector3d a = {0, 0.1, 0.1}, b = {0.05, 0.1, 0.1}, c = {0.05, 0.05, 0.1},
        d = {0, 0.05, 0.1}, e = {0, 0.1, 0.05}, f = {0.05, 0.1, 0.05},
        g = {0.05, 0.05, 0.05}, h = {0, 0.05, 0.05};

    coordinates.push_back(a);
    coordinates.push_back(b);
    coordinates.push_back(c);
    coordinates.push_back(d);
    coordinates.push_back(e);
    coordinates.push_back(f);
    coordinates.push_back(g);
    coordinates.push_back(h);

    element.coordinates(coordinates);
    test = element.calculate_volume();

    REQUIRE(test == Approx(0.000125).epsilon(tolerance));
  }
}
