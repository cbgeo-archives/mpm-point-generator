#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "point.h"

//! \brief Mesh class
class Mesh {
public:
  //!  Constructor
  Mesh(unsigned, double, double, double, double);

  //! Following Values need to be cin'd at some point, values are test case.
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
  //! Spacing in x direction
  double xspacing_;
  //! Spacing in y direction
  double yspacing_;
  //! Vector of points
  std::vector<std::shared_ptr<Point>> points_;
};
