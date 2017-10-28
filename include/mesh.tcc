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

//! Return a vector of vertice coordinates
//! \tparam Tdim Dimension of the mesh
//! \tparam Tvertices Number of vertices in an element
template <unsigned Tdim, unsigned Tvertices>
std::vector<Eigen::VectorXd> Mesh<Tdim, Tvertices>::vertices() {

  std::vector<Eigen::VectorXd> vertices;

  // Iterate over the map of vertices_
  for (std::map<unsigned, Eigen::VectorXd>::iterator it = vertices_.begin();
       it != vertices_.end(); ++it)
    vertices.emplace_back(it->second);

  return vertices;
}

//! Return a vector of elements containing vertices number
//! \tparam Tdim Dimension of the mesh
//! \tparam Tvertices Number of vertices in an element
template <unsigned Tdim, unsigned Tvertices>
std::vector<Eigen::VectorXd> Mesh<Tdim, Tvertices>::elements() {

  std::vector<Eigen::VectorXd> elements;

  // Iterate over the elements_
  for (const auto& element : elements_) {
    elements.emplace_back(element->vertices());
  }
  return elements;
}

//! Assign material properties to MaterialPoints
//! \tparam Tdim Dimension of the mesh
//! \tparam Tvertices Number of vertices in an element
//! \param[in] material pointer to MaterialProperties
template <unsigned Tdim, unsigned Tvertices>
void Mesh<Tdim, Tvertices>::assign_material_properties(
    const std::shared_ptr<MaterialProperties>& material) {

  for (const auto& materialpoint : materialpoints_) {
    materialpoint->assign_material_properties(material);
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

//! Compute initial volume of material points
//! \tparam Tdim Dimension of the mesh
//! \tparam Tvertices Number of vertices in an element
template <unsigned Tdim, unsigned Tvertices>
void Mesh<Tdim, Tvertices>::compute_volumes() {

  unsigned arrayposition = 0;

  double volume = 0;
  std::array<double, Tdim> volumearray;

  for (const auto& element : elements_) {

    unsigned id = element->id();

    volumes_.insert(std::make_pair<unsigned, double>(
        static_cast<int>(id),
        static_cast<double>(element->calculate_volume())));
  }

  std::cout << "Number of Volumes: " << volumes_.size() << '\n';
}
