// Point test
#include <array>
#include <limits>

#include "catch.hpp"
#include "point.h"

//! \brief Check point class in 2D
TEST_CASE("Point base is checked in 2D", "[Point][2D]") {

  //! 2D Test of Point Class
  const double tolerance = 1.E-12;
  const unsigned DIM = 2;

  //! Coordinates are checked for zero values
  SECTION("Coordinates are checked for zero values") {
    const unsigned index = 0;
    const std::array<double, DIM> coordinate{0, 0};
    auto node = std::unique_ptr<Point<DIM>>(new Point<DIM>(index, coordinate));

    REQUIRE(node->id() == 0);
    REQUIRE(node->coordinates().at(0) == Approx(0).epsilon(tolerance));
    REQUIRE(node->coordinates().at(1) == Approx(0).epsilon(tolerance));
  }

  //! Coordinates are checked for minimum values
  SECTION("Coordinates are checked for minimum values") {
    const unsigned index = std::numeric_limits<unsigned>::min();
    const std::array<double, DIM> coordinate{
        std::numeric_limits<double>::min(), std::numeric_limits<double>::min()};
    auto node = std::unique_ptr<Point<DIM>>(new Point<DIM>(index, coordinate));

    REQUIRE(node->id() == std::numeric_limits<unsigned>::min());
    REQUIRE(node->coordinates().at(0) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(node->coordinates().at(1) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
  }

  //! Coordinates are checked for maximum values
  SECTION("Coordinates are checked for maximum values") {
    const unsigned index = std::numeric_limits<unsigned>::max();
    const std::array<double, DIM> coordinate{
        std::numeric_limits<double>::max(), std::numeric_limits<double>::max()};
    auto node = std::unique_ptr<Point<DIM>>(new Point<DIM>(index, coordinate));

    REQUIRE(node->id() == std::numeric_limits<unsigned>::max());
    REQUIRE(node->coordinates().at(0) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(node->coordinates().at(1) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
  }
}

//! \brief Check point class in 3D
TEST_CASE("Point base is checked in 3D", "[Point][3D]") {

  //! 3D Test of Point Class
  const double tolerance = 1.E-12;
  const unsigned DIM = 3;

  //! Coordinates are checked for zero values
  SECTION("Coordinates are checked for zero values") {
    const unsigned index = 0;
    const std::array<double, DIM> coordinate{0, 0, 0};
    auto node = std::unique_ptr<Point<DIM>>(new Point<DIM>(index, coordinate));

    REQUIRE(node->id() == 0);
    REQUIRE(node->coordinates().at(0) == Approx(0).epsilon(tolerance));
    REQUIRE(node->coordinates().at(1) == Approx(0).epsilon(tolerance));
    REQUIRE(node->coordinates().at(2) == Approx(0).epsilon(tolerance));
  }

  //! Coordinates are checked for minimum values
  SECTION("Coordinates are checked for minimum values") {
    const unsigned index = std::numeric_limits<unsigned>::min();
    const std::array<double, DIM> coordinate{
        std::numeric_limits<double>::min(), std::numeric_limits<double>::min(),
        std::numeric_limits<double>::min()};
    auto node = std::unique_ptr<Point<DIM>>(new Point<DIM>(index, coordinate));

    REQUIRE(node->id() == std::numeric_limits<unsigned>::min());
    REQUIRE(node->coordinates().at(0) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(node->coordinates().at(1) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(node->coordinates().at(2) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
  }

  //! Coordinates are checked for maximum values
  SECTION("Coordinates are checked for maximum values") {
    const unsigned index = std::numeric_limits<unsigned>::max();
    const std::array<double, DIM> coordinate{
        std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
        std::numeric_limits<double>::max()};
    auto node = std::unique_ptr<Point<DIM>>(new Point<DIM>(index, coordinate));

    REQUIRE(node->id() == std::numeric_limits<unsigned>::max());
    REQUIRE(node->coordinates().at(0) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(node->coordinates().at(1) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(node->coordinates().at(2) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
  }
}