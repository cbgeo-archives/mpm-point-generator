# MPM Point Generator
> Christopher Wilkes

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/cw646/mpm-point-generator/develop/license.md)
[![Build Status](https://travis-ci.org/cw646/mpm-point-generator.svg?branch=develop)](https://travis-ci.org/cw646/mpm-point-generator)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/11832/badge.svg)](https://scan.coverity.com/projects/cw646-mpm-point-generator)

## Compile and Run

0. Run `mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release /path/to/CMakeLists.txt`

1. Run `make clean && make -jN` (where N is the number of cores)

3. Run lem `./mpm-point-generator /path/to/mesh.msh`

