// GMSH test
#include <array>
#include <limits>
#include <vector>

#include <eigen3/Eigen/Dense>

#include "catch.hpp"
#include "gmsh.h"
#include "material_points.h"

//! Alias for JSON
#include "json.hpp"
using json = nlohmann::json;

//! \brief Check that IO will store right values
TEST_CASE("GMSH is checked in 2D", "[GMSH][2D]") {

  //! 3D Test of IO Class
  const unsigned DIM = 2;
  const double tolerance = 1.E-12;

  //! Make json object with material in it
  std::vector<json> material_json;
  json material_properties = {{"density", 2000}, {"k0", 0.5}};
  material_json.emplace_back(material_properties);

  //! Make pointers to mesh and MaterialProperties
  auto mesh = std::unique_ptr<Mesh<2, 4>>(new GMSH<2, 4>());
  std::vector<std::unique_ptr<MaterialProperties>> material;

  for (unsigned i = 0; i < material_json.size(); i++) {
    material.emplace_back(
        std::make_unique<MaterialProperties>(material_json[i]));
  }

  const std::string filename = "../bin/plate.msh";
  mesh->read_mesh(filename);
  mesh->generate_material_points(1);
  mesh->assign_material_properties(std::move(material));
  mesh->compute_stresses();

  //! Check number of vertices
  REQUIRE(mesh->nvertices() == 106);

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
  // TODO
  REQUIRE(coordinates.size() == 43);
  REQUIRE(stresses.size() == 43);
  REQUIRE(volumes.size() == 43);
  REQUIRE(global_ids.size() == 43);

  //! Check id
  REQUIRE(global_ids.at(0) == 0);
  REQUIRE(global_ids.at(1) == 1);

  //! Check coordinates
  REQUIRE(coordinates.at(0)[0] == Approx(0.6972644851).epsilon(tolerance*1000));
  REQUIRE(coordinates.at(0)[1] == Approx(0.6750020874).epsilon(tolerance*1000));

  //! Check volume
  REQUIRE(volumes.at(0) == Approx(0.2166961155).epsilon(tolerance*1000));
}
