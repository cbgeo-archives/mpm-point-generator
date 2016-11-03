// Copyright (c) [2016] [CB-Geo FE-Lib]

#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

int main() {

  // Following Values need to be cin'd at some point, values are test case.

  const double xlength = 5.;
  const double yheight = 5.;
  const double xspacing = 1;
  const double yspacing = 1;

  int NI =
      ((double)xlength / xspacing) + 1; // NI = Number of nodes in I Direction
  int NJ =
      ((double)yheight / yspacing) + 1; // NJ = Number of nodes in J Direction

  std::vector<std::pair<int, int>> Coord;   // Coordinate output
  std::fstream outfile;                     // Output file stream name
  std::string outputfilename = "Coord.txt"; // Output file name and type

  outfile.open(outputfilename, std::ios::out);

  if (outfile.is_open()) {
    for (int i = 0; i < NI; ++i) {
      for (int j = 0; j < NJ; ++j) {
        Coord.push_back(std::make_pair(i, j));
      }
    }

    for (const auto &coord : Coord)
      outfile << coord.first << "," << coord.second << '\n';
    outfile.close();
  }

  else {
    std::cout << "Could not create file:" << outputfilename << std::endl;
  }
}

// Status : Can print coordinates of points to console
