#include <numeric>
#include <sstream>
#include <string>

#include "input.tcc"
#include "mesh.h"
#include "point.tcc"

//! \brief Open and read gmsh file
//! \details read vertex id and coordinates
template <unsigned Tdim>
void Mesh<Tdim>::get_vertices(const std::string& filename) {

  //! Tdim is constant 3, because max dimensions 3

  std::unique_ptr<Input<3>> inputvertices(new Input<3>());
  vertex_ = inputvertices->read_vertices(filename);
}

//! \brief Open and read gmsh file
//! \details read element id and vertices
//! \tparam Tdim = element type
template <unsigned Tdim>
void Mesh<Tdim>::get_elements(const std::string& filename) {

  std::unique_ptr<Input<Tdim>> inputelements(new Input<Tdim>());
  element_ = inputelements->read_elements(filename);
}


//! \brief Print Vertices Vector to text file
//! \details to Check data entry correct
template <unsigned Tdim>
void Mesh<Tdim>::output_vertices() {

  const std::string outputfilename = "vertexcheck.txt";
  std::fstream inputcheck;
  inputcheck.open(outputfilename, std::ios::out);

  if (inputcheck.is_open()) {

    //! Iterate through vector and print
    inputcheck << vertex_.size() << '\n';

      for (const auto& point : vertex_) {
                  inputcheck << point->coordinates().at(0) << '\t'
                             << point->coordinates().at(1) << '\t'
                             << point->coordinates().at(2) << '\n';
      }
    inputcheck.close();
  }
}


//! \brief Print Element Vector to text file
//! \details to Check data entry correct
template <unsigned Tdim>
void Mesh<Tdim>::output_elements() {

  const std::string outputfilename = "elementcheck.txt";
  std::fstream elementcheck;
  elementcheck.open(outputfilename, std::ios::out);

  if (elementcheck.is_open()) {

    //! Iterate through vector and print
    for (const auto& point : element_) {
      elementcheck << point->id() << '\t';
      elementcheck << point->coordinates().at(0) << " "
                   << point->coordinates().at(1) << " "
                   << point->coordinates().at(2) << " "
                   << point->coordinates().at(3) << '\n';
    }
    elementcheck << "Am I the same as input.txt?";
    elementcheck.close();
  }
}

template <unsigned Tdim>
void Mesh<Tdim>::output_stresses() {

    const std::string outputfilename = "stresscheck.txt";
    std::fstream stresscheck;
    stresscheck.open(outputfilename, std::ios::out);

    if (stresscheck.is_open()) {

        //! Iterate through vector and print

        for (const auto& point : vertex_) {
            stresscheck.setf( std::ios::fixed, std::ios::floatfield );
            //! horizontal 2d stress
            stresscheck << point->id()-1 << '\t';
            stresscheck << (0.5*(0 - (10*((3 - point->coordinates().at(1))*22))))<< '\t'
                        //! vertical 2d stress
                        << (0 - (10*((3 - point->coordinates().at(1))*22))) << '\t'
                        << point->coordinates().at(2) << '\t'
                        << point->coordinates().at(2) << '\t'
                        << point->coordinates().at(2) << '\t'
                        << point->coordinates().at(2) << '\n';
        }
        stresscheck.close();
    }

}

template <unsigned Tdim>
void Mesh<Tdim>::output_3d_stresses() {

    const std::string outputfilename = "stresscheck.txt";
    std::fstream stresscheck;
    stresscheck.open(outputfilename, std::ios::out);

    if (stresscheck.is_open()) {

        //! Iterate through vector and print

        for (const auto& point : vertex_) {
            stresscheck.setf( std::ios::fixed, std::ios::floatfield );
            //! horizontal 3d stress
            stresscheck << point->id()-1 << '\t';
            stresscheck << "0" << '\t'
                        << "0" << '\t'
                        //! vertical 3d stress
                        << "0" << '\t'
                        << "0" << '\t'
                        << "0" << '\t'
                        << "0" << '\n';
        }
        stresscheck.close();
    }

}
