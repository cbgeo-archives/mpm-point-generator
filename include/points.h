#ifndef MPM_MESH_POINTS_H_
#define MPM_MESH_POINTS_H_

#include <memory>
#include <utility>
#include <vector>

#include <eigen3/Eigen/Dense>

#include "point.h"
#include "material_properties.h"

//! \brief Points class to store Point class and associated materials
//! \tparam Tdim dimension
template <unsigned Tdim>
class Points {
 public:
  //! Constructor with point and materialproperties
  //! \param[in] point - Class Point
  //! \param[in] material_properties - Class MaterialProperties
  Points(const Point<Tdim>& point, const MaterialProperties& material_properties) {
    std::pair <std::shared_ptr<Point<Tdim>>, std::shared_ptr<MaterialProperties>> temp(point, material_properties);
    points_.push_back(temp);   
  }

  //! Update points
  void add_points(std::shared_ptr<Point<Tdim>> point, std::shared_ptr<MaterialProperties> material_properties) {
    std::pair <std::shared_ptr<Point<Tdim>>, std::shared_ptr<MaterialProperties>> temp(point, material_properties);
    points_.push_back(temp);    
  }

  //! Return vector of points
  std::vector<std::pair<std::shared_ptr<Point<Tdim>>, 
                        std::shared_ptr<MaterialProperties>>> get_points() const { return points_; }

  //! Assign stress
  void compute_stress();

 private:
  //! Points
  std::vector<std::pair<std::shared_ptr<Point<Tdim>>, 
                        std::shared_ptr<MaterialProperties>>> points_; 

};

#endif  // MPM_MESH_POINTS_H_
