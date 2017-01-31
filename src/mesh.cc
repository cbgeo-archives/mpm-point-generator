#include "mesh.h"
#include "point.cc"

//! Mesh constructor
//! \param[in]
template <unsigned Tdim>
Mesh<Tdim>::Mesh(unsigned id, std::array<double, Tdim> param) : id_{ id }{
		param_ = param;
		ni_ = (param_[0] / param_[2]) + 1;
		nj_ = (param_[1] / param_[3]) + 1;
}
template <unsigned Tdim>
void Mesh<Tdim>::generatecoordinates() {
  unsigned pointid = 0;
  // Iterate through number of nodes in x and y directions
  for (unsigned i = 0; i < ni_; ++i) {
    for (unsigned j = 0; j < nj_; ++j) {
      std::array<double, 2> coord = {static_cast<double>(i) * param_[2],
                                     static_cast<double>(j) * param_[3]};
      // Create a point object based on id and coordinates
      points_.emplace_back(new Point<2>(pointid, coord));
      ++pointid;
    }
  }

  std::cout << "# Points: " << points_.size() << '\n';
}

template <unsigned Tdim>
void Mesh<Tdim>::coordinatesoutput() {
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
