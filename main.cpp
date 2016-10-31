//
//  main.cpp
//  test3
//
//  Created by Christopher Wilkes on 31/10/2016.
//  Copyright © 2016 Christopher Wilkes. All rights reserved.
//

#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int main() {
    
  // Following Values need to be cin'd at some point, values are test case.
    
    int xLength  = 5;
    int yHieght  = 5;
    double xSpacing = 1;
    double ySpacing = 1;
    
   // NI = Number of nodes in I Direction
   // NJ = Number of nodes in J Direction

    int NI = ((double)xLength/xSpacing)+1;
    int NJ = ((double)yHieght/ySpacing)+1;
    

    vector<pair<int,int>> Coord;
    
    for (int i = 0; i < NI; i++)
    {
        for (int j = 0; j < NJ; j++)
        {
            Coord.push_back(make_pair(i,j));
        }
    }
    
    for (int i = 0; i < Coord.size(); i++)
    {
        cout << Coord[i].first <<","<< Coord[i].second << endl;
    }
}

// Status: Can output coordinates to console.
