#include "input.h"
#include "mesh.cc"
#include <numeric>

template <unsigned Idim, unsigned Rows>
Input<Idim, Rows>::Input(std::array<double, Idim> outcoordtest, std::vector<std::array<double, Idim>> incoordvector) {

    incoordvector = incoordvector_;
    outcoordtest = outcoordtest_;
}

template <unsigned Idim, unsigned Rows>
void Input<Idim,Rows>::readfile() {

    
    int i;
    int k = 0;

    const std::string infilename = "input.txt";

    std::fstream infile;
    infile.open(infilename, std::ios::in);

    if(infile.is_open()) {
        std::cout<< '\n' <<"INPUT FILE FOUND" <<'\n' <<'\n';

        std::string line;

        while (infile) {

            //!Get spacing from first line
            if (k == 0) {
                infile >> xspacing;
                getline(infile, line, ',');
                infile >> yspacing;
                getline(infile, line, ',');
                infile >> zspacing;
                getline(infile, line);

                ++k;
            }

            //!Get coordinates from other lines
            infile >> xlow;
            getline(infile, line, ',');

            infile >> ylow;
            getline(infile, line, ',');

            infile >> zlow;
            getline (infile, line, ':');

            infile >> xhigh;
            getline(infile, line, ',');

            infile >> yhigh;
            getline(infile, line, ',');

            infile >> zhigh;
            getline (infile, line);

            linearray = {xlow, ylow, zlow, xhigh, yhigh, zhigh};
            incoordvector_.emplace_back(linearray);

            lengtharray[i][0] = {xlow};
            lengtharray[i][1] = {ylow};
            lengtharray[i][2] = {zlow};
            lengtharray[i][3] = {xhigh};
            lengtharray[i][4] = {yhigh};
            lengtharray[i][5] = {zhigh};

            ++i;

        } infile.close();

    }
    std::cout << "Input Rows used: " << incoordvector_.size() << '\n';
    std::cout << "Dimensions:      " << linearray.size()/2 << '\n';
    }

template <unsigned Idim, unsigned Rows>
void Input<Idim, Rows>::outputcoords(){

    const std::string outputfilename = "inputcheck.txt";
    std::fstream inputcheck;
    inputcheck.open(outputfilename, std::ios::out);


    if (inputcheck.is_open()) {

        inputcheck << xspacing << "," << yspacing << "," << zspacing << '\n';

        for (const auto outcoordstest : incoordvector_)
            inputcheck << outcoordstest.at(0) << "," << outcoordstest.at(1)
                     << "," << outcoordstest.at(2) << ":" << outcoordstest.at(3)
                     << "," << outcoordstest.at(4) << "," << outcoordstest.at(5) <<'\n';
    }
    inputcheck << "Am I the same as input.txt?";
    inputcheck.close();
}

template <unsigned Idim, unsigned Rows>
void Input<Idim, Rows>::generatemesh(){

    std::vector<double> xlength_;
    std::vector<double> ylength_;
    std::vector<double> zlength_;


    //!Sums the total lengths between points
    for (unsigned i =0; i< incoordvector_.size()-1; ++i){

        xlengths = lengtharray[i+1][3] - lengtharray[i][0];
        ylengths = lengtharray[i][4] - lengtharray[i][1];
        zlengths = lengtharray[i+1][5] - lengtharray[i][2];

        xlength_.emplace_back(xlengths);
        ylength_.emplace_back(ylengths);
        zlength_.emplace_back(zlengths);
    }

   xlentotal = std::accumulate(xlength_.begin(), xlength_.end(),0);
   ylentotal = std::accumulate(ylength_.begin(), ylength_.end(),0)/(incoordvector_.size() -1);
   zlentotal = std::accumulate(zlength_.begin(), zlength_.end(),0);

    std::cout<< "x Length:        " << xlentotal << '\n' <<
                "y Length:        " << ylentotal << '\n' <<
                "z Length:        " << zlentotal << '\n';

    std::unique_ptr<Mesh<6>> mesh(new Mesh<6>(0, {xlentotal,ylentotal,zlentotal,xspacing,yspacing,zspacing}));

    mesh->generatecoordinates();

    mesh->coordinatesoutput();
}

