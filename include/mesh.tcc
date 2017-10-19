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

  const unsigned firstelementcoord = elementcoordinates_.begin()->first;
  const unsigned lastelementcoord = elementcoordinates_.rbegin()->first;

  for (unsigned t = firstelementcoord; t < lastelementcoord + 1; ++t) {
    auto coordinatesfind = elementcoordinates_.find(t);
    if (coordinatesfind != elementcoordinates_.end()) {
      //! Store coordinates in 3x8 matrix
      Eigen::MatrixXd m(Tdim, Tvertices);
      for (unsigned i = 0; i < Tvertices; ++i) {
        for (unsigned j = 0; j < Tdim; ++j) {
          arrayposition = (i * Tdim) + j;
          m(j, i) = coordinatesfind->second[arrayposition];
        }
      }

      volumes_.insert(
          std::make_pair(coordinatesfind->first, calculate_volume(m)));
    }
  }
  std::cout << "Number of Volumes: " << volumes_.size() << '\n';
}

//! Calculate volume of an element
//! \tparam Tdim Dimension of the mesh
//! \tparam Tvertices Number of vertices in an element
//! \param[in] 3x8 Matrix of element vertices coordinates
template <unsigned Tdim, unsigned Tvertices>
double Mesh<Tdim, Tvertices>::calculate_volume(const Eigen::MatrixXd& m) {

  double volume = 0;

  /* Node numbering as read in by mesh file
   *
         0-------1
        /|      / |
       / |     /  |
      /  |    /   |
      3--|----2   |
      |  |    |   |
      |  4----|---5
      |  /    |  /
      | /     | /
      |/      |/
      7-------6

      * Calculation of hexahedron volume from
      * https://arc.aiaa.org/doi/pdf/10.2514/3.9013
   */

  Eigen::Vector3d a(m(0, 3), m(1, 3), m(2, 3)), b(m(0, 2), m(1, 2), m(2, 2)),
      c(m(0, 1), m(1, 1), m(2, 1)), d(m(0, 0), m(1, 0), m(2, 0)),
      e(m(0, 7), m(1, 7), m(2, 7)), f(m(0, 6), m(1, 6), m(2, 6)),
      g(m(0, 5), m(1, 5), m(2, 5)), h(m(0, 4), m(1, 4), m(2, 4));

  volume =
      (1.0 / 12) * (a - g).dot(((b - d).cross(c - a)) + ((e - b).cross(f - a)) +
                               ((d - e).cross(h - a))) +
      (1.0 / 12) *
          (b - g).dot(((b - d).cross(c - a)) + ((c - g).cross(c - f))) +
      (1.0 / 12) *
          (e - g).dot(((e - b).cross(f - a)) + ((f - g).cross(h - f))) +
      (1.0 / 12) * (d - g).dot(((d - e).cross(h - a)) + ((h - g).cross(h - c)));

  return volume;
}
