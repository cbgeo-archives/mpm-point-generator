#include "mesh.h"
#include <numeric>
#include <sstream>
#include "point.cc"


//! \brief Constructor
template <unsigned Tdim>
Mesh<Tdim>::Mesh() {
}

//! \brief Open and read gmsh file
//! \details to retrive vertex id and coordinates
//! \tparam Tdim Dimension
template <unsigned Tdim>
void Mesh <Tdim>::readfile() {

    //! \brief Variables used
    //! Number of vertices and vertex coordinates
    double nvertices,xcoord,ycoord,zcoord;
    //! Vertices id
    unsigned vertn;
    //!Array to store vertices coordinates
    std::array<double, Tdim> verticesarray;

    const std::string infilename = "input";
    std::fstream infile;
    infile.open(infilename, std::ios::in);

    //! \brief Iterate through gmsh file to get information
    //! Open input file
    while (infile.is_open()) {
        std::cout << '\n' << "INPUT FILE FOUND" << '\n' << '\n';

        std::string line;

        //!Ignore first 4 lines
        for (unsigned k = 0;  k < 4; ++k ) {
            std::getline(infile, line);
            std::istringstream istream(line);
            if (line.find('#') == std::string::npos && line != "") {
                istream >> line; }
        }
        //! Get number of vertices
        infile >> nvertices;
        getline(infile, line);

        //!Get vertex coordinates & id
        for (int i = 0; i < nvertices; ++i) {
            std::getline(infile, line);
            std::istringstream istream(line);
            if (line.find('#') == std::string::npos && line != "") {
                istream >> vertn;
                istream >> xcoord;
                istream >> ycoord;
                istream >> zcoord;
                verticesarray = {xcoord,ycoord,zcoord};
                vertices_.emplace_back(new Point<Tdim>(vertn, verticesarray));
            }
        }
        infile.close();
    }
    std::cout << "Number of Elements: " << vertices_.size() << '\n';
}

//! \brief Print vector to text file
//! \details to Check data entry correct
template <unsigned Tdim>
void Mesh<Tdim>::outputcoords() {

    const std::string outputfilename = "inputcheck.txt";
    std::fstream inputcheck;
    inputcheck.open(outputfilename, std::ios::out);


    if (inputcheck.is_open()) {

        //! Iterate through vector and print
        for (const auto &point : vertices_) {
            inputcheck << point->id() << '\t';
            inputcheck << point->coordinates().at(0) << " " << point->coordinates().at(1) << " "
                       << point->coordinates().at(2)<< '\n';
        }
        inputcheck << "Am I the same as input.txt?";
        inputcheck.close();
    }
}

