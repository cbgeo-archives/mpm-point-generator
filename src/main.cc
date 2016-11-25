#include <iostream>
#include <memory>

#include "mesh.h"
#include "point.h"

int main() {

  std::unique_ptr<Mesh> mesh(new Mesh(0, 5, 5, 1, 1));

  mesh->generatecoordinates();

  mesh->coordinatesoutput();
}
