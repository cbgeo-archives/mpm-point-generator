#include <numeric>
#include <sstream>
#include <string>

#include "GMSH.h"
#include "point.tcc"

//! \brief Open and read gmsh file
//! \details read vertex id and coordinates
void GMSH::get_vertices(const std::string& filename) {

  //! Number of vertices
  double nvertices, toplines;
  //! Vertices id
  unsigned vertid;
  toplines = 4;
  //! Array to store vertices coordinates
  std::array<double, 3> verticesarray;

  std::fstream infile;
  infile.open(filename, std::ios::in);

  //! Open input file
  if (infile.is_open()) {
    std::cout << "vertices file found" << '\n';

    std::string line;

    //! Ignore first 4 lines
    for (unsigned i = 0; i < toplines; ++i) {
      std::getline(infile, line);
    }
    //! Get number of vertices
    infile >> nvertices;
    getline(infile, line);

    //! Get vertex coordinates & id
    for (int i = 0; i < nvertices; ++i) {
      std::getline(infile, line);
      std::istringstream istream(line);
      if (line.find('#') == std::string::npos && line != "") {
        istream >> vertid;
        istream >> verticesarray.at(0) >> verticesarray.at(1) >>
            verticesarray.at(2);
        vertices_.emplace_back(new Point<3>(vertid, verticesarray));
      }
    }
    infile.close();
  } else {
    throw std::runtime_error("Vertices file not found");
  }
  std::cout << "Number of Vertices: " << vertices_.size() << '\n';
}

//! \brief Print Vertices Vector to text file
//! \details to Check data entry correct
void GMSH::output_vertices() {

  const std::string outputfilename = "vertexcheck.txt";
  std::fstream inputcheck;
  inputcheck.open(outputfilename, std::ios::out);

  if (inputcheck.is_open()) {

    //! Iterate through vector and print
    inputcheck << vertices_.size() << '\n';

    for (const auto& point : vertices_) {
      inputcheck << point->coordinates().at(0) << '\t'
                 << point->coordinates().at(1) << '\t'
                 << point->coordinates().at(2) << '\n';
    }
    inputcheck.close();
  }
}

//! \brief    Generate initial stress of each point and store
//! \details  Get ver_stress, hor_stress, and shear (not used), write output
void GMSH::output_stresses() {

  //! Declare temp value of horizontal and vertical stresses;
  double ver_stress;
  double hor_stress;

  //! ycoord contains a vector of the y-coordinates (vertical) of each point
  std::vector<double> ycoord;

  for (auto const& point : vertices_) {
    ycoord.push_back(point->coordinates().at(1));
  }

  //! Get the maximum height for each point
  double max_height = *std::max_element(ycoord.begin(), ycoord.end());

  //! Make two soil parameters for stress calculation
  double density = 22;
  double K0 = 0.5;

  //! Loop through the points to get vertical and horizontal stresses
  //! Note that tau (shear stress) is assumed 0
  unsigned l = 0;
  for (double coord : ycoord) {
    ver_stress = (-(max_height - coord) * density);
    hor_stress = (-(max_height - coord) * density * K0);
    std::array<double, 6> stress{hor_stress, ver_stress, hor_stress, 0, 0, 0};
    stresses_.emplace_back(
        std::unique_ptr<InitStress>(new InitStress(l, stress)));
    ++l;
  }

  const std::string outputfilename = "stresscheck.txt";
  std::fstream stresscheck;
  stresscheck.open(outputfilename, std::ios::out);

  if (stresscheck.is_open()) {

    //! Write the total number of points generated
    stresscheck << vertices_.size() << '\n';

    //! Write the stress on the points generated
    for (auto const& point : stresses_) {
      stresscheck << point->id() << "\t";
      for (double stress : point->stress()) {
        stresscheck << stress << "\t";
      }
      stresscheck << "\n";
    }

    stresscheck.close();
  }
}