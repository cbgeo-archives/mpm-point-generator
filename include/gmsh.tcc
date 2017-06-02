//! Read vertex id and coordinates in GMSH
//! \param[in] filename Input GMSH file
void GMSH::read_vertices(const std::string& filename) {

  //! Number of vertices
  double nvertices = std::numeric_limits<double>::max();
  const unsigned toplines = 4;
  const unsigned ndimension = 3;

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

    //! Initialize two variables for the loop
    std::array<double, ndimension> coord;
    unsigned vertid = 0;

    //! Read vertex coordinates & id
    for (int i = 0; i < nvertices; ++i) {
      std::getline(infile, line);
      std::istringstream istream(line);

      if (line.find('#') == std::string::npos && line != "") {
        //! Coordinates of vertex
        istream >> vertid;
        istream >> coord.at(0) >> coord.at(1) >> coord.at(2);

        //! change from 1 base to 0 base
        vertid -= 1;

        //! Store to member variables
        vertid_.push_back(vertid);
        coords_.push_back(coord);
      }
    }
    infile.close();
  }
  std::cout << "Number of Vertices: " << coords_.size() << '\n';
  nvertices_ = coords_.size();
  std::cout << "Read vertices.\n";
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

  //! Array to store vertices coordinates
  std::array<double, ndimension> elementarray;

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
        //! \details If element type not == to Tdim, skip element
        // if (elementtype != ndimension) {
        //   istream >> line;
        // } else {
        //   istream >> elementarray.at(0) >> elementarray.at(1) >>
        //       elementarray.at(2) >> elementarray.at(3);
        //   elements_.emplace_back(
        //       new Point<ndimension>(elementid, elementarray));
        // }
      }
    }
    infile.close();
  }

  std::cout << "Number of Elements: " << elements_.size() << '\n';
}

//! \brief compute initial stress from points
void GMSH::compute_stresses() {

  const double density = 22;
  const double k0 = 0.5;
  const double max_height = 3;
  const double conv_factor = 10;
  double ver_stress;
  double hor_stress;

  //! Loop through the points to get vertical and horizontal stresses
  //! Note that tau (shear stress) is assumed 0
  for (const auto& point : coords_) {
    ver_stress = conv_factor * (-(max_height - point.at(2))) * density;
    hor_stress = ver_stress * k0;
    stress_.push_back(
        std::array<double, 6>{hor_stress, hor_stress, ver_stress, 0, 0, 0});
  }

  std::cout << "Computed initial stresses.\n";
}

//! \brief generate material points
void GMSH::generate_points() {

  const unsigned ndimension = 3;

  for (unsigned i = 0; i < nvertices_; ++i) {
    points_.emplace_back(
        new Point<ndimension>(vertid_.at(i), coords_.at(i), stress_.at(i)));
  }

  std::cout << "Generated material points.\n";
}
