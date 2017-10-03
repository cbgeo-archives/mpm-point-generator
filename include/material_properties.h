#ifndef MPM_MESH_MATERIAL_PROPERTIES_H_
#define MPM_MESH_MATERIAL_PROPERTIES_H_

#include <memory>

//! \brief Points class to store material properties
class MaterialProperties {
 public:
  //! Constructor with density and k0
  //! \param[in] density of the material
  //! \param[in] k0 of the material
  MaterialProperties(const double density, const double k0) {
    density_ = density;
    k0_ = k0;
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
