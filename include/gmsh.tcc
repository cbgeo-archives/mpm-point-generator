//! Read mesh
//! \tparam Tdim Dimension
//! \tparam Tvertices Number of vertices in element
//! \param[in] filename Input mesh filename
template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::read_mesh(const std::string& filename) {

  std::ifstream file;
  file.open(filename.c_str(), std::ios::in);
  if (!file.is_open())
    throw std::runtime_error("Specified GMSH file does not exist");
  if (file.good()) {
    read_vertices(file);
    read_elements(file);
  }
  file.close();
}

//! Read keyword
//! \tparam Tdim Dimension
//! \tparam Tvertices Number of vertices in element
//! \param[in] filename Input mesh filename
//! \param[in] keyword search for the word of interest
template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::read_keyword(std::ifstream& file,
                                         const std::string& keyword) {

  bool read_status = false;
  std::string line;
  file.clear();
  file.seekg(0, std::ios::beg);

  //! The loop is trying to find specific keyword and get the line number
  //! The code will obtain the data after the specific keyword
  //! Should the keyword is not found, it terminates and sends error messsage

  while (std::getline(file, line)) {
    if (line != keyword) {
      if (line.find(keyword) != std::string::npos) {
        break;
      };
    } else {
      std::cout << "Read keyword: " << keyword << " successfully\n";
      read_status = true;
      break;
    }
  }
  if (!read_status) std::cerr << "Cannot find keyword: " << keyword << '\n';
}

//! Read vertex id and coordinates in GMSH
//! \tparam Tdim Dimension
//! \tparam Tvertices Number of vertices in element
//! \param[in] filename Input mesh filename
template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::read_vertices(std::ifstream& file) {

  //! Find the line of interest
  read_keyword(file, "$Nodes");

  std::string line;
  std::getline(file, line);
  std::istringstream istream(line);

  //! Read number of vertices
  unsigned nvertices = std::numeric_limits<unsigned>::max();
  istream >> nvertices;
  getline(istream, line);

  //! Vertices id
  unsigned vertid = 0;

  //! Read vertex coordinates & id
  for (unsigned i = 0; i < nvertices; ++i) {
    std::getline(file, line);
    std::istringstream istream(line);

    if (line.find('#') == std::string::npos && line != "") {
      //! Coordinates of vertex
      Eigen::VectorXd vertex(Tdim);

      istream >> vertid;

      if (Tdim == 3) {
        istream >> vertex[0] >> vertex[1] >> vertex[2];
      } else {
        istream >> vertex[0] >> vertex[1];
      }
      this->vertices_.insert(std::make_pair(vertid, vertex));
    }
  }

  this->nvertices_ = vertices_.size();

  //! Check that the number of vertices are correct
  if (nvertices_ != nvertices)
    std::cout << "Error: number of vertices do not match.\n";

  std::cout << "Number of Vertices: " << nvertices_ << '\n';
}

//! Read GMSH elements
//! \tparam Tdim Dimension
//! \tparam Tvertices Number of vertices in element
//! \param[in] filename Input mesh filename and directory
template <unsigned Tdim, unsigned Tvertices>
void GMSH<Tdim, Tvertices>::read_elements(std::ifstream& file) {

  //! Find the line of interest
  read_keyword(file, "$Elements");

  std::string line;
  std::getline(file, line);
  std::istringstream istream(line);

  //! Number of elements
  unsigned nelements = std::numeric_limits<unsigned>::max();
  istream >> nelements;
  getline(istream, line);

  //! Element type
  double elementtype = std::numeric_limits<double>::max();

  double physical = std::numeric_limits<double>::max();
  double elementry = std::numeric_limits<double>::max();
  
  //! Element id
  unsigned elementid = std::numeric_limits<unsigned>::max();

  //! Array to store vertices coordinates
  Eigen::VectorXd elementarray(Tvertices);

  //! specify element type 4 = tetrahedral, 5 = hexahedron
  //! Documentation from GMSH
  //! 2 - Triangle (3 nodes)
  //! 3 - Quadrangle (4 nodes)
  //! 4 - Tetrahedron (4 nodes)
  //! 5 - Hexahedron (8 nodes)
  //! For more informtion on element types, visit:
  //! http://gmsh.info/doc/texinfo/gmsh.html#File-formats
  const unsigned element_type = 5;

  //! Iterate through all elements in the file
  for (unsigned i = 0; i < nelements; ++i) {
    std::getline(file, line);
    std::istringstream istream(line);
    if (line.find('#') == std::string::npos && line != "") {
      istream >> elementid >> elementtype >> elementry >> physical >> elementry;

      //! If element type not equals to specified Tvertices, skip element
      if (elementtype != element_type) {
        istream >> line;
      } else {
        istream >> elementarray[0] >> elementarray[1] >> elementarray[2] >>
            elementarray[3] >> elementarray[4] >> elementarray[5] >>
            elementarray[6] >> elementarray[7];
        this->elements_.insert(std::make_pair(elementid, elementarray));
      }
    }
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

  Eigen::VectorXd elementkeyvalues(Tvertices);
  Eigen::VectorXd verticesarray(Tdim * Tvertices);

  //! Iterate through element_
  for (unsigned i = 0; i < elements_.size(); ++i) {
    auto elementfind = elements_.find(i);
    if (elementfind != elements_.end()) {

      //! In each element, iterate to get vertices id's of the element
      for (unsigned j = 0; j < Tvertices; ++j) {
        elementkeyvalues[j] = elementfind->second[j];
      }
      //! Iterate through the vertices to get coordinates (4 for tetrahedral)
      for (unsigned k = 0; k < Tvertices; ++k) {
        //! Get the vertex wanted from the id
        auto verticesfind = vertices_.find(elementkeyvalues[k]);
        //! For each vertex, store the coordinates
        //! j = 0 -> [X], j = 1 -> [Y], j = 2 -> [Z]
        for (unsigned l = 0; l < Tdim; ++l) {
          verticesarray[k * Tdim + l] = verticesfind->second[l];
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
        pointsarray[i] = 0;
        for (unsigned j = 0; j < Tvertices; ++j) {
          pointsarray[i] += (1. / Tvertices) * m(i, j);
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
  const double conv_factor = 10;

  double max_height = std::numeric_limits<double>::min();

  //! [2D], y is the vertical direction
  //! [3D], z is the vertical direction
  //! In general, [Tdim - 1]
  for (const auto& point : materialpoints_) {
    if (point->coordinates()[Tdim - 1] > max_height) {
      max_height = point->coordinates()[Tdim - 1];
    }
  }

  //! Loop through the points to get vertical and horizontal stresses
  //! Note that tau (shear stress) is assumed 0
  //! [2D], y is the vertical direction
  //! [3D], z is the vertical direction
  for (const auto& materialpoint : materialpoints_) {
    Eigen::VectorXd stress(Tdim * 2);
    stress.setZero();
    stress[Tdim - 1] = conv_factor *
                       (-(max_height - materialpoint->coordinates()[2])) *
                       density;
    for (unsigned i = 2; i <= Tdim; ++i) {
      stress[Tdim - i] = stress[Tdim - 1] * k0;
    }
    materialpoint->stress(stress);
  }
}
