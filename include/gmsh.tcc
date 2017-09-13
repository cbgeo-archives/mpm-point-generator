//! Read mesh
//! \tparam Tdim Dimension
//! \tparam Tvertices Number of vertices in element
//! \param[in] filename Input mesh filename
template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::read_mesh(const std::string& filename) {
  this->read_vertices(filename);
  this->read_elements(filename);
}

//! Read vertex id and coordinates in GMSH
//! \tparam Tdim Dimension
//! \tparam Tvertices Number of vertices in element
//! \param[in] filename Input mesh filename
template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::read_vertices(const std::string& filename) {

  //! Number of vertices
  double nvertices = std::numeric_limits<double>::max();
  const unsigned toplines = 4;

  //! Vertices id
  unsigned vertid = 0;

  std::fstream infile;
  infile.open(filename, std::ios::in);

  //! Check if input file is good
  if (infile.good()) {
    std::cout << "Vertices file found" << '\n';

    std::string line;

    //! Ignore first 4 lines
    for (unsigned i = 0; i < toplines; ++i) {
      std::getline(infile, line);
    }
    //! Read number of vertices
    infile >> nvertices;
    getline(infile, line);

    //! Read vertex coordinates & id
    for (unsigned i = 0; i < nvertices; ++i) {
      std::getline(infile, line);
      std::istringstream istream(line);

      if (line.find('#') == std::string::npos && line != "") {
        //! Coordinates of vertex
        std::array<double, Tdim> vertex;

        istream >> vertid;
        istream >> vertex.at(0) >> vertex.at(1) >> vertex.at(2);
        vertices_.insert(std::make_pair(vertid, vertex));
      }
    }
    infile.close();
  }
  std::cout << "Number of Vertices: " << vertices_.size() << '\n';
}

//! Read GMSH elements
//! \tparam Tdim Dimension
//! \tparam Tvertices Number of vertices in element
//! \param[in] filename Input mesh filename
template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::read_elements(const std::string& filename) {

  //! Number of vertices
  double nvertices = std::numeric_limits<double>::max();
  //! Number of elements
  double nelements = std::numeric_limits<double>::max();
  //! Element type
  double elementtype = std::numeric_limits<double>::max();

  double physical = std::numeric_limits<double>::max();
  double elementry = std::numeric_limits<double>::max();
  //! Element id
  unsigned elementid = std::numeric_limits<unsigned>::max();

  const unsigned toplines = 4;
  // specify element type 5 =  8-node hexahedron
  // For more informtion on element types, visit:
  // http://gmsh.info/doc/texinfo/gmsh.html#File-formats
  const unsigned element_type = 5;

  //! Array to store vertices coordinates
  std::array<double, Tvertices> elementarray;

  std::fstream infile;
  infile.open(filename, std::ios::in);

  //! Check if input msh file is good
  if (infile.good()) {
    std::cout << "Element file found" << '\n';

    std::string line;

    //! Ignore first 4 lines
    for (unsigned k = 0; k < toplines; ++k) {
      std::getline(infile, line);
    }
    //! Get number of vertices
    infile >> nvertices;
    getline(infile, line);
    //! Skip past vertices section
    for (int i = 0; i < nvertices; ++i) {
      std::getline(infile, line);
    }
    //! Skip past element headers
    for (unsigned l = 0; l < 2; ++l) {
      std::getline(infile, line);
    }

    infile >> nelements;
    getline(infile, line);

    for (int i = 0; i < nelements; ++i) {
      std::getline(infile, line);
      std::istringstream istream(line);
      if (line.find('#') == std::string::npos && line != "") {
        istream >> elementid;
        istream >> elementtype;
        istream >> elementry;
        istream >> physical;
        istream >> elementry;

        //! If element type not == to specified Tvertices, skip element
        if (elementtype != element_type) {
          istream >> line;
        } else {
          istream >> elementarray.at(0) >> elementarray.at(1) >>
              elementarray.at(2) >> elementarray.at(3) >> elementarray.at(4) >>
              elementarray.at(5) >> elementarray.at(6) >> elementarray.at(7);

          elements_.insert(std::make_pair(elementid, elementarray));
        }
      }
    }
    infile.close();
  }
  std::cout << "Number of Elements: " << elements_.size() << '\n';

  //! Get the coordinates for each vertex of each element
  this->store_element_vertices();
}

