#include "mesh.h"
#include "point.h"

Mesh::Mesh(double xlength, double yheight, double xspacing, double yspacing)
    : xlength{xlength},
      yheight{yheight},
      xspacing{xspacing},
      yspacing{yspacing} {

	id = 0;

	for (unsigned i = 0; i < ni(); ++i) {
		for (unsigned j = 0; j < nj(); ++j) {
			coord = { i * xspacing, j * yspacing };
			Points.emplace_back(std::make_shared<Point>(id, coord));
			++id;

		}
	}
}
