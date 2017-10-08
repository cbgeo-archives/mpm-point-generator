#ifndef MPM_MESH_MATERIAL_PROPERTIES_H_
#define MPM_MESH_MATERIAL_PROPERTIES_H_

#include <limits>
#include <memory>

//! Alias for JSON
#include "json.hpp"
using json = nlohmann::json;

//! \brief Points class to store material properties
class MaterialProperties {
 public:
  //! Constructor of material properties
  //! \param[in] json input file containing material properties
  explicit MaterialProperties(const json& materialproperties);

  //! Return density
  double density() const { return density_; }

  //! Return k0
  double k0() const { return k0_; }

 private:
  //! density
  double density_ = std::numeric_limits<unsigned>::max();

  //! k0
  double k0_ = std::numeric_limits<unsigned>::max();
};

#include <material_properties.tcc>

#endif  // MPM_MESH_MATERIAL_PROPERTIES_H_
