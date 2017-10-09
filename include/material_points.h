#ifndef MPM_MESH_MATERIAL_POINTS_H_
#define MPM_MESH_MATERIAL_POINTS_H_

#include <memory>
#include <utility>
#include <vector>

#include <eigen3/Eigen/Dense>

#include "material_properties.h"
#include "point.h"

//! Alias for JSON
#include "json.hpp"
using json = nlohmann::json;

//! \brief MaterialPoints class to store Point class and associated materials
//! \tparam Tdim dimension
template <unsigned Tdim>
class MaterialPoints {
 public:
  explicit MaterialPoints(unsigned id) : id_{id} {}

  //! Add points within this subset of MaterialPoints
  void add_points(std::unique_ptr<Point<Tdim>>&& point) {
    points_.emplace_back(std::move(point));
  }

  //! Assign material properties
  //! \param[in] material pointer to MaterialProperties
  void assign_material_properties(const std::shared_ptr<MaterialProperties>& material) {
    material_properties_ = material;
  }

  //! Compute stress
  void compute_stress();

  //! Return vector of coordinates
  std::vector<Eigen::VectorXd> coordinates();

  //! Return vector of stresses
  std::vector<Eigen::VectorXd> stress();

 private:
  //! material points id
  unsigned id_{std::numeric_limits<unsigned>::max()};

  //! Points vector
  std::vector<std::unique_ptr<Point<Tdim>>> points_;

  //! material properties associated with the vector of points
  std::shared_ptr<MaterialProperties> material_properties_{nullptr};
};

#include "material_points.tcc"

#endif  // MPM_MESH_MATERIAL_POINTS_H_
