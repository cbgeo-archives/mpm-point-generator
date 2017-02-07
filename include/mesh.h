#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include "point.h"

//! \brief Mesh class
template<unsigned Tdim> class Mesh {
public:
    //!  Constructor
    Mesh(unsigned, std::array<double, Tdim> param);

    //! Generate coordinates of points
    void generatecoordinates();

    //! Print out coordinates
    void coordinatesoutput();



private:
    //! Mesh id
    unsigned id_;
    //! Number of nodes in I Direction
    unsigned ni_;
    //! Number of nodes in J Direction
    unsigned nj_;

    unsigned nz_;

    double xorigin;
    double yorigin;
    double zorigin;

    double xhigh, yhigh, zhigh;

    double origin2darray[50][6];
    std::array<double, 3> originarray;
    std::vector<std::array<double, 3>> originvector_;

    std::string spacingline;

    //! An array containing parameters used to calculate ni/nj (xlength[0], yehight[1], xspacing[2], yspacing[3])
    std::array<double, Tdim> param_;

    //! Initialise Point template
    std::vector<std::unique_ptr<Point<3>>> points_;




};
