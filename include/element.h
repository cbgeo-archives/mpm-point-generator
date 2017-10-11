#ifndef MPM_ELEMENT_H
#define MPM_ELEMENT_H

#include <eigen3/Eigen/Dense>

namespace element {

namespace hexahedron {

Eigen::VectorXd shapefn(const std::array<double, 3>& xi) {
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

namespace quadrilateral {

Eigen::VectorXd shapefn(const std::array<double, 2>& xi) {
  Eigen::VectorXd shapefn_(4);

  shapefn_[0] = 0.25 * (1 - xi.at(0)) * (1 - xi.at(1));
  shapefn_[1] = 0.25 * (1 + xi.at(0)) * (1 - xi.at(1));
  shapefn_[2] = 0.25 * (1 + xi.at(0)) * (1 + xi.at(1));
  shapefn_[3] = 0.25 * (1 - xi.at(0)) * (1 + xi.at(1));

  return shapefn_;
}
}
};

#endif  // MPM_ELEMENT_H
