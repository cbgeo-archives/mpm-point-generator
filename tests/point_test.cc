// Point test
#include <array>
#include <limits>

#include <Eigen/Dense>

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
    Eigen::VectorXd coordinate(DIM); 
    coordinate << 0, 0;
    Eigen::VectorXd stress(DIM * 2); 
    stress << 0, 0, 0, 0;
    auto node = std::unique_ptr<Point<DIM>>(new Point<DIM>(index, coordinate));
    node->stress(stress);

    REQUIRE(node->id() == 0);
    REQUIRE(node->coordinates()(0) == Approx(0).epsilon(tolerance));
    REQUIRE(node->coordinates()(1) == Approx(0).epsilon(tolerance));
    REQUIRE(node->stress()(0) == Approx(0).epsilon(tolerance));
    REQUIRE(node->stress()(1) == Approx(0).epsilon(tolerance));
    REQUIRE(node->stress()(2) == Approx(0).epsilon(tolerance));
    REQUIRE(node->stress()(3) == Approx(0).epsilon(tolerance));
  }

  //! Coordinates are checked for minimum values
  SECTION("Coordinates are checked for minimum values") {
    const unsigned index = std::numeric_limits<unsigned>::min();
    Eigen::VectorXd coordinate(DIM);
    coordinate << std::numeric_limits<double>::min(), std::numeric_limits<double>::min();
    Eigen::VectorXd stress(DIM * 2);
    stress << std::numeric_limits<double>::min(), std::numeric_limits<double>::min(),
        std::numeric_limits<double>::min(), std::numeric_limits<double>::min();
    auto node = std::unique_ptr<Point<DIM>>(new Point<DIM>(index, coordinate));
    node->stress(stress);

    REQUIRE(node->id() == std::numeric_limits<unsigned>::min());
    REQUIRE(node->coordinates()(0) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(node->coordinates()(1) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(node->stress()(0) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(node->stress()(1) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(node->stress()(2) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(node->stress()(3) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
  }

  //! Coordinates are checked for maximum values
  SECTION("Coordinates are checked for maximum values") {
    const unsigned index = std::numeric_limits<unsigned>::max();
    Eigen::VectorXd coordinate(DIM);
    coordinate << std::numeric_limits<double>::max(), std::numeric_limits<double>::max();
    Eigen::VectorXd stress(DIM * 2);
    stress << std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
        std::numeric_limits<double>::max(), std::numeric_limits<double>::max();
    auto node = std::unique_ptr<Point<DIM>>(new Point<DIM>(index, coordinate));
    node->stress(stress);

    REQUIRE(node->id() == std::numeric_limits<unsigned>::max());
    REQUIRE(node->coordinates()(0) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(node->coordinates()(1) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(node->stress()(0) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(node->stress()(1) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(node->stress()(2) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(node->stress()(3) ==
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
    Eigen::VectorXd coordinate(DIM);
    coordinate << 0, 0, 0;
    Eigen::VectorXd stress(DIM * 2);
    stress << 0, 0, 0, 0, 0, 0;
    auto node = std::unique_ptr<Point<DIM>>(new Point<DIM>(index, coordinate));
    node->stress(stress);

    REQUIRE(node->id() == 0);
    REQUIRE(node->coordinates()(0) == Approx(0).epsilon(tolerance));
    REQUIRE(node->coordinates()(1) == Approx(0).epsilon(tolerance));
    REQUIRE(node->coordinates()(2) == Approx(0).epsilon(tolerance));
    REQUIRE(node->stress()(0) == Approx(0).epsilon(tolerance));
    REQUIRE(node->stress()(1) == Approx(0).epsilon(tolerance));
    REQUIRE(node->stress()(2) == Approx(0).epsilon(tolerance));
    REQUIRE(node->stress()(3) == Approx(0).epsilon(tolerance));
    REQUIRE(node->stress()(4) == Approx(0).epsilon(tolerance));
    REQUIRE(node->stress()(5) == Approx(0).epsilon(tolerance));
  }

  //! Coordinates are checked for minimum values
  SECTION("Coordinates are checked for minimum values") {
    const unsigned index = std::numeric_limits<unsigned>::min();
    Eigen::VectorXd coordinate(DIM);
    coordinate << std::numeric_limits<double>::min(), std::numeric_limits<double>::min(),
        std::numeric_limits<double>::min();
    Eigen::VectorXd stress(DIM * 2);
    stress << std::numeric_limits<double>::min(), std::numeric_limits<double>::min(),
        std::numeric_limits<double>::min(), std::numeric_limits<double>::min(),
        std::numeric_limits<double>::min(), std::numeric_limits<double>::min();
    auto node = std::unique_ptr<Point<DIM>>(new Point<DIM>(index, coordinate));
    node->stress(stress);

    REQUIRE(node->id() == std::numeric_limits<unsigned>::min());
    REQUIRE(node->coordinates()(0) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(node->coordinates()(1) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(node->coordinates()(2) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(node->stress()(0) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(node->stress()(1) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(node->stress()(2) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(node->stress()(3) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(node->stress()(4) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
    REQUIRE(node->stress()(5) ==
            Approx(std::numeric_limits<double>::min()).epsilon(tolerance));
  }

  //! Coordinates are checked for maximum values
  SECTION("Coordinates are checked for maximum values") {
    const unsigned index = std::numeric_limits<unsigned>::max();
    Eigen::VectorXd coordinate(DIM);
    coordinate << std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
        std::numeric_limits<double>::max();
    Eigen::VectorXd stress(DIM * 2);
    stress << std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
        std::numeric_limits<double>::max(), std::numeric_limits<double>::max(),
        std::numeric_limits<double>::max(), std::numeric_limits<double>::max();
    auto node = std::unique_ptr<Point<DIM>>(new Point<DIM>(index, coordinate));
    node->stress(stress);

    REQUIRE(node->id() == std::numeric_limits<unsigned>::max());
    REQUIRE(node->coordinates()(0) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(node->coordinates()(1) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(node->coordinates()(2) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(node->stress()(0) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(node->stress()(1) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(node->stress()(2) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(node->stress()(3) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(node->stress()(4) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
    REQUIRE(node->stress()(5) ==
            Approx(std::numeric_limits<double>::max()).epsilon(tolerance));
  }
}