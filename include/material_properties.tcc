//! Constructor with density and k0
//! \param[in] json input file containing material properties
MaterialProperties::MaterialProperties(const json& jsonfile) {
  density_ = jsonfile["material_properties"]["density"].get<double>();
  k0_ = jsonfile["material_properties"]["k0"].get<double>();
}