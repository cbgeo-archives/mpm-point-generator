//! Return vector of coordinates
//! \tparam Tdim Dimension
template <unsigned Tdim>
std::vector<Eigen::VectorXd> MaterialPoints<Tdim>::coordinates() {

  std::vector<Eigen::VectorXd> coordinates;

  //! Loop through the points to get the stresses
  for (const auto& materialpoint : points_) {
    coordinates.emplace_back(materialpoint->coordinates());
  }

  return coordinates;
}

//! Return vector of stress
//! \tparam Tdim Dimension
template <unsigned Tdim>
std::vector<Eigen::VectorXd> MaterialPoints<Tdim>::stress() {

  std::vector<Eigen::VectorXd> stress;

  //! Loop through the points to get the stresses
  for (const auto& materialpoint : points_) {
    stress.emplace_back(materialpoint->stress());
  }

  return stress;
}

//! Compute stresses of the material points
//! \tparam Tdim Dimension
template <unsigned Tdim>
void MaterialPoints<Tdim>::compute_stress() {

  //! Gravity
  const double conv_factor = 9.81;

  double max_height = std::numeric_limits<double>::min();

  //! [2D], y is the vertical direction
  //! [3D], z is the vertical direction
  //! In general, [Tdim - 1]
  for (const auto& point : points_) {
    if (point->coordinates()[Tdim - 1] > max_height) {
      max_height = point->coordinates()[Tdim - 1];
    }
  }

  //! Loop through the points to get vertical and horizontal stresses
  //! Note that tau (shear stress) is assumed 0
  //! [2D], y is the vertical direction
  //! [3D], z is the vertical direction
  for (const auto& point : points_) {
    Eigen::VectorXd stress(Tdim * 2);
    stress.setZero();

    stress[Tdim - 1] = conv_factor *
                       (-(max_height - point->coordinates()[Tdim])) *
                       material_properties_->density();

    for (unsigned i = 2; i <= Tdim; ++i) {
      stress[Tdim - i] = stress[Tdim - 1] * material_properties_->k0();
    }

    point->stress(stress);
  }
}