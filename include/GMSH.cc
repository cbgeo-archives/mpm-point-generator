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

void GMSH::output_stresses() {

  const std::string outputfilename = "stresscheck.txt";
  std::fstream stresscheck;
  stresscheck.open(outputfilename, std::ios::out);

  if (stresscheck.is_open()) {

    //! Iterate through vector and print

    for (const auto& point : vertices_) {
      stresscheck.setf(std::ios::fixed, std::ios::floatfield);
      //! horizontal 2d stress
      stresscheck << point->id() - 1 << '\t';
      stresscheck << (0.5 *
                      (0 - (10 * ((3 - point->coordinates().at(1)) * 22))))
                  << '\t'
                  //! vertical 2d stress
                  << (0 - (10 * ((3 - point->coordinates().at(1)) * 22)))
                  << '\t' << point->coordinates().at(2) << '\t'
                  << point->coordinates().at(2) << '\t'
                  << point->coordinates().at(2) << '\t'
                  << point->coordinates().at(2) << '\n';
    }
    stresscheck.close();
  }
}

void GMSH::output_3d_stresses() {

  const std::string outputfilename = "stresscheck.txt";
  std::fstream stresscheck;
  stresscheck.open(outputfilename, std::ios::out);

  if (stresscheck.is_open()) {

    //! Iterate through vector and print

    for (const auto& point : vertices_) {
      stresscheck.setf(std::ios::fixed, std::ios::floatfield);
      //! horizontal 3d stress
      stresscheck << point->id() - 1 << '\t';
      stresscheck << "0" << '\t' << "0" << '\t'
                  //! vertical 3d stress
                  << "0" << '\t' << "0" << '\t' << "0" << '\t' << "0" << '\n';
    }
    stresscheck.close();
  }
}
