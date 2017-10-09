//! Constructor with density and k0
//! \param[in] json input file containing material properties
MaterialProperties::MaterialProperties(const json& materialproperties) {
  density_ = materialproperties["density"].get<double>();
  k0_ = materialproperties["k0"].get<double>();
}