//! Return vector of coordinates
//! \tparam Tdim Dimension
template <unsigned Tdim>
std::vector<Eigen::VectorXd> MaterialPoints<Tdim>::coordinates() {

  std::vector<Eigen::VectorXd> coordinates;

  //! Loop through the points to get the coordinates
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
  const double gravity = 9.81;

  //! Compute maximum height of the points
  //! [2D], y is the vertical direction
  //! [3D], z is the vertical direction
  //! In general, [Tdim - 1]
  double max_height = std::numeric_limits<double>::min();
  for (const auto& point : points_) {
    const double height = point->coordinates()[Tdim - 1];
    if (height > max_height) max_height = height;
  }

  //! Loop through the points to get vertical and horizontal stresses
  //! Note that tau (shear stress) is assumed 0
  //! [2D], y is the vertical direction
  //! [3D], z is the vertical direction
  for (const auto& point : points_) {

    //! Obtain density and k0 from material properties;
    const double density = material_properties_->density();
    const double k0 = material_properties_->k0();

    //! Compute the height of the point
    const double height = point->coordinates()[Tdim - 1];

    //! Compute and store stresses
    Eigen::VectorXd stress(Tdim * 2);
    stress.setZero();
    const auto coordinates = point->coordinates();
    stress[Tdim - 1] = gravity * (-(max_height - height)) * density;

    for (unsigned i = 2; i <= Tdim; ++i) {
      stress[Tdim - i] = stress[Tdim - 1] * k0;
    }

    point->stress(stress);
  }
}
