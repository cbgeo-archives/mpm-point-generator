// GMSH test
#include <array>
#include <limits>
#include <vector>

#include <eigen3/Eigen/Dense>

#include "catch.hpp"
#include "gmsh.h"
#include "material_points.h"
#include "regression_global.h"

//! Alias for JSON
#include "json.hpp"
using json = nlohmann::json;

//! \brief Check that IO will store right values
TEST_CASE("GMSH is checked in 3D", "[GMSH][3D]") {

  //! 3D Test of IO Class
  const unsigned DIM = 3;
  const double tolerance = 1.E-12;

  //! Make json object with material in it
  std::vector<json> material_json;
  json material_properties = {{"density", 2000}, {"k0", 0.5}};
  material_json.emplace_back(material_properties);

  //! Make pointers to mesh and MaterialProperties
  auto mesh = std::unique_ptr<Mesh<3, 8>>(new GMSH<3, 8>());
  std::vector<std::unique_ptr<MaterialProperties>> material;

  for (unsigned i = 0; i < material_json.size(); i++) {
    material.emplace_back(std::unique_ptr<MaterialProperties>(
        new MaterialProperties(material_json[i])));
  }

  mesh->read_mesh(filename);
  mesh->generate_material_points(1);
  mesh->assign_material_properties(std::move(material));
  mesh->compute_stresses();

  //! Check number of vertices
  REQUIRE(mesh->nvertices() == 18);

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
  REQUIRE(coordinates.size() == 4);
  REQUIRE(stresses.size() == 4);
  REQUIRE(volumes.size() == 4);
  REQUIRE(global_ids.size() == 4);

  //! Check id
  REQUIRE(global_ids.at(0) == 0);
  REQUIRE(global_ids.at(1) == 1);
  REQUIRE(global_ids.at(2) == 2);
  REQUIRE(global_ids.at(3) == 3);

  //! Check coordinates
  REQUIRE(coordinates.at(0)[0] == Approx(0.25).epsilon(tolerance));
  REQUIRE(coordinates.at(0)[1] == Approx(0.50).epsilon(tolerance));
  REQUIRE(coordinates.at(0)[2] == Approx(0.25).epsilon(tolerance));
  REQUIRE(coordinates.at(1)[0] == Approx(0.25).epsilon(tolerance));
  REQUIRE(coordinates.at(1)[1] == Approx(0.50).epsilon(tolerance));
  REQUIRE(coordinates.at(1)[2] == Approx(0.75).epsilon(tolerance));
  REQUIRE(coordinates.at(2)[0] == Approx(0.75).epsilon(tolerance));
  REQUIRE(coordinates.at(2)[1] == Approx(0.50).epsilon(tolerance));
  REQUIRE(coordinates.at(2)[2] == Approx(0.25).epsilon(tolerance));
  REQUIRE(coordinates.at(3)[0] == Approx(0.75).epsilon(tolerance));
  REQUIRE(coordinates.at(3)[1] == Approx(0.50).epsilon(tolerance));
  REQUIRE(coordinates.at(3)[2] == Approx(0.75).epsilon(tolerance));

  //! Check stress
  REQUIRE(stresses.at(0)[0] == Approx(-4905).epsilon(tolerance));
  REQUIRE(stresses.at(0)[1] == Approx(-4905).epsilon(tolerance));
  REQUIRE(stresses.at(0)[2] == Approx(-9810).epsilon(tolerance));
  REQUIRE(stresses.at(0)[3] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(0)[4] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(0)[5] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(1)[0] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(1)[1] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(1)[2] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(1)[3] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(1)[4] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(1)[5] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(2)[0] == Approx(-4905).epsilon(tolerance));
  REQUIRE(stresses.at(2)[1] == Approx(-4905).epsilon(tolerance));
  REQUIRE(stresses.at(2)[2] == Approx(-9810).epsilon(tolerance));
  REQUIRE(stresses.at(2)[3] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(2)[4] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(2)[5] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(3)[0] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(3)[1] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(3)[2] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(3)[3] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(3)[4] == Approx(0).epsilon(tolerance));
  REQUIRE(stresses.at(3)[5] == Approx(0).epsilon(tolerance));

  //! Check volume
  REQUIRE(volumes.at(0) == Approx(0.25).epsilon(tolerance));
  REQUIRE(volumes.at(1) == Approx(0.25).epsilon(tolerance));
  REQUIRE(volumes.at(2) == Approx(0.25).epsilon(tolerance));
  REQUIRE(volumes.at(3) == Approx(0.25).epsilon(tolerance));
}