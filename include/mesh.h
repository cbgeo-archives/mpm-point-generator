#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include "point.h"

//! Class to input coordinates from text file
template<unsigned Tdim> class Mesh {

public:
    //!  Constructor
    Mesh();

    //! Read file
    void readfile();

    //!Output contents of vector to check right data included
    void outputcoords();

private:

    //!coordinate and id container
    std::vector<std::unique_ptr<Point<Tdim>>> vertices_;
};
