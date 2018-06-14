#include "io.h"

//! Constructor with argc and argv
//! \param[in] argc Number of input arguments
//! \param[in] argv Array of input arguments
IO::IO(int argc, char** argv) {

  // Set title
  TCLAP::CmdLine cmd("Material Point Generator (CB-Geo)", ' ', "0.0.1");

  // Define dimension
  //  TCLAP::ValueArg<unsigned int> dim_arg(
  //    "d", "dimension", "Problem dimension", true, 3, "Dimension");
  //  cmd.add(dim_arg);

  // Define working directory
  TCLAP::ValueArg<std::string> cwd_arg(
      "f", "working_dir", "Current working folder", true, "", "Working_folder");
  cmd.add(cwd_arg);

  // Define input file
  TCLAP::ValueArg<std::string> input_arg("i", "input_file",
                                         "Input JSON file [cube.json]", false,
                                         "cube.json", "input_file");
  cmd.add(input_arg);

  // Parse arguments
  cmd.parse(argc, argv);

  //! Set working directory
  working_dir_ = cwd_arg.getValue();

  //! Set input file if the optional argument is not empty
  const auto input_file = input_arg.getValue();

  const auto json_filename = working_dir_ + input_file;

  //! Check if json file is present
  std::ifstream inputFile(json_filename);

  try {
    if (!inputFile.is_open())
      throw std::runtime_error(
          std::string("Input file not found in specified location: ") +
          json_filename);
  } catch (const std::runtime_error& except) {
    std::cerr << "Exception opening/reading json file";
  }

  //! Store json object as private variable
  //! Read json file and store to private variables
  json_ = json::parse(inputFile);
}

std::string IO::mesh_file_name() const {

  std::string mesh_file_name;

  //! Check if mesh file is present
  mesh_file_name =
      working_dir_ + json_["mesh_file"].template get<std::string>();
  std::ifstream meshfile;
  meshfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    meshfile.open(mesh_file_name);
  } catch (const std::ifstream::failure& except) {
    std::cerr << "Exception opening/reading mesh file";
  }
  meshfile.close();

  return mesh_file_name;
}

//! \brief Return user-specified material propertes
std::vector<json> IO::material_properties() const {

  std::vector<json> json_material_properties;

  // Store json object for material properties
  // IO handles null json object by making empty json object
  // MaterialProperties class could handle empty json object
  for (unsigned i = 0; i < json_["material_properties"].size(); i++) {
    if (!json_["material_properties"].is_null()) {
      json_material_properties.emplace_back(json_["material_properties"].at(i));
    } else {
      std::cout << "No material properties specified, using default\n";
      json_material_properties.clear();
    }
  }

  return json_material_properties;
}

//! \brief Return user-specified gauss points
unsigned IO::ngauss_points() const {

  unsigned ngauss_points{0};

  //! Read and pass the
  //! If not specified, set default value of 1
  try {
    if (json_.at("ngauss_points").size())
      ngauss_points = json_["ngauss_points"].template get<unsigned>();
  } catch (json::out_of_range& out_of_range) {
    std::cerr << out_of_range.what() << '\n';
    std::cout << "ngauss_points not specified. Using a default value of 1\n";
    ngauss_points = 1;
  }

  return ngauss_points;
}

//! \brief Return user-specified dimension
unsigned IO::dimension() const {

  unsigned dimension{0};

  //! Read and pass the
  //! If not specified, set default value of 1
  try {
    if (json_.at("dimension").size())
      dimension = json_["dimension"].template get<unsigned>();
  } catch (json::out_of_range& out_of_range) {
    std::cerr << out_of_range.what() << '\n';
    std::cout << "dimension not specified. Using a default value of 2\n";
    dimension = 2;
  }

  return dimension;
}

//! \brief Write output file names and store them in private member
//! \param[in] attribute Attribute being written (eg., material_points / stress)
//! \param[in] file_extension File Extension (*.txt)
boost::filesystem::path IO::output_file(const std::string& attribute,
                                        const std::string& file_extension) {

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
  if (!path.empty()) path = working_dir_ + path;

  //! Create results folder if not present
  boost::filesystem::path dir(path);
  if (!boost::filesystem::exists(dir)) boost::filesystem::create_directory(dir);

  //! Create full path with working directory path and file name
  boost::filesystem::path file_path(path + file_name.str().c_str());
  return file_path;
}