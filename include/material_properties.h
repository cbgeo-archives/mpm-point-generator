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
  MaterialProperties(const std::string& filename);

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

#include <material_properties.tcc>

#endif  // MPM_MESH_MATERIAL_PROPERTIES_H_
