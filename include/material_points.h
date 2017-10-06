#ifndef MPM_MESH_MATERIAL_POINTS_H_
#define MPM_MESH_MATERIAL_POINTS_H_

#include <memory>
#include <utility>
#include <vector>

#include <eigen3/Eigen/Dense>

#include "material_properties.h"
#include "point.h"

//! \brief MaterialPoints class to store Point class and associated materials
//! \tparam Tdim dimension
template <unsigned Tdim>
class MaterialPoints {
 public:
  MaterialPoints(unsigned id) : id_{id} {}

  //! Add points within this subset of MaterialPoints
  void add_points(const std::shared_ptr<Point<Tdim>>& point) {
    points_.push_back(point);
  }

  //! Add material properties
  //! Read and store material properties
  void add_material_properties(const std::string& filename) {
    material_properties_ = std::make_shared<MaterialProperties>(filename);
    ;
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
  std::vector<std::shared_ptr<Point<Tdim>>> points_;

  //! material properties associated with the vector of points
  std::shared_ptr<MaterialProperties> material_properties_;
};

#include "material_points.tcc"

#endif  // MPM_MESH_MATERIAL_POINTS_H_
