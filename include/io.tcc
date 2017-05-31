//! \brief Write output file for point
//! \details Get stress vector of vertex coordinates, and number of vertices
void IO::write_vertices(
    const std::vector<std::shared_ptr<Point<3>>>& vertices) {

  //! Open file to write output
  std::fstream outputfile;
  outputfile.open(outputfilename_vertex_, std::ios::out);
  if (outputfile.is_open()) {

    //! Write the total number of vertices generated
    outputfile << vertices.size() << "\n";

    //! Write the coordinates of the vertices generated
    //! [X] [Y] [Z]
    //! Note that for 2D, z values are 0
    //! For 1D, both y and z values are 0
    for (auto const& point : vertices) {
      for (double coordinate : point->coordinates()) {
        outputfile << coordinate << "\t";
      }
      outputfile << "\n";
    }
    outputfile.close();
  }

  std::cout << "The output file for soil particles has been generated.\n";
}

//! \brief Write output file for stress
//! \details get stress vector of Voigt stress, and number of vertices
//! \brief Write output file for stress
void IO::write_stresses(const std::vector<std::array<double, 6>>& stress) {

  //! Open file to write output
  std::fstream outputfile;
  outputfile.open(outputfilename_stress_, std::ios::out);

  if (outputfile.is_open()) {

    //! Write the total number of vertices generated
    outputfile << stress.size() << "\n";

    //! stress_ is the array of stresses in Voigt Notation
    //! id  sig_x  sig_y  sig_z  tau_yz  tau_zx  tau_xy
    for (const auto& point : stress) {
      outputfile.setf(std::ios::fixed, std::ios::floatfield);
      for (double stress_component : point) {
        outputfile << stress_component << '\t';
      }
      outputfile << "\n";
    }
    outputfile.close();
  }
  std::cout << "The output file for initial stresses of particles has been "
               "generated.\n";
}
