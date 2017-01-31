#include <iostream>
#include <memory>

#include "mesh.cc"

int main() {

    std::string infilename = "corner.txt";
    std::fstream infile;
    infile.open(infilename, std::ios::in);

    std::vector<std::array<double, 2>> linevector_;

    std::string line;

    getline(infile, line);

    while (infile) {

        double xlow;
        infile >> xlow;

        getline(infile, line, ',');

        double ylow;
        infile >> ylow;

        //std::cout << xlow << "," << ylow << '\n';

        std::array<double, 2> linearray = {xlow, ylow};

        linevector_.emplace_back(linearray);

        }


    std::cout << "vector size:" << linevector_.size() << '\n';

    const std::string outputfilename = "coords2.txt";
    std::fstream outfile2;
    outfile2.open(outputfilename, std::ios::out);


    if (outfile2.is_open()) {
        for (const auto &coord : linevector_)
            outfile2 << coord.at(0) << "," << coord.at(1) << '\n';
        outfile2.close();

    }

    std::unique_ptr<Mesh<4>> mesh(new Mesh<4>(0, {5,5,1,1 }));

    mesh->generatecoordinates();

    mesh->coordinatesoutput();


  }
