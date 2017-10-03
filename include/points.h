#ifndef MPM_MESH_POINTS_H_
#define MPM_MESH_POINTS_H_

#include <memory>
#include <utility>
#include <vector>

#include <eigen3/Eigen/Dense>

#include "material_properties.h"
#include "point.h"

//! \brief Points class to store Point class and associated materials
//! \tparam Tdim dimension
template <unsigned Tdim>
class Points {
 public:
  //! Update points
  void add_points(std::shared_ptr<Point<Tdim>> point,
                  std::shared_ptr<MaterialProperties> material_properties) {
    points_.emplace_back(std::make_pair(point, material_properties));
  }

  //! Return vector of points
  std::vector<std::pair<std::shared_ptr<Point<Tdim>>,
                        std::shared_ptr<MaterialProperties>>>
      get_points() const {
    return points_;
  }

  //! Compute stress
  void compute_stress();

 private:
  //! Points vector
  std::vector<std::pair<std::shared_ptr<Point<Tdim>>,
                        std::shared_ptr<MaterialProperties>>>
      points_;
};

#include "points.tcc"

#endif  // MPM_MESH_POINTS_H_
