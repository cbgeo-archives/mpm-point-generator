#include "mesh.h"

//! Mesh constructor
//! \param[in] xlength Lenght of mesh in x-direction
Mesh::Mesh(unsigned id, double xlength, double yheight, double xspacing,
           double yspacing)
    : id_{id}, xspacing_{xspacing}, yspacing_{yspacing} {
  ni_ = (xlength / xspacing_) + 1;
  nj_ = (yheight / yspacing_) + 1;
}

void Mesh::generatecoordinates() {
  unsigned pointid = 0;
  // Iterate through number of nodes in x and y directions
  for (unsigned i = 0; i < ni_; ++i) {
    for (unsigned j = 0; j < nj_; ++j) {
      std::array<double, 2> coord = {static_cast<double>(i) * xspacing_,
                                     static_cast<double>(j) * yspacing_};
      // Create a point object based on id and coordinates
      points_.emplace_back(new Point(pointid, coord));
      ++pointid;
    }
  }
}

void Mesh::coordinatesoutput() {
  const std::string outputfilename = "coords.txt";
  std::fstream outfile;
  outfile.open(outputfilename, std::ios::out);

  for (const auto& point : points_) {
    outfile << point->id() << '\t';
    outfile << point->coordinates().at(0) << "," << point->coordinates().at(1)
            << '\n';
  }
  outfile.close();
}
