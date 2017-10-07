//! Constructor with json input file
//! Get mesh_filename and output_directory
//! \param[in] json input file name
template <unsigned Tdim>
IO<Tdim>::IO(const std::string& file_directory, const std::string& json_file)
    : file_directory_{file_directory} {

  json_filename_ = file_directory_ + json_file;

  //! Check if json file is present
  std::ifstream inputFile(json_filename_);
  inputFile.exceptions(std::ifstream::badbit);

  // //! Store json object as private variable
  // //! Read json file and store to private variables
  inputFile >> json_file_;
  std::string filename = json_file_["mesh_file"].get<std::string>();
  mesh_filename_ = file_directory_ + filename;

  //! Check if mesh file is present
  std::ifstream meshfile;
  meshfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    meshfile.open(mesh_filename_);
  } catch (const std::ifstream::failure& except) {
    std::cerr << "Exception opening/reading mesh file";
  }
  meshfile.close();

  //! Material point and stresses output file
  material_points_filename_ = file_directory_ + "material_points.txt";
  stress_filename_ = file_directory_ + "initial_stresses.txt";
}

//! \brief output coordinates of material points
//! \details Get vector of point coordinates
//! \tparam Tdim dimension
template <unsigned Tdim>
void IO<Tdim>::write_point_coordinates(
    const std::vector<Eigen::VectorXd>& coordinates) {

  std::cout << "material_points will be stored in: " << file_directory_ << "\n";

  //! Output vertices file
  std::fstream material_points_file;
  material_points_file.open(material_points_filename_, std::ios::out);

  if (material_points_file.is_open()) {
    //! Write the total number of vertices
    material_points_file << coordinates.size() << "\n";

    //! Write the coordinates of the vertices
    //! [X] [Y] [Z]
    //! Note that for 2D, z values are 0
    //! For 1D, both y and z values are 0
    for (auto const& coordinate : coordinates) {
      for (unsigned i = 0; i < coordinate.size(); ++i) {
        material_points_file << coordinate[i] << "\t";
      }
      material_points_file << "\n";
    }
    material_points_file.close();
  }

  std::cout << "Wrote material point coordinates\n";
}

//! \brief output initial stresses of material points
//! \Param[in] stresses Initial stress of material points
//! /tparam Tdim dimension
template <unsigned Tdim>
void IO<Tdim>::write_stresses(const std::vector<Eigen::VectorXd>& stresses) {
  unsigned id = 0;

  std::cout << "initial_stresses will be stored in: " << file_directory_
            << "\n";

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
      for (unsigned i = 0; i < stress.size(); ++i) {
        stress_file << stress[i] << "\t";
      }
      stress_file << "\n";
      ++id;
    }
    stress_file.close();
  }
  std::cout << "Wrote initial stresses\n";
}