#include "mesh.h"
#include <numeric>
#include <algorithm>
#include "point.cc"


template <unsigned Tdim>
Mesh<Tdim>::Mesh() {
}

template <unsigned Tdim>
void Mesh <Tdim>::readfile() {
    int k = 0;

    const std::string infilename = "input";
    std::fstream infile;
    infile.open(infilename, std::ios::in);

    while (infile.is_open()) {
        std::cout << '\n' << "INPUT FILE FOUND" << '\n' << '\n';

        std::string line;

        //!Get data from first 5 lines
        while (k == 0) {

            infile >> line1;
            getline(infile, line);

            infile >> line2;
            getline(infile, line);

            infile >> line3;
            getline(infile, line);

            infile >> line4;
            getline(infile, line);

            infile >> nvertices;
            getline(infile, line);

            ++k;
        }

        //!Get vertex coordinates
        for (int i = 0; i < nvertices; ++i) {

            infile >> vertn;
            getline(infile, line, ' ');

            infile >> xcoord;
            getline(infile, line, ' ');

            infile >> ycoord;
            getline(infile, line, ' ');

            infile >> zcoord;
            getline(infile, line);

            vertices_.emplace_back(new Point<3>(vertn, {xcoord, ycoord, zcoord}));
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

