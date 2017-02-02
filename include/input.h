#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#ifndef MPM_POINT_GEN_INPUT_H
#define MPM_POINT_GEN_INPUT_H

//! Class to input coordinates from text file
template<unsigned Idim, unsigned Rows> class Input {

public:
    //!  Constructor
    Input(std::array<double, Idim> outcoordtest, std::vector<std::array<double, Idim>> incoordvector);

    //! Read mesh coordinates from file
    void readfile();

    //!Output contents of vector to check right data included
    void outputcoords();

    //!Generate point coordinates
    void generatemesh();



private:

    //! Vector containing input coordinates
    std::vector<std::array<double, Idim>> incoordvector_;
    //! Array used in outputting coordinates to test incoordvector_contents
    std::array<double, Idim> outcoordtest_;

    std::array<double, Idim> linearray;

    double meshsize = linearray.size();

    double lengtharray[Rows][4];


    //test variables
    double xlengths;
    double ylengths;

    double xlentotal;
    double ylentotal;



    //! coordinates used in incoordvector
    double xlow, ylow, xhigh, yhigh;
};
#endif //MPM_POINT_GEN_INPUT_H
