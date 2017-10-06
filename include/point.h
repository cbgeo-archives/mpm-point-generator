#ifndef MPM_MESH_POINT_H_
#define MPM_MESH_POINT_H_

#include <limits>

#include <eigen3/Eigen/Dense>

//! \brief Point class to store vertex coordinates & id
//! \tparam Tdim dimension
template <unsigned Tdim>
class Point {
 public:
  //! Constructor with id and coordinates
  //! \param[in] id index of the vertex
  //! \param[in] coord Coordinates of the point
  Point(unsigned id, unsigned global_id, const Eigen::VectorXd& coord)  {
    id_ = id;
    global_id_ = id;
    coordinates_ = coord;
  }

  //! Return the id of the point
  unsigned id() const { return id_; }

  //! Return the global id of the point
  unsigned global_id() const { return global_id_; }

  //! Return coordinates of the point
  Eigen::VectorXd coordinates() const { return coordinates_; }

  //! Return stresses of the point
  Eigen::VectorXd stress() const { return stress_; }

  //! Assign stress
  void stress(const Eigen::VectorXd stress) { stress_ = stress; }

 private:
  //! local index
  unsigned id_ = std::numeric_limits<unsigned>::max();

  //! global index
  unsigned global_id_ = std::numeric_limits<unsigned>::max();

  //! Coordinates
  Eigen::VectorXd coordinates_;
  //! Stress
  Eigen::VectorXd stress_;
};

#endif  // MPM_MESH_POINT_H_
