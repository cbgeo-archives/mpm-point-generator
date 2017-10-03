//! Compute stresses of the material points
//! \tparam Tdim Dimension
template <unsigned Tdim>
void Points<Tdim>::compute_stresses() {

  //! Gravity
  const double conv_factor = 9.81;

  double max_height = std::numeric_limits<double>::min();

  //! [2D], y is the vertical direction
  //! [3D], z is the vertical direction
  //! In general, [Tdim - 1]
  for (const auto& point : points_) {
    if (point.first->coordinates()[Tdim - 1] > max_height) {
      max_height = point.first->coordinates()[Tdim - 1];
    }
  }

  //! Loop through the points to get vertical and horizontal stresses
  //! Note that tau (shear stress) is assumed 0
  //! [2D], y is the vertical direction
  //! [3D], z is the vertical direction
  for (const auto& points : points_) {
    Eigen::VectorXd stress(Tdim * 2);
    stress.setZero();

    stress[Tdim - 1] = conv_factor *
                       (-(max_height - points.first->coordinates()[Tdim])) *
                       points.second->density();
    
    for (unsigned i = 2; i <= Tdim; ++i) {
      stress[Tdim - i] = stress[Tdim - 1] * points.second->k0();
    }

    points.first->stress(stress);
  }
}