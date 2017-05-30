#include <numeric>
#include <sstream>
#include <string>

#include "gmsh.h"
#include "point.h"

//! \brief Open and read gmsh file
//! \details read vertex id and coordinates
void GMSH::get_vertices(const std::string& filename) {

  //! Number of vertices
  double nvertices = std::numeric_limits<double>::max();
  const unsigned toplines = 4;
  const unsigned ndimension = 3;

  //! Vertices id
  unsigned vertid;

  //! Array to store vertices coordinates
  std::array<double, ndimension> verticesarray;

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
        vertices_.emplace_back(new Point<ndimension>(vertid, verticesarray));
      }
    }
    infile.close();
  } else {
    throw std::runtime_error("Vertices file not found");
  }
  std::cout << "Number of Vertices: " << vertices_.size() << '\n';

  tot_vertices_ = vertices_.size();
}

//! \brief Open and read gmsh file
//! \details read elements
void GMSH::read_elements(const std::string& filename) {

  //! Number of vertices
  double nvertices = std::numeric_limits<double>::max();
  //! Number of elements
  double nelements = std::numeric_limits<double>::max();
  //! Element type
  double elementtype = std::numeric_limits<double>::max();

  double physical = std::numeric_limits<double>::max();
  double elementry = std::numeric_limits<double>::max();
  //! Element id
  unsigned elementid = std::numeric_limits<unsigned>::max();

  const unsigned toplines = 4;
  const unsigned ndimension = 3;

  //! Array to store vertices coordinates
  std::array<double, ndimension> elementarray;

  std::fstream infile;
  infile.open(filename, std::ios::in);
  //! Open input file
  if (infile.is_open()) {
    std::cout << "Element file found" << '\n';

    std::string line;

    //! Ignore first 4 lines
    for (unsigned k = 0; k < toplines; ++k) {
      std::getline(infile, line);
    }
    //! Get number of vertices
    infile >> nvertices;
    getline(infile, line);
    //! Skip past vertices section
    for (int i = 0; i < nvertices; ++i) {
      std::getline(infile, line);
    }
    //! Skip past element headers
    for (unsigned l = 0; l < 2; ++l) {
      std::getline(infile, line);
    }

    infile >> nelements;
    getline(infile, line);

    for (int i = 0; i < nelements; ++i) {
      std::getline(infile, line);
      std::istringstream istream(line);
      if (line.find('#') == std::string::npos && line != "") {
        istream >> elementid;
        istream >> elementtype;
        istream >> elementry;
        istream >> physical;
        istream >> elementry;

        //! \brief Check element type
        //! \details If element type not == to Tdim, skip element
        if (elementtype != ndimension) {
          istream >> line;
        } else {
          istream >> elementarray.at(0) >> elementarray.at(1) >>
              elementarray.at(2) >> elementarray.at(3);
          elements_.emplace_back(
              new Point<ndimension>(elementid, elementarray));
        }
      }
    }
    infile.close();
  } else {
    throw std::runtime_error("Element file not found");
  }

  std::cout << "Number of Elements: " << elements_.size() << '\n';
}

void GMSH::output_stresses(const std::string& outputfilename) {

  std::fstream outputfile;
  outputfile.open(outputfilename, std::ios::out);

  const double density = 22;
  const double K0 = 0.5;

  if (outputfile.is_open()) {

    //! Iterate through vector and print
    outputfile << tot_vertices_ << '\n';

    for (const auto& point : vertices_) {
      outputfile.setf(std::ios::fixed, std::ios::floatfield);
      //! horizontal 2d stress
      outputfile << point->id() - 1 << '\t';
      outputfile << (K0 *
                     (0 - (10 * ((3 - point->coordinates().at(1)) * density))))
                 << '\t'
                 //! vertical 2d stress
                 << (0 - (10 * ((3 - point->coordinates().at(1)) * density)))
                 << '\t' << point->coordinates().at(2) << '\t'
                 << point->coordinates().at(2) << '\t'
                 << point->coordinates().at(2) << '\t'
                 << point->coordinates().at(2) << '\n';
    }
    outputfile.close();
  }
  std::cout
      << "The output file for initial stresses of particles has been generated."
      << "\n";
}
