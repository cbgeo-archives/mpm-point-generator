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

  auto mesh = std::unique_ptr<Mesh<3, 8>> (new GMSH<3, 8>());
  mesh->read_mesh("../bin/regression_test.msh");
  mesh->compute_material_points();
  mesh->compute_stresses();

  //! Check number of vertices
  REQUIRE(mesh->nvertices() == 18);

  //! Check size
  REQUIRE(mesh->material_points().size() == 4);

  //! Check id
  REQUIRE(mesh->material_points().at(0)->id() == 45);
  REQUIRE(mesh->material_points().at(1)->id() == 46);
  REQUIRE(mesh->material_points().at(2)->id() == 47);
  REQUIRE(mesh->material_points().at(3)->id() == 48);

  //! Check coordinates
  REQUIRE(mesh->material_points().at(0)->coordinates()[0] == Approx(0.25).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(0)->coordinates()[1] == Approx(0.50).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(0)->coordinates()[2] == Approx(0.25).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(1)->coordinates()[0] == Approx(0.25).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(1)->coordinates()[1] == Approx(0.50).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(1)->coordinates()[2] == Approx(0.75).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(2)->coordinates()[0] == Approx(0.75).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(2)->coordinates()[1] == Approx(0.50).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(2)->coordinates()[2] == Approx(0.25).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(3)->coordinates()[0] == Approx(0.75).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(3)->coordinates()[1] == Approx(0.50).epsilon(tolerance));
  REQUIRE(mesh->material_points().at(3)->coordinates()[2] == Approx(0.75).epsilon(tolerance));

  //! Check stress
  REQUIRE(mesh->stress().at(0)[0] == Approx(-55).epsilon(tolerance));
  REQUIRE(mesh->stress().at(0)[1] == Approx(-55).epsilon(tolerance));
  REQUIRE(mesh->stress().at(0)[2] == Approx(-110).epsilon(tolerance));
  REQUIRE(mesh->stress().at(0)[3] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(0)[4] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(0)[5] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(1)[0] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(1)[1] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(1)[2] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(1)[3] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(1)[4] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(1)[5] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(2)[0] == Approx(-55).epsilon(tolerance));
  REQUIRE(mesh->stress().at(2)[1] == Approx(-55).epsilon(tolerance));
  REQUIRE(mesh->stress().at(2)[2] == Approx(-110).epsilon(tolerance));
  REQUIRE(mesh->stress().at(2)[3] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(2)[4] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(2)[5] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(3)[0] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(3)[1] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(3)[2] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(3)[3] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(3)[4] == Approx(0).epsilon(tolerance));
  REQUIRE(mesh->stress().at(3)[5] == Approx(0).epsilon(tolerance));
}