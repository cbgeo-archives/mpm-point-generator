#include "mesh.h"
#include <numeric>
#include <sstream>
#include "point.cc"


template <unsigned Tdim>
Mesh<Tdim>::Mesh() {
}

template <unsigned Tdim>
void Mesh <Tdim>::readfile() {

    //! total number of vectors and vertex coordinates
    double nvertices,xcoord,ycoord,zcoord;
    //! Vertices id
    unsigned vertn;
    //!Array to store vertices coordinates
    std::array<double, Tdim> verticesarray;

    const std::string infilename = "input";
    std::fstream infile;
    infile.open(infilename, std::ios::in);

    while (infile.is_open()) {
        std::cout << '\n' << "INPUT FILE FOUND" << '\n' << '\n';

        std::string line;

        //!ignore first 4 lines
        for (unsigned k = 0;  k < 4; ++k ) {
            std::getline(infile, line);
            std::istringstream istream(line);
            if (line.find('#') == std::string::npos && line != "") {
                istream >> line; }
        }
        //!get number of vertices
        infile >> nvertices;
        getline(infile, line);

        //!Get vertex coordinates
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

template <unsigned Tdim>
void Mesh<Tdim>::outputcoords() {

    const std::string outputfilename = "inputcheck.txt";
    std::fstream inputcheck;
    inputcheck.open(outputfilename, std::ios::out);


    if (inputcheck.is_open()) {

        for (const auto &point : vertices_) {
            inputcheck << point->id() << '\t';
            inputcheck << point->coordinates().at(0) << " " << point->coordinates().at(1) << " "
                       << point->coordinates().at(2)<< '\n';
        }
        inputcheck << "Am I the same as input.txt?";
        inputcheck.close();
    }
}

