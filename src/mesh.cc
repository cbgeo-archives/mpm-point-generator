#include "mesh.h"
#include "point.cc"
//! Mesh constructor
//! \param[in]
template <unsigned Tdim>
Mesh<Tdim>::Mesh(unsigned id, std::array<double, Tdim> param) : id_{ id }{
		param_ = param;
		ni_ = (param_[0] / param_[3]) + 1;
		nj_ = (param_[1] / param_[4]) + 1;
        nz_ = (param_[2] / param_[5]) + 1;
}
template <unsigned Tdim>
void Mesh<Tdim>::generatecoordinates() {
  unsigned pointid = 0;

    //!Find origin of shape, so coordinates of points will fit in shape
    const std::string infilename = "input.txt";
    std::fstream infile;
    infile.open(infilename, std::ios::in);

        std::string line;

            //!Ignore spacing line
            infile >> spacingline;
            getline (infile, line);

            //!gets first coordinate to use as origin
            infile >> xorigin;
            getline(infile, line, ',');

            infile >> yorigin;
            getline(infile, line, ':');

            infile >> zorigin;
            getline(infile, line, ':');

        infile.close();

  // Iterate through number of nodes in x and y directions
  for (auto i = xorigin; i < ni_ + xorigin; ++i) {
    for (auto j = yorigin; j < nj_ + yorigin; ++j) {
        if (nz_ > 0){
        for (auto k = zorigin; k < nz_ + zorigin; ++k) {
            std::array<double, 3> coord = {static_cast<double>(i) * param_[3],
                                           static_cast<double>(j) * param_[4],
                                           static_cast<double>(k) * param_[5]};
            // Create a point object based on id and coordinates
            points_.emplace_back(new Point<3>(pointid, coord));
            ++pointid;
        }}
        else {
            std::array<double, 3> coord = {static_cast<double>(i) * param_[3],
                                           static_cast<double>(j) * param_[4]};
            // Create a point object based on id and coordinates
            points_.emplace_back(new Point<3>(pointid, coord));
            ++pointid;
        }}
  }

  std::cout << "# Points: " << points_.size() << '\n';
}

template <unsigned Tdim>
void Mesh<Tdim>::coordinatesoutput() {
  const std::string outputfilename = "coords.txt";
  std::fstream outfile;
  outfile.open(outputfilename, std::ios::out);
    if (nz_ > 0){
        for (const auto& point : points_) {
        outfile << point->id() << "," << '\t';
        outfile << point->coordinates().at(0) << "," << point->coordinates().at(1)
                << "," << point->coordinates().at(2) << '\n';
        }}
        else{
            for (const auto& point : points_) {
                outfile << point->id() << "," << '\t';
                outfile << point->coordinates().at(0) << "," << point->coordinates().at(1) <<'\n';
            }
        }
  outfile.close();
}
