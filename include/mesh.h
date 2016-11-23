#include "point.h"
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

class Mesh {

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

  unsigned id;

  //! Create point vector
  std::vector<std::shared_ptr<Point>> points;

  // Output file stream name
  std::fstream outfile;

  // Output file name and type
  std::string outputfilename = "coord.txt";

public:
  //!  Constructor
  Mesh(double, double, double, double);

  // Following Values need to be cin'd at some point, values are test case.
  void generatecoordinates() {

    std::array<double, 2> coord;

    for (unsigned i = 0; i < ni(); ++i) {
      for (unsigned j = 0; j < nj(); ++j) {
        coord = {i * xspacing, j * yspacing};
        // need to call the points object created by Point class here - not sure
        // how
        points.emplace_back(std::make_shared<Point>(id, coord));
        ++id;
      }
    }
  }

  void coordinatesoutput() {

    outfile.open(outputfilename, std::ios::out);

    for (const auto &point : points) {
      outfile << point->id() << '\t';
      outfile << point->coordinates().at(0) << "," << point->coordinates().at(1)
              << '\n';
    }

    outfile.close();
  }
};

//    if (outfile.is_open()) {
//        for (const auto& coord : coords)
//            outfile << coord.at(0) << "," << coord.at(1) << '\n';
//        outfile.close();
//    } else {
//        std::cout << "Could not create file:" << outputfilename <<
//        std::endl;
//    }
