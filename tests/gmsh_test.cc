// GMSH test
#include <array>
#include <limits>

#include "catch.hpp"
#include "point.h"
#include "gmsh.h"

//! \brief Check that IO will store right values
TEST_CASE("GMSH is checked in 3D", "[GMSH][3D]") {

  //! 3D Test of IO Class
  const unsigned DIM = 3;
  const double tolerance = 1.E-12;

  auto mesh = std::unique_ptr<Mesh<3, 4>> (new GMSH<3, 4>());
  mesh->read_mesh("../bin/test_3d.msh");
  mesh->compute_material_points();
  mesh->compute_stresses();

  //! Check number of vertices
  REQUIRE(mesh->nvertices() == 12);

  //! Check size
  REQUIRE(mesh->material_points().size() == 4);

  //! Check id
  REQUIRE(mesh->material_points().at(0)->id() == 1);
  REQUIRE(mesh->material_points().at(1)->id() == 2);
  REQUIRE(mesh->material_points().at(2)->id() == 3);
  REQUIRE(mesh->material_points().at(3)->id() == 4);

  //! Check coordinates
  REQUIRE(mesh->material_points().at(0)->coordinates().at(0) == Approx(0.5).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(0)->coordinates().at(1) == Approx(0.0).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(0)->coordinates().at(2) == Approx(0.5).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(1)->coordinates().at(0) == Approx(0.5).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(1)->coordinates().at(1) == Approx(0.0).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(1)->coordinates().at(2) == Approx(1.5).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(2)->coordinates().at(0) == Approx(0.5).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(2)->coordinates().at(1) == Approx(1.0).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(2)->coordinates().at(2) == Approx(0.5).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(3)->coordinates().at(0) == Approx(0.5).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(3)->coordinates().at(1) == Approx(1.0).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(3)->coordinates().at(2) == Approx(1.5).epsilon(tolerance));

  //! Check stress
  REQUIRE(mesh->stress().at(0).at(0) == Approx(-110).epsilon(tolerance));
  REQUIRE(mesh->stress().at(0).at(1) == Approx(-110).epsilon(tolerance));
  REQUIRE(mesh->stress().at(0).at(2) == Approx(-220).epsilon(tolerance));
  REQUIRE(mesh->stress().at(0).at(3) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(0).at(4) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(0).at(5) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(1).at(0) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(1).at(1) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(1).at(2) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(1).at(3) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(1).at(4) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(1).at(5) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(2).at(0) == Approx(-110).epsilon(tolerance));
  REQUIRE(mesh->stress().at(2).at(1) == Approx(-110).epsilon(tolerance));
  REQUIRE(mesh->stress().at(2).at(2) == Approx(-220).epsilon(tolerance));
  REQUIRE(mesh->stress().at(2).at(3) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(2).at(4) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(2).at(5) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(3).at(0) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(3).at(1) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(3).at(2) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(3).at(3) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(3).at(4) == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(3).at(5) == Approx(0).epsilon(tolerance));
}