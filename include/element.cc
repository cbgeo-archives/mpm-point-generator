

//! Calculate volume of an element
//!\retval volume of an element
double Element::calculate_volume() {

  /* Node numbering as read in by mesh file
   *
         0-------1
        /|      / |
       / |     /  |
      /  |    /   |
      3--|----2   |
      |  |    |   |
      |  4----|---5
      |  /    |  /
      | /     | /
      |/      |/
      7-------6

      * Calculation of hexahedron volume from
      * https://arc.aiaa.org/doi/pdf/10.2514/3.9013
   */

  const Eigen::Vector3d a(coordinates_.at(3)[0], coordinates_.at(3)[1],
                          coordinates_.at(3)[2]),
      b(coordinates_.at(2)[0], coordinates_.at(2)[1], coordinates_.at(2)[2]),
      c(coordinates_.at(1)[0], coordinates_.at(1)[1], coordinates_.at(1)[2]),
      d(coordinates_.at(0)[0], coordinates_.at(0)[1], coordinates_.at(0)[2]),
      e(coordinates_.at(7)[0], coordinates_.at(7)[1], coordinates_.at(7)[2]),
      f(coordinates_.at(6)[0], coordinates_.at(6)[1], coordinates_.at(6)[2]),
      g(coordinates_.at(5)[0], coordinates_.at(5)[1], coordinates_.at(5)[2]),
      h(coordinates_.at(4)[0], coordinates_.at(4)[1], coordinates_.at(4)[2]);

  const double volume =
      (1.0 / 12) * (a - g).dot(((b - d).cross(c - a)) + ((e - b).cross(f - a)) +
                               ((d - e).cross(h - a))) +
      (1.0 / 12) *
          (b - g).dot(((b - d).cross(c - a)) + ((c - g).cross(c - f))) +
      (1.0 / 12) *
          (e - g).dot(((e - b).cross(f - a)) + ((f - g).cross(h - f))) +
      (1.0 / 12) * (d - g).dot(((d - e).cross(h - a)) + ((h - g).cross(h - c)));

  return volume;
}
