template <unsigned Tdim>
std::vector<std::shared_ptr<Point<Tdim>>> Input<Tdim>::read_vertices(
    const std::string& filename) {

  //! \brief  Vector coordinate and id container
  std::vector<std::shared_ptr<Point<Tdim>>> vertices_;
  //! Number of vertices
  double nvertices = 0, toplines = 0;
  //! Vertices id
  unsigned vertid = std::numeric_limits<unsigned>::max();
  toplines = 4;
  //! Array to store vertices coordinates
  std::array<double, Tdim> verticesarray;

  std::fstream infile;
  infile.open(filename, std::ios::in);

  //! Open input file
  if (infile.is_open()) {
    std::cout << "vertices file found" << '\n';

    std::string line;

    //! Ignore first 4 lines
    for (unsigned i = 0; i < toplines; ++i) {
      std::getline(infile, line);
    }
    //! Get number of vertices
    infile >> nvertices;
    getline(infile, line);

    //! Get vertex coordinates & id
    for (int i = 0; i < nvertices; ++i) {
      std::getline(infile, line);
      std::istringstream istream(line);
      if (line.find('#') == std::string::npos && line != "") {
        istream >> vertid;
        istream >> verticesarray.at(0) >> verticesarray.at(1) >>
            verticesarray.at(2);
        vertices_.emplace_back(new Point<Tdim>(vertid, verticesarray));
      }
    }
    infile.close();
  } else {
    throw std::runtime_error("Vertices file not found");
  }
  std::cout << "Number of Vertices: " << vertices_.size() << '\n';

  return vertices_;
}

template <unsigned Tdim>
std::vector<std::shared_ptr<Point<Tdim>>> Input<Tdim>::read_elements(
    const std::string& filename) {

  //! Element Coordinate and id container
  std::vector<std::shared_ptr<Point<Tdim>>> elements_;
  //! Number of vertices
  double nvertices = std::numeric_limits<double>::max();
  //! Number of elements
  double nelements = std::numeric_limits<double>::max();
  //! Element type
  double elementtype = std::numeric_limits<double>::max();

  double physical = std::numeric_limits<double>::max();
  double elementry = std::numeric_limits<double>::max();
  //! Element id
  unsigned elementid = = std::numeric_limits<unsigned>::max();

  //! Array to store vertices coordinates
  std::array<double, Tdim> elementarray;

  std::fstream infile;
  infile.open(filename, std::ios::in);
  //! Open input file
  if (infile.is_open()) {
    std::cout << "Element file found" << '\n';

    std::string line;

    //! Ignore first 4 lines
    for (unsigned k = 0; k < 4; ++k) {
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
        if (elementtype != Tdim) {
          istream >> line;
        } else {
          istream >> elementarray.at(0) >> elementarray.at(1) >>
              elementarray.at(2) >> elementarray.at(3);
          elements_.emplace_back(new Point<Tdim>(elementid, elementarray));
        }
      }
    }
    infile.close();
  } else {
    throw std::runtime_error("Element file not found");
  }

  std::cout << "Number of Elements: " << elements_.size() << '\n';
  return elements_;
}
