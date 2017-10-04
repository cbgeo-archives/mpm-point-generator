// Point test
#include <limits>

#include "catch.hpp"
#include "material_properties.h"

//! \brief Check point class in 2D
TEST_CASE("MaterialProperties base is checked", "[MaterialProperties]") {

  //! Test for MaterialProperties
  const double tolerance = 1.E-12;

  //! Coordinates are checked for zero values
  SECTION("Checking for zero values") {
    const double density = 0;
    const double k0 = 0;
    auto node = std::unique_ptr<MaterialProperties>(
        new MaterialProperties(density, k0));

    REQUIRE(node->density() == Approx(0).epsilon(tolerance));
    REQUIRE(node->k0() == Approx(0).epsilon(tolerance));
  }

  //! Coordinates are checked for minimum values
  SECTION("Checking for minimum values") {
    const double density = std::numeric_limits<unsigned>::min();
    const double k0 = std::numeric_limits<unsigned>::min();
    auto node = std::unique_ptr<MaterialProperties>(
        new MaterialProperties(density, k0));

    REQUIRE(node->density() ==
            Approx(std::numeric_limits<unsigned>::min()).epsilon(tolerance));
    REQUIRE(node->k0() ==
            Approx(std::numeric_limits<unsigned>::min()).epsilon(tolerance));
  }

  //! Coordinates are checked for maximum values
  SECTION("Checking for maximum values") {
    const double density = std::numeric_limits<unsigned>::max();
    const double k0 = std::numeric_limits<unsigned>::max();
    auto node = std::unique_ptr<MaterialProperties>(
        new MaterialProperties(density, k0));

    REQUIRE(node->density() ==
            Approx(std::numeric_limits<unsigned>::max()).epsilon(tolerance));
    REQUIRE(node->k0() ==
            Approx(std::numeric_limits<unsigned>::max()).epsilon(tolerance));
  }
}