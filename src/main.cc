#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "point.h"

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

  std::vector<std::shared_ptr<Point>> points;

  // Compute coordinates
  std::vector<std::array<double, 2>> coords;
  unsigned id = 0;
  for (unsigned i = 0; i < ni; ++i) {
    for (unsigned j = 0; j < nj; ++j) {
      std::array<double, 2> coord = {i * xspacing, j * yspacing};
      points.emplace_back(std::make_shared<Point>(id, coord));
      ++id;
    }
  }

  std::cout << "# Points: " << points.size() << '\n';

  // Output file stream name
  std::fstream outfile;

  // Output file name and type
  std::string outputfilename = "coord.txt";
  outfile.open(outputfilename, std::ios::out);

  for (const auto& point : points) {
    outfile << point->id() << '\t';
    outfile << point->coordinates().at(0) << "," << point->coordinates().at(1)
            << '\n';
  }

  outfile.close();

  //    if (outfile.is_open()) {
  //        for (const auto& coord : coords)
  //            outfile << coord.at(0) << "," << coord.at(1) << '\n';
  //        outfile.close();
  //    } else {
  //        std::cout << "Could not create file:" << outputfilename <<
  //        std::endl;
  //    }
}
