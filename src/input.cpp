#include "input.h"
#include "mesh.cc"

template <unsigned Idim>
Input<Idim>::Input(std::array<double, Idim> outcoordtest, std::vector<std::array<double, Idim>> incoordvector) {

    incoordvector = incoordvector_;
    outcoordtest = outcoordtest_;
}

template <unsigned Idim>
void Input<Idim>::readfile() {

    int i;
    i = 0;

    const std::string infilename = "input.txt";

    std::fstream infile;
    infile.open(infilename, std::ios::in);

    if(infile.is_open()) {
        std::string line;

        getline(infile, line);

        while (infile) {

            infile >> xlow;
            getline(infile, line, ',');

            infile >> ylow;
            getline(infile, line, ':');

            infile >> xhigh;
            getline(infile, line, ',');

            infile >> yhigh;
            getline(infile, line);

            if(!infile){
                break;
            }

            linearray = {xlow, ylow, xhigh, yhigh};
            incoordvector_.emplace_back(linearray);

            lengtharray[i][0] = {xlow};
            lengtharray[i][1] = {ylow};
            lengtharray[i][2] = {xhigh};
            lengtharray[i][3] = {yhigh};

            i++;

        } infile.close();
    }
    std::cout << "# Vector: " << incoordvector_.size() << '\n';
    std::cout << "# Array: " << linearray.size() << '\n';
}

template <unsigned Idim>
void Input<Idim>::outputcoords(){

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

//!Generate point coordinates
template <unsigned Idim>
void Input<Idim>::generatemesh(){

        //std::cout << a << "," << b << '\n';

    //Algorithm to go here which uses lengtharray to calculate xlength & ylength

    std::unique_ptr<Mesh<4>> mesh(new Mesh<4>(0, {5,5,1,1}));

    mesh->generatecoordinates();

    mesh->coordinatesoutput();
}


