#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include "point.h"

//! \brief Template class to read gmsh file
//! \details Stores id and coordinates in vector
//! \tparam Tdim Dimension
template<unsigned Tdim> class Mesh {

public:
    //! \brief Constructor
    Mesh();

    //! Read from file
    void readfile();

    //! Text output of coordinates
    void outputcoords();

private:

    //! \brief  Coordinate and id container
    std::vector<std::unique_ptr<Point<Tdim>>> vertices_;
};
