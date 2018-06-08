// Point test
#include <limits>

#include "catch.hpp"
#include "material_properties.h"

//! Alias for JSON
#include "json.hpp"
using json = nlohmann::json;

//! \brief Check point class in 2D
TEST_CASE("MaterialProperties base is checked", "[MaterialProperties]") {

  //! Test for MaterialProperties
  const double tolerance = 1.E-12;

  //! Material properties are checked for zero values
  SECTION("Checking for zero values") {
    json materialproperties;
    materialproperties["density"] = 0;
    materialproperties["k0"] = 0;

    auto material = std::shared_ptr<MaterialProperties>(
        new MaterialProperties(materialproperties));

    REQUIRE(material->density() == Approx(0).epsilon(tolerance));
    REQUIRE(material->k0() == Approx(0).epsilon(tolerance));
  }

  //! Material properties are checked for minimum values
  SECTION("Checking for minimum values") {
    json materialproperties;
    materialproperties["density"] = std::numeric_limits<double>::min();
    materialproperties["k0"] = std::numeric_limits<double>::min();

    auto material = std::shared_ptr<MaterialProperties>(
        new MaterialProperties(materialproperties));

    REQUIRE(material->density() ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(material->k0() ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
  }

  //! Material properties are checked for maximum values
  SECTION("Checking for maximum values") {
    json materialproperties;
    materialproperties["density"] = std::numeric_limits<double>::max();
    materialproperties["k0"] = std::numeric_limits<double>::max();

    auto material = std::shared_ptr<MaterialProperties>(
        new MaterialProperties(materialproperties));

    REQUIRE(material->density() ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(material->k0() ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
  }
}