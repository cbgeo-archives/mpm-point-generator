//! Constructor with json input file
//! Read json file, get mesh_filename and output_directory
//! \param[in] json input directory
//! \param[in] json input file name
template <unsigned Tdim>
IO<Tdim>::IO(const std::string& file_directory, const std::string& json_file)
    : file_directory_{file_directory} {

  json_filename_ = file_directory_ + json_file;

  //! Check if json file is present
  std::ifstream inputFile(json_filename_);

  try {
    if (!inputFile.is_open())
      throw std::runtime_error(
          std::string("Input file not found in specified location: ") +
          json_filename_);
  } catch (const std::runtime_error& except) {
    std::cerr << "Exception opening/reading json file";
  }

  //! Store json object as private variable
  //! Read json file and store to private variables
  json_ = json::parse(inputFile);

  //! Store json object for material properties
  //! IO handles null json object by making empty json object
  //! MaterialProperties class could handle empty json object
  if (!json_["material_properties"].is_null()) {
    json_material_properties_ = json_["material_properties"];
  } else {
    std::cout << "No material properties specified, using default\n";
    json_material_properties_.clear();
  }

  //! Check if mesh file is present
  mesh_filename_ =
      file_directory_ + json_["mesh_file"].template get<std::string>();
  std::ifstream meshfile;
  meshfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    meshfile.open(mesh_filename_);
  } catch (const std::ifstream::failure& except) {
    std::cerr << "Exception opening/reading mesh file";
  }
  meshfile.close();

  //! Read and store number of gauss points per coordinate
  //! If not specified, set default value of 1
  try {
    if (json_.at("ngauss_points").size())
      ngauss_points_ = json_["ngauss_points"].template get<unsigned>();
  } catch (json::out_of_range& out_of_range) {
    std::cerr << out_of_range.what() << '\n';
    std::cout << "ngauss_points not specified. Using a default value of 1\n";
    ngauss_points_ = 1;
  }
}

//! \brief Write coordinates of material points
//! \details Write point coordinates
//! \tparam Tdim dimension
template <unsigned Tdim>
void IO<Tdim>::write_coordinates(
    const std::vector<Eigen::VectorXd>& coordinates) {

  const auto filename = this->output_file("material_points", ".txt").string();
  std::cout << "material points will be stored in: "
            << filename << "\n";

  //! Output vertices file
  std::fstream material_points_file;
  material_points_file.open(filename, std::ios::out);

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

//! \brief Write initial stresses of material points
//! \Param[in] stresses is initial stress of material points
//! \tparam Tdim dimension
template <unsigned Tdim>
void IO<Tdim>::write_stresses(const std::vector<Eigen::VectorXd>& stresses) {
  unsigned id = 0;

  const auto filename = this->output_file("initial_stresses", ".txt").string();

  std::cout << "initial stresses will be stored in: "
            << filename << "\n";

  //! Output stress file
  std::fstream stress_file;
  stress_file.open(filename, std::ios::out);

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

//! \brief Write output file names and store them in private member
//! \param[in] attribute Attribute being written (eg., material_points / stress)
//! \param[in] file_extension File Extension (*.txt)
//! \tparam Tdim dimension
template <unsigned Tdim>
boost::filesystem::path IO<Tdim>::output_file(
    const std::string& attribute, const std::string& file_extension) {

  std::stringstream file_name;
  std::string path{"results/"};

  try {
    auto results = json_.at("results_path");
    if (!results.empty()) path = results;

  } catch (std::exception& except) {
    std::cerr << except.what() << '\n';
    // console_->error("Output file creation: {}", except.what());
    // console_->warn("Using default path: {}", path);
  }

  //! Make the file_name
  file_name.str(std::string());
  file_name << attribute << file_extension;

  //! Include path
  if (!path.empty()) path = file_directory_ + path;

  //! Create results folder if not present
  boost::filesystem::path dir(path);
  if (!boost::filesystem::exists(dir)) boost::filesystem::create_directory(dir);

  //! Create full path with working directory path and file name
  boost::filesystem::path file_path(path + file_name.str().c_str());
  return file_path;
}

//! \brief Write volumes
//! \param[in] volumes Map of point id and the corresponding volume
//! \tparam Tdim dimension
template <unsigned Tdim>
void IO<Tdim>::write_volumes(const std::map<unsigned, double>& volumes) {

  unsigned id = 0;

  const auto filename = this->output_file("volumes", ".txt").string();
  std::cout << "initial volumes will be stored in: "
            << filename << "\n";

  //! Output stress file
  std::fstream volume_file;
  volume_file.open(filename, std::ios::out);

  if (volume_file.is_open()) {
    //! Write the total number of vertices generated
    volume_file << volumes.size() << "\n";

    //! write element id and volume
    for (const auto& volume : volumes) {
      volume_file << id << '\t' << volume.second;
      volume_file << "\n";
      ++id;
    }
    volume_file.close();
  }
  std::cout << "Wrote Volumes \n";
}
