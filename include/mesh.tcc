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
std::map<unsigned, double> Mesh<Tdim, Tvertices>::calculate_volumes() {

  std::map<unsigned, double> volumes;

  for (const auto& element : elements_) {

    unsigned id = element->id();

    volumes.insert(std::make_pair<unsigned, double>(
        static_cast<int>(id),
        static_cast<double>(element->calculate_volume())));
  }

  return volumes;
}

//! \brief Output .vtk files for viewing material points
//! \details Write material points coordinates and initial stresses
//! \tparam Tdim dimension
//! \tparam Tvertices Number of vertices in an element
//! \param[in] stress_vtk_filename the directory and filename of output
template <unsigned Tdim, unsigned Tvertices>
void Mesh<Tdim, Tvertices>::write_vtk_stresses(
    boost::filesystem::path stress_vtk_filename) {

  unsigned num_points = 0;
  for (const auto& materialpoints : materialpoints_) {
    num_points += materialpoints->coordinates().size();
  }

  std::cout << "output .vtk file for initial stresses will be stored in: "
            << stress_vtk_filename.string() << "\n";

  //! Output stress file
  std::fstream stress_vtk_file;
  stress_vtk_file.open(stress_vtk_filename.string(), std::ios::out);

  //! Write .vtk file
  if (stress_vtk_file.is_open()) {
    stress_vtk_file << "# vtk DataFile Version 2.0\n";
    stress_vtk_file << "MPM_POINT_GENERATOR: Initial Stresses\n";
    stress_vtk_file << "ASCII\n";
    stress_vtk_file << "DATASET UNSTRUCTURED_GRID\n";

    stress_vtk_file << "POINTS " << num_points << " float\n";

    // Iterate over materialpoints_ to get coordinates
    for (const auto& materialpoint : materialpoints_) {
      for (const auto& coordinate : materialpoint->coordinates()) {
        stress_vtk_file << coordinate[0] << ' ' << coordinate[1] << ' '
                        << coordinate[2] << '\n';
        ;
      }
    }

    stress_vtk_file << "CELLS " << num_points << " " << 2 * num_points << '\n';
    for (unsigned i = 0; i < num_points; i++)
      stress_vtk_file << "1 " << i << '\n';

    stress_vtk_file << "CELL_TYPES " << num_points << '\n';
    for (unsigned i = 0; i < num_points; i++) stress_vtk_file << "1 " << '\n';

    stress_vtk_file << "POINT_DATA " << num_points << '\n';
    stress_vtk_file << "VECTORS Stress float\n";

    // Iterate over materialpoints_ to get stress
    for (const auto& materialpoint : materialpoints_) {
      for (const auto& stress : materialpoint->stress()) {
        if (Tdim == 2)
          stress_vtk_file << stress[0] << ' ' << stress[1] << " 0.\n";
        else if (Tdim == 3)
          stress_vtk_file << stress[0] << ' ' << stress[1] << ' ' << stress[2]
                          << '\n';
      }
    }
    stress_vtk_file.close();
  }
  std::cout << "Wrote initial stresses vtk file\n";
}

//! \brief Output .vtk files for viewing mesh
//! \details Write mesh coordinates and elements
//! \tparam Tdim dimension
//! \tparam Tvertices Number of vertices in an element
//! \param[in] mesh_vtk_filename the directory and filename of output
template <unsigned Tdim, unsigned Tvertices>
void Mesh<Tdim, Tvertices>::write_vtk_mesh(
    boost::filesystem::path mesh_vtk_filename) {

  unsigned num_vertices = vertices_.size();
  unsigned num_elements = elements_.size();

  //! Assign element_type from VTK documentation
  //! 5 - Triangle (3 nodes)
  //! 9 - Quadrangle (4 nodes)
  //! 10 - Tetrahedron (4 nodes)
  //! 12 - Hexahedron (8 nodes)
  //! For more informtion on element types, visit:
  //! https://www.vtk.org/wp-content/uploads/2015/04/file-formats.pdf
  unsigned element_type = 12;
  unsigned nodes_in_element = 8;

  std::cout << "output .vtk file for mesh will be stored in: "
            << mesh_vtk_filename.string() << "\n";

  //! Output stress file
  std::fstream mesh_vtk_file;
  mesh_vtk_file.open(mesh_vtk_filename.string(), std::ios::out);

  //! Write .vtk file
  if (mesh_vtk_file.is_open()) {
    mesh_vtk_file << "# vtk DataFile Version 2.0\n";
    mesh_vtk_file << "MPM_POINT_GENERATOR: Mesh\n";
    mesh_vtk_file << "ASCII\n";
    mesh_vtk_file << "DATASET UNSTRUCTURED_GRID\n";

    mesh_vtk_file << "POINTS " << num_vertices << " float\n";

    // Iterate over the map of vertices_
    for (std::map<unsigned, Eigen::VectorXd>::iterator it = vertices_.begin();
         it != vertices_.end(); ++it) {
      Eigen::VectorXd vertice = it->second;

      mesh_vtk_file << vertice[0] << ' ' << vertice[1] << ' ' << vertice[2]
                    << '\n';
    }

    // Note minus 1 is because element starts from 1 instead of 0
    mesh_vtk_file << "CELLS " << num_elements << " "
                  << num_elements * (nodes_in_element + 1) << '\n';

    for (const auto& element : elements_) {
      mesh_vtk_file << nodes_in_element << ' ';
      Eigen::VectorXd vertices = element->vertices();
      for (unsigned i = 0; i < nodes_in_element; ++i) {
        mesh_vtk_file << vertices[i] - 1 << ' ';
      }
      mesh_vtk_file << '\n';
    }

    mesh_vtk_file << "CELL_TYPES " << num_elements << '\n';
    for (unsigned i = 0; i < num_elements; i++)
      mesh_vtk_file << element_type << '\n';

    mesh_vtk_file.close();
  }
  std::cout << "Wrote mesh vtk file\n";
}