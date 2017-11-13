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
