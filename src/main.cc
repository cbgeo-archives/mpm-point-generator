#include <array>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

int main() {

  // Following Values need to be cin'd at some point, values are test case.

  const double xlength = 5.;
  const double yheight = 5.;
  const double xspacing = 1.;
  const double yspacing = 1.;

  // NI = Number of nodes in I Direction
  const int ni = (static_cast<double>(xlength / xspacing)) + 1;
  // NJ = Number of nodes in J Direction
  const int nj = (static_cast<double>(yheight / yspacing)) + 1;
  // Coordinate output
  std::vector<std::array<double, 2>> coords;
  std::fstream outfile;                      // Output file stream name
  std::string outputfilename = "coord.txt";  // Output file name and type

  for (unsigned i = 0; i < ni; ++i) {
    for (unsigned j = 0; j < nj; ++j) {
      std::array<double, 2> coord = {i * xspacing, j * yspacing};
      coords.push_back(coord);
    }
  }

  outfile.open(outputfilename, std::ios::out);

  if (outfile.is_open()) {
    for (const auto& coord : coords)
      outfile << coord.at(0) << "," << coord.at(1) << '\n';
    outfile.close();
  }

  else {
    std::cout << "Could not create file:" << outputfilename << std::endl;
  }
}

// Status : Can print coordinates of points to console
