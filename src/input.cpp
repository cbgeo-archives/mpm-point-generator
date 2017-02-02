#include "input.h"
#include "mesh.cc"
#include <boost/range/numeric.hpp>

template <unsigned Idim, unsigned Rows>
Input<Idim, Rows>::Input(std::array<double, Idim> outcoordtest, std::vector<std::array<double, Idim>> incoordvector) {

    incoordvector = incoordvector_;
    outcoordtest = outcoordtest_;
}

template <unsigned Idim, unsigned Rows>
void Input<Idim,Rows>::readfile() {

    
    int i;
    const std::string infilename = "input.txt";

    std::fstream infile;
    infile.open(infilename, std::ios::in);

    if(infile.is_open()) {
        std::cout<<"OPEN";

        std::string line;

        while (infile) {

            infile >> xlow;
            getline(infile, line, ',');

            infile >> ylow;
            getline(infile, line, ':');

            infile >> xhigh;
            getline(infile, line, ',');

            infile >> yhigh;
            getline(infile, line);

            linearray = {xlow, ylow, xhigh, yhigh};
            incoordvector_.emplace_back(linearray);

            lengtharray[i][0] = {xlow};
            lengtharray[i][1] = {ylow};
            lengtharray[i][2] = {xhigh};
            lengtharray[i][3] = {yhigh};

            ++i;

        } infile.close();

    }
    std::cout << "Rows used:  " << incoordvector_.size() << '\n';
    std::cout << "Dimensions: " << linearray.size()/2 << '\n';





}

template <unsigned Idim, unsigned Rows>
void Input<Idim, Rows>::generatemesh(){

    std::vector<double> xlength_;
    std::vector<double> ylength_;

    for (unsigned i =0; i< incoordvector_.size()-1; ++i){

        xlengths = lengtharray[i+1][2] - lengtharray[i][0];
        ylengths = lengtharray[i+1][3] - lengtharray[i][1];

        xlength_.emplace_back(xlengths);
        ylength_.emplace_back(ylengths);
    }

   xlentotal = boost::accumulate(xlength_, 0);
   ylentotal = boost::accumulate(ylength_, 0);

    std::cout<< "x Length:   " << xlentotal << '\n' <<
                "y Length:   " << ylentotal << '\n';

    //Algorithm to go here which uses lengtharray to calculate xlength & ylength

    std::unique_ptr<Mesh<4>> mesh(new Mesh<4>(0, {xlentotal,ylentotal,1,1}));

    mesh->generatecoordinates();

    mesh->coordinatesoutput();
}

template <unsigned Idim, unsigned Rows>
void Input<Idim, Rows>::outputcoords(){

    const std::string outputfilename = "coords2.txt";
    std::fstream outfile2;
    outfile2.open(outputfilename, std::ios::out);


    if (outfile2.is_open()) {
        for (const auto &outcoordstest : incoordvector_)
            outfile2 << outcoordstest.at(0) << "," << outcoordstest.at(1)
                     << ":" << outcoordstest.at(2) << "," << outcoordstest.at(3) <<'\n';
        outfile2.close();
    }
}
