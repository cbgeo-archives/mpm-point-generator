//! Constructor with density and k0
//! \param[in] json input file containing material properties
MaterialProperties::MaterialProperties(const json& materialproperties) {
  if (!materialproperties.empty()) {
    density_ = materialproperties["density"].get<double>();
    k0_ = materialproperties["k0"].get<double>();
  } else {
    std::cout << "Using default material properties to make zero stresses\n";
    density_ = 0;
    k0_ = 0;
  }
}