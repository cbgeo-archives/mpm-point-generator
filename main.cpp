//Copyright (c) [2016] [CB-Geo FE-Lib]

#include <iostream>
#include <vector>
#include <utility>

int main() {
    
  // Following Values need to be cin'd at some point, values are test case.
    
    const double xlength=5.;
    const double yheight=5.;
    const double xspacing = 1;
    const double yspacing = 1;
    
   // NI = Number of nodes in I Direction
   // NJ = Number of nodes in J Direction

    int NI = ((double)xlength/xspacing)+1;
    int NJ = ((double)yheight/yspacing)+1;
    

    std::vector<std::pair<int,int>> Coord; //Coordinate output
    
    for (int i = 0; i < NI; ++i)
    {
        for (int j = 0; j < NJ; ++j)
        {
            Coord.push_back(std::make_pair(i,j));
        }
    }
    
    for (const auto &coord : Coord) std::cout << coord.first <<","<< coord.second << '\n';
    
}

// Status : Can print coordinates of points to console

