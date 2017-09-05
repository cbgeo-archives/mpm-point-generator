# MPM Point Generator

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/cb-geo/mpm-point-generator/develop/license.md)
[![Build Status](https://api.travis-ci.org/cb-geo/mpm-point-generator.svg?branch=develop)](https://api.travis-ci.org/cb-geo/mpm-point-generator.svg?branch=develop)
[![CLA assistant](https://cla-assistant.io/readme/badge/cb-geo/mpm-point-generator)](https://cla-assistant.io/cb-geo/mpm-point-generator)
[![CircleCI](https://circleci.com/gh/cb-geo/mpm-point-generator.svg?style=svg)](https://circleci.com/gh/cb-geo/mpm-point-generator)
[![codecov](https://codecov.io/gh/cb-geo/mpm-point-generator/branch/develop/graph/badge.svg)](https://codecov.io/gh/cb-geo/mpm-point-generator)

## Compile and Run

0. Run `mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release /path/to/CMakeLists.txt`

1. Run `make clean && make -jN` (where N is the number of cores)

3. Run `./mpm_point_generator /path/to/mesh.msh`

