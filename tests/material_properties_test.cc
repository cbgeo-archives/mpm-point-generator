// Point test
#include <limits>

#include "catch.hpp"
#include "material_properties.h"
#include "json.hpp"

//! Short alias for convenience
using json = nlohmann::json;

//! \brief Check point class in 2D
TEST_CASE("MaterialProperties base is checked", "[MaterialProperties]") {

  //! Test for MaterialProperties
  const double tolerance = 1.E-12;

  //! Coordinates are checked for zero values
  SECTION("Checking for zero values") {
    json jsonfile;
    jsonfile["material_properties"]["density"] = 0;
    jsonfile["material_properties"]["k0"] = 0;

    auto node = std::unique_ptr<MaterialProperties>(
        new MaterialProperties(jsonfile));

    REQUIRE(node->density() == Approx(0).epsilon(tolerance));
    REQUIRE(node->k0() == Approx(0).epsilon(tolerance));
  }

  //! Coordinates are checked for minimum values
  SECTION("Checking for minimum values") {
    json jsonfile;
    jsonfile["material_properties"]["density"] = std::numeric_limits<unsigned>::min();
    jsonfile["material_properties"]["k0"] = std::numeric_limits<unsigned>::min();

    auto node = std::unique_ptr<MaterialProperties>(
        new MaterialProperties(jsonfile));

    REQUIRE(node->density() ==
            Approx(std::numeric_limits<unsigned>::min()).epsilon(tolerance));
    REQUIRE(node->k0() ==
            Approx(std::numeric_limits<unsigned>::min()).epsilon(tolerance));
  }

  //! Coordinates are checked for maximum values
  SECTION("Checking for maximum values") {
    json jsonfile;
    jsonfile["material_properties"]["density"] = std::numeric_limits<unsigned>::max();
    jsonfile["material_properties"]["k0"] = std::numeric_limits<unsigned>::max();

    auto node = std::unique_ptr<MaterialProperties>(
        new MaterialProperties(jsonfile));

    REQUIRE(node->density() ==
            Approx(std::numeric_limits<unsigned>::max()).epsilon(tolerance));
    REQUIRE(node->k0() ==
            Approx(std::numeric_limits<unsigned>::max()).epsilon(tolerance));
  }
}