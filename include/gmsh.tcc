//! Read vertex id and coordinates in GMSH
//! \param[in] filename Input GMSH file
void GMSH::read_vertices(const std::string& filename) {

  //! Number of vertices
  double nvertices = std::numeric_limits<double>::max();
  const unsigned toplines = 4;
  const unsigned ndimension = 3;

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
        std::array<double, ndimension> vertex;

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
//! \param[in] filename Input GMSH file
void GMSH::read_elements(const std::string& filename) {

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
  const unsigned ndimension = 3;
  // specify element type 4 = tetrahedral
  const unsigned elementype = 4;
  // specify element vertices 4 = tetrahedral
  const unsigned elementvertices = 4;

  //! Array to store vertices coordinates
  std::array<double, elementvertices> elementarray;

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
        //! \details If element type not == to specified elementtype_, skip
        //! element
        if (elementtype != elementype) {
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
}

void GMSH::store_element_vertices() {
  const unsigned firstelement = elements_.begin()->first;
  const unsigned lastelement = elements_.rbegin()->first;

  std::map<double, std::array<double, 4>>::iterator elementfind;
  std::map<double, std::array<double, 3>>::iterator verticesfind;

  std::array<double, 4> elementkeyvalues;
  std::array<double, 12> verticesarray;

  //! Iterate through element_
  for (unsigned q = firstelement; q < lastelement + 1; ++q) {
    elementfind = elements_.find(q);
    if (elementfind != elements_.end()) {

      elementkeyvalues[0] = elementfind->second[0];
      elementkeyvalues[1] = elementfind->second[1];
      elementkeyvalues[2] = elementfind->second[2];
      elementkeyvalues[3] = elementfind->second[3];

      for (unsigned q = 0; q < 4; ++q) {
        if (q == 0) {
          verticesfind = vertices_.find(elementkeyvalues[0]);
          if (elementfind != elements_.end()) {
            verticesarray[0] = verticesfind->second[0];
            verticesarray[1] = verticesfind->second[1];
            verticesarray[2] = verticesfind->second[2];
          } else {
          }
        } else {
        }
        if (q == 1) {
          verticesfind = vertices_.find(elementkeyvalues[1]);
          if (elementfind != elements_.end()) {
            verticesarray[3] = verticesfind->second[0];
            verticesarray[4] = verticesfind->second[1];
            verticesarray[5] = verticesfind->second[2];
          } else {
          }
        } else {
        }
        if (q == 2) {
          verticesfind = vertices_.find(elementkeyvalues[2]);
          if (elementfind != elements_.end()) {
            verticesarray[6] = verticesfind->second[0];
            verticesarray[7] = verticesfind->second[1];
            verticesarray[8] = verticesfind->second[2];
          } else {
          }
        } else {
        }
        if (q == 3) {
          verticesfind = vertices_.find(elementkeyvalues[3]);
          if (elementfind != elements_.end()) {
            verticesarray[9] = verticesfind->second[0];
            verticesarray[10] = verticesfind->second[1];
            verticesarray[11] = verticesfind->second[2];
          } else {
          }
        } else {
        }
      }
      elementcoordinates_.insert(
          std::make_pair(elementfind->first, verticesarray));
    } else {
    }
  }
}

void GMSH::compute_material_points() {

  double xcoord;
  double ycoord;
  double zcoord;

  std::array<double, 3> pointsarray;
  std::map<double, std::array<double, 12>>::iterator coordinatesfind;

  const unsigned firstelementcoord = elementcoordinates_.begin()->first;
  const unsigned lastelementcoord = elementcoordinates_.rbegin()->first;

  for (unsigned t = firstelementcoord; t < lastelementcoord + 1; ++t) {
    coordinatesfind = elementcoordinates_.find(t);
    if (coordinatesfind != elementcoordinates_.end()) {

      MatrixXd m(3, 4);

      m(0, 0) = coordinatesfind->second[0];
      m(1, 0) = coordinatesfind->second[1];
      m(2, 0) = coordinatesfind->second[2];

      m(0, 1) = coordinatesfind->second[3];
      m(1, 1) = coordinatesfind->second[4];
      m(2, 1) = coordinatesfind->second[5];

      m(0, 2) = coordinatesfind->second[6];
      m(1, 2) = coordinatesfind->second[7];
      m(2, 2) = coordinatesfind->second[8];

      m(0, 3) = coordinatesfind->second[9];
      m(1, 3) = coordinatesfind->second[10];
      m(2, 3) = coordinatesfind->second[11];

      // Centroid test
      //++++++++++++++++++++++++++++++++++++++
      xcoord = 0.25 * (m(0, 0) + m(0, 1) + m(0, 2) + m(0, 3));
      ycoord = 0.25 * (m(1, 0) + m(1, 1) + m(1, 2) + m(1, 3));
      zcoord = 0.25 * (m(2, 0) + m(2, 1) + m(2, 2) + m(2, 3));

      pointsarray[0] = xcoord;
      pointsarray[1] = ycoord;
      pointsarray[2] = zcoord;
      //++++++++++++++++++++++++++++++++++++++

      materialpoints_.emplace_back(
          new Point<3>(coordinatesfind->first, pointsarray));
    }
  }
    std::cout << "Number of material points: " << materialpoints_.size() << '\n';
}
//! Compute stresses
void GMSH::compute_stresses() {

  double density = 22;
  double k0 = 0.5;
  double max_height = 3;
  double conv_factor = 10;
  double ver_stress;
  double hor_stress;

  //! Loop through the points to get vertical and horizontal stresses
  //! Note that tau (shear stress) is assumed 0
  for (const auto& point : materialpoints_) {
    ver_stress =
        conv_factor * (-(max_height - point->coordinates().at(2))) * density;
    hor_stress = ver_stress * k0;
    std::array<double, 6> stress{hor_stress, hor_stress, ver_stress, 0, 0, 0};
    stress_.emplace_back(stress);
  }

  std::cout << "Initial stresses for material points computed.\n";
}
