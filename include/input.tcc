#include "input.h"
//! \brief Open and read gmsh file
//! \details to retrive vertex id and coordinates
//! \tparam Tdim Dimension
template <unsigned Tdim>
void Input <Tdim>::read_vertices() {

    //! \brief Variables used

    //! Number of vertices and vertex coordinates
    double nvertices,xcoord,ycoord,zcoord;
    //! Vertices id
    unsigned vertid;
    //!Array to store vertices coordinates
    std::array<double, Tdim> verticesarray;

    const std::string infilename = "test";
    std::fstream infile;
    infile.open(infilename, std::ios::in);

    //! \brief Iterate through gmsh file to get information
    //! Open input file
    while (infile.is_open()) {
        std::cout << '\n' << "VERTICES FILE FOUND" << '\n' << '\n';

        std::string line;

        //!Ignore first 4 lines
        for (unsigned k = 0;  k < 4; ++k ) {
            std::getline(infile, line);
            std::istringstream istream(line);
            if (line.find('#') == std::string::npos && line != "") {
                istream >> line;
            }
        }
        //! Get number of vertices
        infile >> nvertices;
        getline(infile, line);

        //!Get vertex coordinates & id
        for (int i = 0; i < nvertices; ++i) {
            std::getline(infile, line);
            std::istringstream istream(line);
            if (line.find('#') == std::string::npos && line != "") {
                istream >> vertid;
                istream >> xcoord;
                istream >> ycoord;
                istream >> zcoord;
                verticesarray = {xcoord,ycoord,zcoord};
                vertices_.emplace_back(new Point<Tdim>(vertid, verticesarray));
            }
        } infile.close();
    }
    std::cout << "Number of Vertices: " << vertices_.size() << '\n';
}

template <unsigned Tdim>
void Input <Tdim>::read_elements() {

   //! \brief Variables used
    //! Vertices id
    double nvertices,nelements;
    double elementtype,physical,elementry;
    double vertices1,vertices2,vertices3,vertices4;
    unsigned elementid;
    //!Array to store vertices coordinates
    std::array<double, Tdim> elementarray;

    const std::string infilename = "test";
    std::fstream infile;
    infile.open(infilename, std::ios::in);

    //! \brief Iterate through gmsh file to get information
    //! Open input file
    while (infile.is_open()) {
        std::cout << '\n' << "ELEMENT FILE FOUND" << '\n' << '\n';

        std::string line;

        //!Ignore first 4 lines
        for (unsigned k = 0;  k < 4; ++k ) {
            std::getline(infile, line);
            std::istringstream istream(line);
            if (line.find('#') == std::string::npos && line != "") {
                istream >> line;
            }
        }
        //! Get number of vertices
        infile >> nvertices;
        getline(infile, line);
        //! Skip past vertices section
        for (int i = 0; i < nvertices; ++i) {
            std::getline(infile, line);
        }
        for (unsigned l = 0;  l < 2; ++l ) {
            std::getline(infile, line);
            std::istringstream istream(line);
            if (line.find('#') == std::string::npos && line != "") {
                istream >> line; }
        }

        infile >> nelements;
        getline(infile, line);

        for (int i = 0; i < nelements; ++i) {
            std::getline(infile, line);
            std::istringstream istream(line);
            if (line.find('#') == std::string::npos && line != "") {
                istream >> elementid;
                istream >> elementtype;
                istream >> elementry;
                istream >> physical;
                istream >> elementry;

                //! \brief Check element type
                //! \details If element type not = to Tdim, skip element
                if(elementtype != Tdim){
                    istream >> line;
                }

                else {
                    istream >> vertices1;
                    istream >> vertices2;
                    istream >> vertices3;
                    istream >> vertices4;
                    elementarray = {vertices1,vertices2,vertices3,vertices4};
                    elements_.emplace_back(new Point<Tdim>(elementid, elementarray));
                }
            }
        } infile.close();
    }
    std::cout << "Number of Elements: " << elements_.size() << '\n';
}

