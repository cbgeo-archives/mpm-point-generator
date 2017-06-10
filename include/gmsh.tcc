//! Read vertex id and coordinates in GMSH
//! \param[in] filename Input GMSH file
//! \Param[in] Tdim = Dimension, Tvert = n vertices in element
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
        Mesh<Tdim, Tvertices>::vertices_.insert(std::make_pair(vertid, vertex));
      }
    }
    infile.close();
  }
  std::cout << "Number of Vertices: " << Mesh<Tdim, Tvertices>::vertices_.size()
            << '\n';
}

//! Read GMSH elements
//! \param[in] filename Input GMSH file
//! \Param[in] Tdim = Dimension, Tvert = n vertices in element
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

        //! \brief Check element type
        //! \details If element type not == to specified Tvertices, skip
        //! element
        if (elementtype != Tvertices) {
          istream >> line;
        } else {
          istream >> elementarray.at(0) >> elementarray.at(1) >>
              elementarray.at(2) >> elementarray.at(3);

          Mesh<Tdim, Tvertices>::elements_.insert(
              std::make_pair(elementid, elementarray));
        }
      }
    }
    infile.close();
  }
  std::cout << "Number of Elements: " << Mesh<Tdim, Tvertices>::elements_.size()
            << '\n';

  //! Get the coordinates for each vertex of each element
  GMSH::store_element_vertices();
}

//! \brief store each coordinates of an element
//! \Param[in] Tdim = Dimension, Tvert = n vertices in element
template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::store_element_vertices() {

  const unsigned firstelement = Mesh<Tdim, Tvertices>::elements_.begin()->first;
  const unsigned lastelement = Mesh<Tdim, Tvertices>::elements_.rbegin()->first;

  typename std::map<unsigned, std::array<double, Tvertices>>::iterator
      elementfind;
  typename std::map<unsigned, std::array<double, Tdim>>::iterator verticesfind;

  std::array<double, Tvertices> elementkeyvalues;
  std::array<double, Tdim * Tvertices> verticesarray;

  //! Iterate through element_
  for (unsigned i = firstelement; i <= lastelement; ++i) {
    elementfind = Mesh<Tdim, Tvertices>::elements_.find(i);
    if (elementfind != Mesh<Tdim, Tvertices>::elements_.end()) {

      //! In each element, iterate to get vertices id's of the element
      for (unsigned j = 0; j < 4; ++j) {
        elementkeyvalues[j] = elementfind->second[j];
      }
      //! Iterate through the vertices to get coordinates (4 for tetrahedral)
      for (unsigned j = 0; j < 4; ++j) {
        //! Get the vertex wanted from the id
        verticesfind =
            Mesh<Tdim, Tvertices>::vertices_.find(elementkeyvalues[j]);
        //! For each vertex, store the coordinates
        //! k = 0 -> [X], k = 1 -> [Y], k = 2 -> [Z]
        for (unsigned k = 0; k <= 2; ++k) {
          verticesarray[j * 3 + k] = verticesfind->second[k];
        }
      }

      Mesh<Tdim, Tvertices>::elementcoordinates_.insert(
          std::make_pair(elementfind->first, verticesarray));
    }
  }
  std::cout
      << "The coordinates for vertices of each element have been stored.\n";
}

//! \brief generate material points from elements
//! \Param[in] Tdim = Dimension, Tvert = n vertices in element
template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::compute_material_points() {

  unsigned arrayposition = 0;

  typename std::map<unsigned, std::array<double, Tdim * Tvertices>>::iterator
      coordinatesfind;

  const unsigned firstelementcoord =
      Mesh<Tdim, Tvertices>::elementcoordinates_.begin()->first;
  const unsigned lastelementcoord =
      Mesh<Tdim, Tvertices>::elementcoordinates_.rbegin()->first;

  for (unsigned t = firstelementcoord; t < lastelementcoord + 1; ++t) {
    coordinatesfind = Mesh<Tdim, Tvertices>::elementcoordinates_.find(t);
    if (coordinatesfind != Mesh<Tdim, Tvertices>::elementcoordinates_.end()) {
      //! Store coordinates in 3x4 matrix
      Eigen::MatrixXd m(3, 4);
      for (unsigned i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < 4; ++j) {
          arrayposition = (j * 3) + i;
          m(i, j) = coordinatesfind->second[arrayposition];
        }
      }

      //! Initialize array to contain points (need re-initialize as 0)
      std::array<double, Tdim> pointsarray{0, 0, 0};

      //! Centroid test
      //++++++++++++++++++++++++++++++++++++++
      for (unsigned i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < 4; j++) {
          pointsarray[i] += 0.25 * m(i, j);
        }
      }
      //++++++++++++++++++++++++++++++++++++++

      Mesh<Tdim, Tvertices>::materialpoints_.emplace_back(
          new Point<Tdim>(coordinatesfind->first, pointsarray));
    }
  }
  std::cout << "Number of Material Points: "
            << Mesh<Tdim, Tvertices>::materialpoints_.size() << '\n';
}

//! \brief Compute stresses
//! \Param[in] Tdim = Dimension, Tvert = n vertices in element
template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::compute_stresses() {

  const double density = 22;
  const double k0 = 0.5;
  const double max_height = 3;
  const double conv_factor = 10;
  const unsigned stress_comp = 6;
  double ver_stress;
  double hor_stress;

  //! Loop through the points to get vertical and horizontal stresses
  //! Note that tau (shear stress) is assumed 0
  for (const auto& point : Mesh<Tdim, Tvertices>::materialpoints_) {
    ver_stress =
        conv_factor * (-(max_height - point->coordinates().at(2))) * density;
    hor_stress = ver_stress * k0;
    std::array<double, stress_comp> stress{hor_stress, hor_stress, ver_stress,
                                           0,          0,          0};
    Mesh<Tdim, Tvertices>::stress_.emplace_back(stress);
  }

  std::cout << "Initial stresses for material points computed.\n";
}
