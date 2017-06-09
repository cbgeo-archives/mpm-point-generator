//! \brief Write output file for point
//! \details Get stress vector of vertex coordinates, and number of vertices
void IO::write_vertices(
    const std::vector<std::shared_ptr<Point<3>>>& materialpoints) {

  //! Output vertices file
  std::fstream vertices_file;
  vertices_file.open(vertices_filename_, std::ios::out);

  if (vertices_file.is_open()) {
    //! Write the total number of vertices
    vertices_file << materialpoints.size() << "\n";

    //! Write the coordinates of the vertices
    //! [X] [Y] [Z]
    //! Note that for 2D, z values are 0
    //! For 1D, both y and z values are 0
    for (auto const& points : materialpoints) {
      for (double coordinate : points->coordinates()) {
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
  unsigned id = 0;

  //! Output stress file
  std::fstream stress_file;
  stress_file.open(stress_filename_, std::ios::out);

  if (stress_file.is_open()) {
    //! Write the total number of vertices generated
    stress_file << stresses.size() << "\n";

    //! Stresses in Voigt Notation
    // Stress needs ID too
    //! $\sigma_{xx}$ $\sigma_{yy}$ $\sigma_{zz}$
    //! $\tau_{yz}$ $\tau_{zx}$ $\tau_{xy}$
    for (const auto& stress : stresses) {
      stress_file.setf(std::ios::fixed, std::ios::floatfield);
      stress_file << id << '\t';
      for (double stress_component : stress) {
        stress_file << stress_component << '\t';
      }
      stress_file << "\n";
      ++id;
    }
    stress_file.close();
  }
  std::cout << "Wrote initial stresses\n";
}
