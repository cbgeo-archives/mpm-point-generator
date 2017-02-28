#ifndef MPM_POINT_GEN_INPUT_H
#define MPM_POINT_GEN_INPUT_H
#include "point.h"
#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <numeric>
#include <sstream>


//! Class to input coordinates from text file
template<unsigned Tdim> class Input {

public:

    //!Read vertices from gmsh input file
    void read_vertices();

    //! \brief Return function for vector
    //! \details vector stores vertices read in from gmsh file
    std::vector<std::shared_ptr<Point<Tdim>>> return_vertices() { return (vertices_);}

    void read_elements();

    //! \brief Return function for elements
    //! \details vector stores elements read in from gmsh file
    std::vector<std::shared_ptr<Point<Tdim>>> return_elements() { return (elements_);}

private:

    //! \brief  Vector coordinate and id container
    std::vector<std::shared_ptr<Point<Tdim>>> vertices_;

    //! \brief  Element Coordinate and id container
    std::vector<std::shared_ptr<Point<Tdim>>> elements_;

};


#endif //MPM_POINT_GEN_INPUT_H
