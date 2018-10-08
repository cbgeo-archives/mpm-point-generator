# MPM Point Generator

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/cb-geo/mpm-point-generator/develop/license.md)
[![Build Status](https://api.travis-ci.org/cb-geo/mpm-point-generator.svg?branch=develop)](https://api.travis-ci.org/cb-geo/mpm-point-generator.svg?branch=develop)
[![CLA assistant](https://cla-assistant.io/readme/badge/cb-geo/mpm-point-generator)](https://cla-assistant.io/cb-geo/mpm-point-generator)
[![CircleCI](https://circleci.com/gh/cb-geo/mpm-point-generator.svg?style=svg)](https://circleci.com/gh/cb-geo/mpm-point-generator)
[![codecov](https://codecov.io/gh/cb-geo/mpm-point-generator/branch/develop/graph/badge.svg)](https://codecov.io/gh/cb-geo/mpm-point-generator)
[![Coverity Scan](https://scan.coverity.com/projects/12790/badge.svg?flat=1)](https://scan.coverity.com/projects/cb-geo-mpm-point-generator)
[![DOI](https://zenodo.org/badge/doi/10.5281/zenodo.1450330.svg)](https://zenodo.org/badge/doi/10.5281/zenodo.1450330.svg)

## Compile and Run

0. Run `mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release /path/to/CMakeLists.txt`

1. Run `make clean && make -jN` (where N is the number of cores)

3. Run mpm `./mpm_point_generator -f /path/ -i json_file_name`

4. To test, run the two folloing
  * Unit tests: `./mpm_point_generator_unit_test`
  * Regression tests: `./mpm_point_generator_regression_test /path/to/meshfile.msh`

## Usage 
```
   ./mpm_point_generator  [-i <input_file>] -f <Working_folder> [--]
                          [--version] [-h]
```
where: 
```
   -i <input_file>,  --input_file <input_file>
     Input JSON file [cube.json]

   -f <Working_folder>,  --working_dir <Working_folder>
     (required)  Current working folder

   --,  --ignore_rest
     Ignores the rest of the labeled arguments following this flag.

   --version
     Displays version information and exits.

   -h,  --help
     Displays usage information and exits.
```

## Referencing the code

To reference the code, please use the DOI: [![DOI](https://zenodo.org/badge/doi/10.5281/zenodo.1450330.svg)](https://zenodo.org/badge/doi/10.5281/zenodo.1450330.svg)

Wilkes, C., Tjung, E., Kumar., K (2018) CB-Geo MPM point generator, version 1.0-alpha, https://github.com/cb-geo/mpm-point-generator, doi://10.5281/zenodo.1450330.
