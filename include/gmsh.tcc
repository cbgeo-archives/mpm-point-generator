//! Read vertex id and coordinates in GMSH
//! \tparam Tdim Dimension, Tvertices Number of vertices in element

template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::read_vertices(const std::string& filename) {

  //! Number of vertices
  double nvertices = std::numeric_limits<double>::max();
  const unsigned toplines = 4;

  //! Vertices id
  unsigned vertid;

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
//! \tparam Tdim Dimension, Tvertices Number of vertices in element
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
  // specify element type 4 = tetrahedral
  const unsigned element_type = 4;

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
              elementarray.at(2) >> elementarray.at(3);

          elements_.insert(std::make_pair(elementid, elementarray));
        }
      }
    }
    infile.close();
  }
  std::cout << "Number of Elements: " << elements_.size() << '\n';

  //! Get the coordinates for each vertex of each element
  GMSH::store_element_vertices();
}

//! \tparam Tdim Dimension, Tvert Number of vertices in element
template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::store_element_vertices() {

  const unsigned firstelement = elements_.begin()->first;
  const unsigned lastelement = elements_.rbegin()->first;

  typename std::map<double, std::array<double, Tvertices>>::iterator
      elementfind;
  typename std::map<double, std::array<double, Tdim>>::iterator verticesfind;

  std::array<double, Tvertices> elementkeyvalues;
  std::array<double, Tdim * Tvertices> verticesarray;

  //! Iterate through element_
  for (unsigned q = firstelement; q <= lastelement; ++q) {
    elementfind = elements_.find(q);
    if (elementfind != elements_.end()) {

      //! In each element, iterate to get vertices id's of the element
      for (unsigned j = 0; j < Tvertices; ++j) {
        elementkeyvalues[j] = elementfind->second[j];
      }
      //! Iterate through the vertices to get coordinates (4 for tetrahedral)
      for (unsigned q = 0; q < Tvertices; ++q) {
        //! Get the vertex wanted from the id
        verticesfind = vertices_.find(elementkeyvalues[q]);
        //! For each vertex, store the coordinates
        //! j = 0 -> [X], j = 1 -> [Y], j = 2 -> [Z]
        for (unsigned j = 0; j < Tdim; ++j) {
          verticesarray[q * Tdim + j] = verticesfind->second[j];
        }
      }

      elementcoordinates_.insert(
          std::make_pair(elementfind->first, verticesarray));
    }
  }
  std::cout
      << "The coordinates for vertices of each element have been stored.\n";
}

//! \tparam Tdim Dimension, Tvert Number of vertices in element
template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::compute_material_points() {

  unsigned arrayposition = 0;

  std::array<double, Tdim> pointsarray;
  typename std::map<double, std::array<double, Tdim * Tvertices>>::iterator
      coordinatesfind;

  const unsigned firstelementcoord = elementcoordinates_.begin()->first;
  const unsigned lastelementcoord = elementcoordinates_.rbegin()->first;

  for (unsigned t = firstelementcoord; t < lastelementcoord + 1; ++t) {
    coordinatesfind = elementcoordinates_.find(t);
    if (coordinatesfind != elementcoordinates_.end()) {
      //! Store coordinates in 3x4 matrix
      Eigen::MatrixXd m(Tdim, Tvertices);
      for (unsigned i = 0; i < Tvertices; ++i) {
        for (unsigned j = 0; j < Tdim; ++j) {
          arrayposition = (i * Tdim) + j;
          m(j, i) = coordinatesfind->second[arrayposition];
        }
      }

      // Centroid test
      //++++++++++++++++++++++++++++++++++++++
      for (unsigned i = 0; i < Tdim; ++i) {
        // reset array values
        pointsarray[i] = 0;
        for (unsigned j = 0; j < Tvertices; ++j) {
          pointsarray[i] += 0.25 * m(i, j);
        }
      }
      //++++++++++++++++++++++++++++++++++++++

      Mesh<Tdim>::materialpoints_.emplace_back(
          new Point<Tdim>(coordinatesfind->first, pointsarray));
    }
  }
  std::cout << "Number of Material Points: "
            << Mesh<Tdim>::materialpoints_.size() << '\n';
}
//! Compute stresses
//! \tparam Tdim Dimension, Tvert Number of vertices in element
template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::compute_stresses() {

  const double density = 22;
  const double k0 = 0.5;
  const double max_height = 3;
  const double conv_factor = 10;
  double ver_stress;
  double hor_stress;

  //! Loop through the points to get vertical and horizontal stresses
  //! Note that tau (shear stress) is assumed 0
  for (const auto& point : Mesh<Tdim>::materialpoints_) {
    ver_stress =
        conv_factor * (-(max_height - point->coordinates().at(2))) * density;
    hor_stress = ver_stress * k0;
    std::array<double, Tdim * 2> stress{hor_stress, hor_stress, ver_stress,
                                        0,          0,          0};
    Mesh<Tdim>::stress_.emplace_back(stress);
  }
}
