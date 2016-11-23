#include <iostream>
#include <memory>

#include "mesh.h"
#include "point.h"

int main() {

  Mesh newmesh(5, 5, 1, 1);

  newmesh.generatecoordinates();
  newmesh.coordinatesoutput();
}
