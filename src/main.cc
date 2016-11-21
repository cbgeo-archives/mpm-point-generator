#include <fstream>
#include <iostream>
#include <memory>

#include "mesh.h"
#include "point.h"

int main() {

  Mesh newmesh(5, 5, 1, 1);

  std::vector<std::shared_ptr<Point>> points;

  unsigned id = 0;
  for (unsigned i = 0; i < newmesh.ni(); ++i) {
    for (unsigned j = 0; j < newmesh.nj(); ++j) {
      newmesh.coord = {i * newmesh.xspacing, j * newmesh.yspacing};
      points.emplace_back(std::make_shared<Point>(id, newmesh.coord));
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
