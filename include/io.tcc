//! \brief Write output file for point
//! \details Get stress vector of vertex coordinates, and number of vertices
//! \tparam Tdim dimension
template <unsigned Tdim>
void IO<Tdim>::write_material_points(
    const std::vector<std::shared_ptr<Point<Tdim>>>& materialpoints) {

  //! Output vertices file
  std::fstream material_points_file;
  material_points_file.open(material_points_filename_, std::ios::out);

  if (material_points_file.is_open()) {
    //! Write the total number of vertices
    material_points_file << materialpoints.size() << "\n";

    //! Write the coordinates of the vertices
    //! [X] [Y] [Z]
    //! Note that for 2D, z values are 0
    //! For 1D, both y and z values are 0
    for (auto const& points : materialpoints) {
      for (unsigned i = 0; i < Tdim; ++i) {
        material_points_file << points->coordinates()[i] << "\t";
      }
      material_points_file << "\n";
    }
    material_points_file.close();
  }

  std::cout << "Wrote material point coordinates\n";
}

//! \brief Write initial stresses of material points
//! \Param[in] stresses Initial stress of material points
//! /tparam Tdim dimension
template <unsigned Tdim>
void IO<Tdim>::write_stresses(const std::vector<Eigen::VectorXd>& stresses) {
  unsigned id = 0;

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
      stress_file << id << '\t';
      for (unsigned i = 0; i < Tdim * 2; ++i) {
        stress_file << stress[i] << "\t";
      }
      stress_file << "\n";
      ++id;
    }
    stress_file.close();
  }
  std::cout << "Wrote initial stresses\n";
}