//! Store element vertices
//! \tparam Tdim Dimension
//! \tparam Tvertices Number of vertices in element
template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::store_element_vertices() {

  const unsigned firstelement = elements_.begin()->first;
  const unsigned lastelement = elements_.rbegin()->first;

  std::array<double, Tvertices> elementkeyvalues;
  std::array<double, Tdim * Tvertices> verticesarray;

  //! Iterate through element_
  for (unsigned i = firstelement; i <= lastelement; ++i) {
    auto elementfind = elements_.find(i);
    if (elementfind != elements_.end()) {

      //! In each element, iterate to get vertices id's of the element
      for (unsigned j = 0; j < Tvertices; ++j) {
        elementkeyvalues.at(j) = elementfind->second[j];
      }
      //! Iterate through the vertices to get coordinates (4 for tetrahedral)
      for (unsigned k = 0; k < Tvertices; ++k) {
        //! Get the vertex wanted from the id
        auto verticesfind = vertices_.find(elementkeyvalues[k]);
        //! For each vertex, store the coordinates
        //! j = 0 -> [X], j = 1 -> [Y], j = 2 -> [Z]
        for (unsigned l = 0; l < Tdim; ++l) {
          verticesarray.at(k * Tdim + l) = verticesfind->second[l];
        }
      }

      elementcoordinates_.insert(
          std::make_pair(elementfind->first, verticesarray));
    }
  }
  std::cout
      << "The coordinates for vertices of each element have been stored.\n";
}

//! Compute material points based on the centroid
//! \tparam Tdim Dimension
//! \tparam Tvertices Number of vertices in element
template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::compute_material_points() {

  unsigned arrayposition = 0;

  Eigen::VectorXd pointsarray(Tdim);

  const unsigned firstelementcoord = elementcoordinates_.begin()->first;
  const unsigned lastelementcoord = elementcoordinates_.rbegin()->first;

  for (unsigned t = firstelementcoord; t < lastelementcoord + 1; ++t) {
    auto coordinatesfind = elementcoordinates_.find(t);
    if (coordinatesfind != elementcoordinates_.end()) {
      //! Store coordinates in 3x4 matrix
      Eigen::MatrixXd m(Tdim, Tvertices);
      for (unsigned i = 0; i < Tvertices; ++i) {
        for (unsigned j = 0; j < Tdim; ++j) {
          arrayposition = (i * Tdim) + j;
          m(j, i) = coordinatesfind->second[arrayposition];
        }
      }

      // Assign the centroid as the coordinate of the material point
      for (unsigned i = 0; i < Tdim; ++i) {
        pointsarray(i) = 0;
        for (unsigned j = 0; j < Tvertices; ++j) {
          pointsarray(i) += (1. / Tvertices) * m(i, j);
        }
      }

      materialpoints_.emplace_back(
          new Point<Tdim>(coordinatesfind->first, pointsarray));
    }
  }
  std::cout << "Number of Material Points: " << materialpoints_.size() << '\n';
}

//! Compute stresses of the material points
//! \tparam Tdim Dimension
//! \tparam Tvertices Number of vertices in element
template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::compute_stresses() {

  // Material density
  const double density = 22;
  // K0 static pressure coefficient
  const double k0 = 0.5;
  const double max_height = 3;
  const double conv_factor = 10;

  //! Loop through the points to get vertical and horizontal stresses
  //! Note that tau (shear stress) is assumed 0
  //! [2D], y is the vertical direction
  //! [3D], z is the vertical direction
  for (const auto& materialpoint : materialpoints_) {
    Eigen::VectorXd stress(Tdim * 2);
    stress.setZero();
    stress(Tdim - 1) = conv_factor *
                       (-(max_height - materialpoint->coordinates()(2))) *
                       density;
    for (unsigned i = 2; i <= Tdim; ++i) {
      stress(Tdim - i) = stress(Tdim - 1) * k0;
    }
    materialpoint->stress(stress);
  }
}
