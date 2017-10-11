#ifndef MPM_GAUSS_POINTS_H_
#define MPM_GAUSS_POINTS_H_

namespace gauss_points {

//! Map to store gauss points coefficients
const std::map<unsigned, std::vector<double>> gauss_points{
    {1, {0}},
    {2, {-0.5773502691896257, 0.5773502691896257}},
    {3, {-0.7745966692414834, 0, 0.7745966692414834}},
    {4,
     {-0.8611363115940526, -0.3399810435848563, 0.3399810435848563,
      0.8611363115940526}},
    {5,
     {-0.9061798459386640, -0.5384693101056831, 0, 0.5384693101056831,
      0.9061798459386640}}};
}

#endif  // MPM_GAUSS_POINTS_H_
