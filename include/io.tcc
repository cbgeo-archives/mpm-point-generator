//! \brief Write output file for point
//! \details Get stress vector of vertex coordinates, and number of vertices
void IO::write_vertices(
    const std::vector<std::shared_ptr<Point<3>>>& vertices) {

  //! Output vertices file
  std::fstream vertices_file;
  vertices_file.open(vertices_filename_, std::ios::out);

  if (vertices_file.is_open()) {
    //! Write the total number of vertices
    vertices_file << vertices.size() << "\n";

    //! Write the coordinates of the vertices
    //! [X] [Y] [Z]
    //! Note that for 2D, z values are 0
    //! For 1D, both y and z values are 0
    for (auto const& vertex : vertices) {
      for (double coordinate : vertex->coordinates()) {
        vertices_file << coordinate << "\t";
      }
      vertices_file << "\n";
    }
    vertices_file.close();
  }

  std::cout << "Wrote material point coordinates\n";
}

//! \brief Write initial stresses of material points
//! \param[in[ stresses Initial stress of material points
void IO::write_stresses(const std::vector<std::array<double, 6>>& stresses) {

  //! Output stress file
  std::fstream stress_file;
  stress_file.open(stress_filename_, std::ios::out);

  if (stress_file.is_open()) {
    //! Write the total number of vertices generated
    stress_file << stresses.size() << "\n";

    //! Stresses in Voigt Notation
    //! $\sigma_{xx}$ $\sigma_{yy}$ $\sigma_{zz}$
    //! $\tau_{yz}$ $\tau_{zx}$ $\tau_{xy}$
    for (const auto& stress : stresses) {
      stress_file.setf(std::ios::fixed, std::ios::floatfield);
      for (double stress_component : stress) {
        stress_file << stress_component << '\t';
      }
      stress_file << "\n";
    }
    stress_file.close();
  }
  std::cout << "Wrote initial stresses\n";
}
