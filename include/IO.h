#ifndef MPM_POINT_GEN_IO_H
#define MPM_POINT_GEN_IO_H

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <numeric>
#include <sstream>
#include <vector>

//! \brief    Class to store input/output options
//! \details  Includes input, output for points and stress

class IO {
	public:
	  //! \brief	Make constructor for input and output files
  	IO(const std::string& inputfile, 
  	 	 const std::string& output_point, 
  	 	 const std::string& output_stress) {
  	
  			inputfilename_ = inputfile;
  			outputfilename_point_ = output_point;
  			outputfilename_stress_ = output_stress;
    }

  	//! \brief 	Get the private properties

  	//! Returninputfilename_
  	const std::string inputfilename() { return inputfilename_; }

  	//! Return outputfilename_point_
  	const std::string outputfilename_point() { return outputfilename_point_; }

  	//! Return outputfilename_stress_
  	const std::string outputfilename_stress() { return outputfilename_stress_; }


 	private:
 		//! inputfilename_ is the directory and filename of the input
 		std::string inputfilename_;

 		//! outputfilename_point_ is the directory and filename of the output for point
 		std::string outputfilename_point_;

 		//! outputfilename_stress_ is the directory and filename of the output for stress
 		std::string outputfilename_stress_;
};



#endif  // MPM_POINT_GEN_IO_H