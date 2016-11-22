
#include <array>
#include <vector>

class Mesh {

public:
  //!  Constructor
  Mesh(double, double, double, double);

  // Following Values need to be cin'd at some point, values are test case.
  void forloop() {}

private:

  const double xlength;
  const double yheight;
  const double xspacing;
  const double yspacing;

  // NI = Number of nodes in I Direction
  double ni() const { return (xlength / xspacing) + 1; };

  // NJ = Number of nodes in J Direction
  double nj() const { return (yheight / yspacing) + 1; };

  std::vector<std::array<double, 2>> coords;

 // std::array<double, 2> coord;

  unsigned id;






};
