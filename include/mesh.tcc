//! Return a vector of coordinates
//! \tparam Tdim Dimension of the mesh
//! \tparam Tvertices Number of vertices in an element
template <unsigned Tdim, unsigned Tvertices>
std::vector<Eigen::VectorXd> Mesh<Tdim, Tvertices>::coordinates() {

  std::vector<Eigen::VectorXd> coordinates;

  // Iterate over materialpoints_ to get coordinates
  for (const auto& materialpoint : materialpoints_) {
    for (const auto& coordinate : materialpoint->coordinates()) {
      coordinates.emplace_back(coordinate);
    }
  }
  return coordinates;
}

//! Return a vector of stresses
//! \tparam Tdim Dimension of the mesh
//! \tparam Tvertices Number of vertices in an element
template <unsigned Tdim, unsigned Tvertices>
std::vector<Eigen::VectorXd> Mesh<Tdim, Tvertices>::stress() {

  std::vector<Eigen::VectorXd> stresses;

  // Iterate over materialpoints_ to get stress
  for (const auto& materialpoint : materialpoints_) {
    for (const auto& stress : materialpoint->stress()) {
      stresses.emplace_back(stress);
    }
  }
  return stresses;
}

//! Add material properties from json object
//! \tparam Tdim Dimension of the mesh
//! \tparam Tvertices Number of vertices in an element
//! \param[in] jsonfile contains material properties that will be parsed in MaterialPoints
template <unsigned Tdim, unsigned Tvertices>
void Mesh<Tdim, Tvertices>::add_material_properties(const json& jsonfile) {

  for (const auto& materialpoint : materialpoints_) {
    materialpoint->add_material_properties(jsonfile);
  }
}

//! Compute stress of material points
//! \tparam Tdim Dimension of the mesh
//! \tparam Tvertices Number of vertices in an element
template <unsigned Tdim, unsigned Tvertices>
void Mesh<Tdim, Tvertices>::compute_stresses() {

  for (const auto& materialpoint : materialpoints_) {
    materialpoint->compute_stress();
  }
}