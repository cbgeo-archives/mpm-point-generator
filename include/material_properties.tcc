//! Constructor with density and k0
//! \param[in] json input file containing material properties
MaterialProperties::MaterialProperties(const std::string& filename) {
  std::ifstream file;
  std::shared_ptr<MaterialProperties> material_properties;
  file.open(filename.c_str(), std::ios::in);

  if (!file.is_open())
    throw std::runtime_error(
        "Specified material properties file does not exist");
  if (file.good()) {
    json j;
    file >> j;
    density_ = j["material_properties"]["density"].get<double>();
    k0_ = j["material_properties"]["k0"].get<double>();
  }

  file.close();
}