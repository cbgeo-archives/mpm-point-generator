// GMSH test
#include <array>
#include <limits>

#include <eigen3/Eigen/Dense>

#include "catch.hpp"
#include "element.h"

//! \brief Check the volume of an element computation
TEST_CASE("GMSH is checked in 3D", "[GMSH][3D]") {

  const double tolerance = 1.E-12;

  // Element id
  const unsigned id = 0;

  SECTION("Check volume of a hexahedron") {

    // Element coordinates
    std::vector<Eigen::VectorXd> coordinates;
    // Element vertices
    Eigen::VectorXd vertices(8);
    vertices.setZero();

    // Create a new element
    Element element(id, vertices);

    // Assign coordinates of vertices
    Eigen::Vector3d a = {0, 0.1, 0.1}, b = {0.05, 0.1, 0.1},
                    c = {0.05, 0.05, 0.1}, d = {0, 0.05, 0.1},
                    e = {0, 0.1, 0.05}, f = {0.05, 0.1, 0.05},
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

    REQUIRE(element.calculate_volume() == Approx(0.000125).epsilon(tolerance));
  }

  SECTION("Check volume of a tetrahedron") {

    // Element coordinates
    std::vector<Eigen::VectorXd> coordinates;
    // Element vertices
    Eigen::VectorXd vertices(4);
    vertices.setZero();

    // Create a new element
    Element element(id, vertices);

    // Assign coordinates of vertices
    Eigen::Vector3d a = {0, 0, 0}, b = {0, 0, 3},
                    c = {3, 0, 0}, d = {0, 3, 0};

    coordinates.push_back(a);
    coordinates.push_back(b);
    coordinates.push_back(c);
    coordinates.push_back(d);

    element.coordinates(coordinates);

    REQUIRE(element.calculate_volume() == Approx(4.5).epsilon(tolerance));
  }
}
