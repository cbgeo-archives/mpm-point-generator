#ifndef MPM_MESH_POINT_H_
#define MPM_MESH_POINT_H_

#include <limits>

#include <eigen3/Eigen/Dense>

//! \brief Point class to store vertex coordinates & id
//! \tparam Tdim dimension
template <unsigned Tdim>
class Point {
 public:
  //! Constructor with global id, id and coordinates
  //! \param[in] id index of the vertex
  //! \param[in] coord Coordinates of the point
  Point(unsigned global_id, unsigned id, const Eigen::VectorXd& coord,
        double volume) {
    global_id_ = global_id;
    id_ = id;
    coordinates_ = coord;
    volume_ = volume;
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

  //! Return volume
  double volume() const { return volume_; }

 private:
  //! local index
  unsigned id_{std::numeric_limits<unsigned>::max()};

  //! global index
  unsigned global_id_{std::numeric_limits<unsigned>::max()};

  //! Coordinates
  Eigen::VectorXd coordinates_;

  //! Stress
  Eigen::VectorXd stress_;

  //! Volume
  double volume_{std::numeric_limits<double>::max()};
};

#endif  // MPM_MESH_POINT_H_
