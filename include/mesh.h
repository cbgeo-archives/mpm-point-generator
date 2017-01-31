#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "point.h"

//! \brief Mesh class
template<unsigned Tdim> class Mesh {
public:
  //!  Constructor
  Mesh(unsigned, std::array<double, Tdim> param);

  //! Following Values need to be cin'd at some point, values are test case.
  void generatecoordinates();

  //! Print out coordinates
  void coordinatesoutput();

private:
  //! Mesh id
  unsigned id_;
  //! Number of nodes in I Direction (possible memory loss when converting warning)
  unsigned ni_;
  //! Number of nodes in J Direction (possible memory loss when converting warning)
  unsigned nj_;

   //! An array containing parameters used to calculate ni/nj (xlength[0], yehight[1], xspacing[2], yspacing[3])
  std::array<double, Tdim> param_;

  std::vector<std::unique_ptr<Point<2>>> points_;




};
