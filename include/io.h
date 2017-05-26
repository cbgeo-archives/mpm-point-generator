#ifndef MPM_POINT_GEN_IO_H_
#define MPM_POINT_GEN_IO_H_

#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <sstream>

//! \brief Class to store input/output options
//! \details Includes input, output for points and stress

class IO {
 public:
  //! \brief Make constructor for input and output files
  IO(const std::string& inputfile, const std::string& output_point,
     const std::string& output_stress) {

    inputfilename_ = inputfile;
    outputfilename_point_ = output_point;
    outputfilename_stress_ = output_stress;
  }

  //! \brief Get the private properties

  //! return input file name
  const std::string inputfilename() { return inputfilename_; }

  //! return output file name for point
  const std::string outputfilename_point() { return outputfilename_point_; }

  //! return output file name for stress
  const std::string outputfilename_stress() { return outputfilename_stress_; }

 private:
  //! inputfilename_ is the filename of the input
  std::string inputfilename_;

  //! outputfilename_point_ is the filename of the output for point
  std::string outputfilename_point_;

  //! outputfilename_stress_ is the filename of the output for stress
  std::string outputfilename_stress_;
};

#endif  // MPM_POINT_GEN_IO_H_