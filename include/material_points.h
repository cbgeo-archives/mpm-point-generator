#ifndef MPM_MESH_MATERIAL_POINTS_H_
#define MPM_MESH_MATERIAL_POINTS_H_

#include <memory>
#include <utility>
#include <vector>

#include <eigen3/Eigen/Dense>

#include "material_properties.h"
#include "point.h"

#include "json.hpp"

//! Short alias for convenience
using json = nlohmann::json;

//! \brief MaterialPoints class to store Point class and associated materials
//! \tparam Tdim dimension
template <unsigned Tdim>
class MaterialPoints {
 public:
  MaterialPoints(unsigned id) : id_{id} {
  }

  //! Add points within this subset of MaterialPoints
  void add_points(const std::shared_ptr<Point<Tdim>>& point) {
    points_.push_back(point);
  }

  //! Add material properties
  void add_material_properties(const std::string& filename);

  //! Compute stress
  void compute_stress();

  //! Return vector of points
  std::vector<std::shared_ptr<Point<Tdim>>> points() const {
    return points_;
  }

  //! Return material properties
  std::shared_ptr<MaterialProperties> material_properties() const {
    return material_properties_;
  }

  //! Return vector of stresses
  std::vector<Eigen::VectorXd> stress();

 private:
  //! material points id
  unsigned id_;

  //! Points vector
  std::vector<std::shared_ptr<Point<Tdim>>> points_;

  //! material properties associated with the vector of points
  std::shared_ptr<MaterialProperties> material_properties_;
};

#include "material_points.tcc"

#endif  // MPM_MESH_MATERIAL_POINTS_H_
