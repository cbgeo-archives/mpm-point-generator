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

  //! Generate coordinates of points
  void generatecoordinates();

  //! Print out coordinates
  void coordinatesoutput();



private:
  //! Mesh id
  unsigned id_;
  //! Number of nodes in I Direction
  unsigned ni_;
  //! Number of nodes in J Direction
  unsigned nj_;

  double xorigin;
  double yorigin;

   //! An array containing parameters used to calculate ni/nj (xlength[0], yehight[1], xspacing[2], yspacing[3])
  std::array<double, Tdim> param_;

    //! Initialise Point template
  std::vector<std::unique_ptr<Point<2>>> points_;




};
