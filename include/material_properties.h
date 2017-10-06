#ifndef MPM_MESH_MATERIAL_PROPERTIES_H_
#define MPM_MESH_MATERIAL_PROPERTIES_H_

#include <memory>

#include "json.hpp"

//! Short alias for convenience
using json = nlohmann::json;

//! \brief Points class to store material properties
class MaterialProperties {
 public:
  //! Constructor with density and k0
  //! \param[in] json input file containing material properties
  MaterialProperties(const std::string& filename) {
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

  //! Return density
  double density() const { return density_; }

  //! Return k0
  double k0() const { return k0_; }

 private:
  //! density
  double density_;

  //! k0
  double k0_;
};

#endif  // MPM_MESH_MATERIAL_PROPERTIES_H_
