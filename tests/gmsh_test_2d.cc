// GMSH test
#include <array>
#include <limits>

#include <eigen3/Eigen/Dense>

#include "catch.hpp"
#include "gmsh.h"
#include "material_points.h"
#include "regression_global.h"

//! Alias for JSON
#include "json.hpp"
using json = nlohmann::json;

//! \brief Check that IO will store right values
TEST_CASE("GMSH is checked in 2D", "[GMSH][2D]") {

  //! 3D Test of IO Class
  const unsigned DIM = 2;
  const double tolerance = 1.E-12;

  //! Make json object with material in it
  json material_json = {{"density", 2000}, {"k0", 0.5}};

  //! Make pointers to mesh and MaterialProperties
  auto mesh = std::unique_ptr<Mesh<2, 4>>(new GMSH<2, 4>());
  auto material = std::shared_ptr<MaterialProperties>(
      new MaterialProperties(material_json));

  mesh->read_mesh(filename, 3);
  mesh->compute_material_points(1, 3);
  mesh->assign_material_properties(material);
  mesh->compute_stresses();

  //! Check number of vertices
  REQUIRE(mesh->nvertices() == 6);

  //! Get coordinates, stresses, volumes and global_ids
  std::vector<Eigen::VectorXd> coordinates;
  std::vector<Eigen::VectorXd> stresses;
  std::vector<double> volumes;
  std::vector<unsigned> global_ids;

  for (auto iterators = mesh->material_points_begin();
       iterators != mesh->material_points_end(); ++iterators) {
    for (auto itr = (*iterators)->points_begin();
         itr != (*iterators)->points_end(); ++itr) {
      coordinates.emplace_back((*itr)->coordinates());
      stresses.emplace_back((*itr)->stress());
      volumes.emplace_back((*itr)->volume());
      global_ids.emplace_back((*itr)->global_id());
    }
  }

  //! Check size
  REQUIRE(coordinates.size() == 2);
  REQUIRE(stresses.size() == 2);
  REQUIRE(volumes.size() == 2);
  REQUIRE(global_ids.size() == 2);

  //! Check id
  REQUIRE(global_ids.at(0) == 0);
  REQUIRE(global_ids.at(1) == 1);

  //! Check coordinates
  REQUIRE(coordinates.at(0)[0] == Approx(0.50).epsilon(tolerance));
  REQUIRE(coordinates.at(0)[1] == Approx(0.50).epsilon(tolerance));
  REQUIRE(coordinates.at(1)[0] == Approx(0.50).epsilon(tolerance));
  REQUIRE(coordinates.at(1)[1] == Approx(2.00).epsilon(tolerance));

  //! Check stress
  REQUIRE(stresses.at(0)[0] == Approx(-14715).epsilon(tolerance));
  REQUIRE(stresses.at(0)[1] == Approx(-29430).epsilon(tolerance));
  REQUIRE(stresses.at(0)[2] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(0)[3] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(0)[4] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(0)[5] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(1)[0] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(1)[1] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(1)[2] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(1)[3] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(1)[4] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(1)[5] == Approx(0).epsilon(tolerance));
  
  //! Check volume
  REQUIRE(volumes.at(0) == Approx(1).epsilon(tolerance));
  REQUIRE(volumes.at(1) == Approx(2).epsilon(tolerance));

}