#ifndef MPM_POINT_GEN_IO_H_
#define MPM_POINT_GEN_IO_H_

#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <sstream>

#include "json.hpp"

//! \brief Class to store input/output options
//! \details Includes input, output for points and stress

class IO {
 public:
  //! \brief Make constructor for input and output files
  IO(const std::string& pathfile_name) {

    //! Open path file
    std::ifstream pathfile(pathfile_name);
    pathfile.exceptions(std::ifstream::badbit);

    //! Read file and store to private variables
    nlohmann::json j;
    pathfile >> j;
    inputfilename_ = j["inputfile"].get<std::string>();
    outputfilename_point_ = j["outputfile_point"].get<std::string>();
    outputfilename_stress_ = j["outputfile_stress"].get<std::string>();
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