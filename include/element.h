#ifndef MPM_ELEMENT_H
#define MPM_ELEMENT_H

#include <map>
#include <vector>

#include <eigen3/Eigen/Dense>

//! Namespace containing required global constants / functions
//! Used in computing material points
namespace element {

//! Map to store gauss points coefficients
const std::map<unsigned, std::vector<double>> gauss_points{
    {1, {0}},
    {2, {-0.5773502691896257, 0.5773502691896257}},
    {3, {-0.7745966692414834, 0, 0.7745966692414834}},
    {4,
     {-0.8611363115940526, -0.3399810435848563, 0.3399810435848563,
      0.8611363115940526}},
    {5,
     {-0.9061798459386640, -0.5384693101056831, 0, 0.5384693101056831,
      0.9061798459386640}}};

//! Namespace conatining shape functions for 8-node hexahedron
namespace hexahedron {

//! Compute shape function of hexahedron at different coordinates xi
//! \param[in] xi array of coordinates in mapped coordinate
inline Eigen::VectorXd shapefn(const std::array<double, 3>& xi) {
  Eigen::VectorXd shapefn_(8);

  shapefn_[0] = 0.125 * (1 - xi.at(0)) * (1 - xi.at(1)) * (1 - xi.at(2));
  shapefn_[1] = 0.125 * (1 + xi.at(0)) * (1 - xi.at(1)) * (1 - xi.at(2));
  shapefn_[2] = 0.125 * (1 + xi.at(0)) * (1 + xi.at(1)) * (1 - xi.at(2));
  shapefn_[3] = 0.125 * (1 - xi.at(0)) * (1 + xi.at(1)) * (1 - xi.at(2));
  shapefn_[4] = 0.125 * (1 - xi.at(0)) * (1 - xi.at(1)) * (1 + xi.at(2));
  shapefn_[5] = 0.125 * (1 + xi.at(0)) * (1 - xi.at(1)) * (1 + xi.at(2));
  shapefn_[6] = 0.125 * (1 + xi.at(0)) * (1 + xi.at(1)) * (1 + xi.at(2));
  shapefn_[7] = 0.125 * (1 - xi.at(0)) * (1 + xi.at(1)) * (1 + xi.at(2));

  return shapefn_;
}
}

//! Namespace conatining shape functions for 4-node quadrilateral
namespace quadrilateral {

//! Compute shape function of quadrilateral at different coordinates xi
//! \param[in] xi array of coordinates in mapped coordinate
inline Eigen::VectorXd shapefn(const std::array<double, 2>& xi) {
  Eigen::VectorXd shapefn_(4);

  shapefn_[0] = 0.25 * (1 - xi.at(0)) * (1 - xi.at(1));
  shapefn_[1] = 0.25 * (1 + xi.at(0)) * (1 - xi.at(1));
  shapefn_[2] = 0.25 * (1 + xi.at(0)) * (1 + xi.at(1));
  shapefn_[3] = 0.25 * (1 - xi.at(0)) * (1 + xi.at(1));

  return shapefn_;
}
}
};

//! Element class to hold element vertices id and coordinates
//! \param[in] element id
//! \param[in] vertices id
//! \param[in] coordinates
class Element {

 public:
  //! constructor for Element class
  //! \param[in] element id and vertices id's
  Element(unsigned id, const Eigen::VectorXd& vertices) : id_{id} {

    vertices_ = vertices;
  }

  //! Calculate volume of element
  double calculate_volume();

  //! Pass element vertices coordinates from mesh to element class
  //!\param[in] coordinates of all element vertices
  void coordinates(const std::vector<Eigen::Vector3d>& coordinates) {

    coordinates_ = coordinates;
  }

  //! Return element id
  unsigned id() const { return id_; }

  //! Return coordinates of a vertex
  Eigen::Vector3d vertex_coordinates(unsigned vid) const {
    return coordinates_.at(vid);
  }

  //! Return coordinates of the point
  Eigen::VectorXd vertices() const { return vertices_; }

  //! return id of an element vertex
  unsigned vertex_id(unsigned vid) const { return vertices_[vid]; }

 private:
  //! element id
  unsigned id_;

  //! vector of element vertices id's
  Eigen::VectorXd vertices_;

  //! vector of element vertices coordinates
  std::vector<Eigen::Vector3d> coordinates_;
};

#endif  // MPM_ELEMENT_H
