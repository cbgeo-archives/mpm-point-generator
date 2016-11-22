#include "mesh.h"
#include "point.h"

Mesh::Mesh(double xlength, double yheight, double xspacing, double yspacing)
	: xlength{ xlength },
	yheight{ yheight },
	xspacing{ xspacing },
	yspacing{ yspacing } {

	id = 0;
}
