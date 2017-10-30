project(mpm-point-gen LANGUAGES CXX)

# Require C++11-compliant compiler; only available for CMake v. 3.1 and up
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

cmake_minimum_required(VERSION 3.1)

SET(CMAKE_COLOR_MAKEFILE ON)
SET(CMAKE_VERBOSE_MAKEFILE OFF)

# General compile settings
IF (NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "RelWithDebInfo")
ENDIF (NOT CMAKE_BUILD_TYPE)

# GNU Specific settings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-parameter -Wno-missing-braces -Wno-misleading-indentation -Wno-deprecated-declarations")
endif()

# OpenMP
find_package(OpenMP)
if (OPENMP_FOUND)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#  add_compile_options(${OpenMP_CXX_FLAGS})
endif()

# CMake Modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Eigen
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# Boost FileSystem
find_package(Boost REQUIRED COMPONENTS system filesystem)
include_directories(${BOOST_INCLUDE_DIRS})
link_libraries(${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

# Include directories
include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/external
)

# mpm_point_generator executable
SET(mpm_point_gen_src
  src/main.cc)
add_executable(mpm_point_generator ${mpm_point_gen_src})

# Unit test
SET(unit_test_src
  ${PROJECT_SOURCE_DIR}/tests/unit_test.cc
  ${PROJECT_SOURCE_DIR}/tests/point_test.cc
  ${PROJECT_SOURCE_DIR}/tests/material_properties_test.cc
        ${PROJECT_SOURCE_DIR}/tests/volume_test.cc
)
add_executable(mpm_point_generator_unit_test ${unit_test_src})

# Regression test
SET(regression_test_src
  ${PROJECT_SOURCE_DIR}/tests/regression_test.cc
  ${PROJECT_SOURCE_DIR}/tests/gmsh_test.cc
)
add_executable(mpm_point_generator_regression_test ${regression_test_src})

option(EIGEN3_HEADER_PATH "path to eigen3 header files,  command line option" "")


add_test(NAME mpm_point_generator_unit_test COMMAND $<TARGET_FILE:mpm_point_generator_unit_test>)
include(CTest)

add_test(NAME mpm_point_generator_regression_test COMMAND $<TARGET_FILE:mpm_point_generator_regression_test>)
include(CTest)

find_program( MEMORYCHECK_COMMAND valgrind )
set( MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --error-exitcode=1" )

# Coverage
find_package(codecov)
add_coverage(mpm_point_generator)
add_coverage(mpm_point_generator_unit_test)
add_coverage(mpm_point_generator_regression_test)

install(TARGETS mpm_point_generator mpm_point_generator_unit_test mpm_point_generator_regression_test RUNTIME DESTINATION bin)
