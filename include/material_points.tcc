//! Read and store material properties
//! \tparam Tdim Dimension
//! \tparam Tvertices Number of vertices in element
//! \param[in] filename of material properties (initial input json file)
template <unsigned Tdim>
void MaterialPoints<Tdim>::add_material_properties(const std::string& filename) {

  std::ifstream file;
  std::shared_ptr<MaterialProperties> material_properties;
  file.open(filename.c_str(), std::ios::in);

  if (!file.is_open())
    throw std::runtime_error(
        "Specified material properties file does not exist");
  if (file.good()) {
    json j;
    file >> j;
    double density = j["MaterialProperties"]["density"].get<double>();
    double k0 = j["MaterialProperties"]["k0"].get<double>();
    unsigned nmaterials_ = j["nMaterial"].get<unsigned>();
    
    //! Store it to private variables
    material_properties_ = std::make_shared<MaterialProperties>(density, k0);
  }
  file.close();


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