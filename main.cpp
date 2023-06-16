#include <cstdio>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#define USE_EIGEN3
#ifdef USE_EIGEN3
#include "eigen3/Eigen/Eigenvalues"
#include "eigen3/Eigen/Dense"
using namespace Eigen;
#endif

#define PI 3.1415926535897932384626
#define REPORT_ERROR ;std::cout << "Got an ERROR! " << std::endl;

class Quat{
public:
  double x, y, z, w;

  Quat()
    : x(0), y(0), z(0), w(0){}

  Quat(double x_, double y_, double z_, double w_)
    : x(x_), y(y_), z(z_), w(w_){}

  double norm(){
    return sqrt(x*x + y*y + z*z + w*w);
  }

  Quat normalize(){
    double l = sqrt(x*x + y*y + z*z + w*w);
    if (l < 1e-6) { REPORT_ERROR }; // got a bug
    return {x/l, y/l, z/l, w/l};
  }

  Quat conj(){
    return {x, -y, -z, -w};
  }

  Quat inv(){
    double l = x*x + y*y + z*z + w*w;
    if (l < 1e-6) REPORT_ERROR; // got a bug
    return {x/l,-y/l, -z/l, -w/l};
  }

  Quat operator+(Quat p){
    return {x + p.x, y + p.y, z + p.z, w + p.w};
  }

  Quat operator-(Quat p){
    return {x - p.x, y - p.y, z - p.z, w - p.w};
  }

  Quat operator*(double r){
    return {r * x, r * y, r * z, r * w}; 
  }

  Quat operator*(Quat p){
    return {
        x*p.x - y*p.y - z*p.z - w*p.w,
        x*p.y + p.x*y + z*p.w - w*p.z,
        x*p.z + p.x*z + w*p.y - y*p.w,
        x*p.w + p.x*w + y*p.z - z*p.y
      };
  }

  Quat operator/(double r){
    return {x / r, y / r, z / r, w / r}; 
  }

  Quat operator/(Quat p){
    return *this * p.inv();
  }

  Quat rot(Quat p){
    // assert *this should be normalized
    Quat n = normalize();
    return (n * p) * n.inv();
  }


  double to_eular(){
    Quat n = normalize();
    return acos(n.x) * 2; // there symetry
  }

#ifdef USE_EIGEN3
  Quat(Vector3d v)
    : x(0), y(v[0]), z(v[1]), w(v[2]) {}

  Quat(Vector3d v, double theta){
    x = cos(theta/2);
    double norm = v.norm();
    y = sin(theta/2) * v[0] / norm;
    z = sin(theta/2) * v[1] / norm;
    w = sin(theta/2) * v[2] / norm;
  }

  Vector3d rot(Vector3d v){
    Quat p(v);
    return rot(p).vec();
  }

  Matrix3d to_mat(){
    // got v and x
    double x = this->x;
    Vector3d v{y,z,w};
    Matrix3d vm{
      {    0, -v[2],  v[1]},
      { v[2],     0, -v[0]},
      {-v[1],  v[0],     0}
    };
    Matrix3d vtv{
      { v[0]*v[0], v[0]*v[1], v[0]*v[2]},
      { v[1]*v[0], v[1]*v[1], v[1]*v[2]},
      { v[2]*v[0], v[2]*v[2], v[2]*v[2]}
    };
    Matrix3d I = Matrix3d::Identity();
    return (2 * x*x - 1) * I + 2 * vtv + 2 * x * vm;  
  }

  Vector3d vec(){
    return {y, z, w};
  }
#endif

};

std::ostream& operator<<(std::ostream& out, const Quat p){
  // the way `std::cout << Quat << std::endl;` and of course other customized methods.
  out <<  "(" << p.x << "," << p.y << "i," << p.z << "j," << p.w << "k)";
  return out;
}


#ifdef USE_EIGEN3
Quat mat_to_quat(Matrix3d m){
  // Rot Matrix? m.T * m == Id ? 
  //
  // find the v of quat, which can be a real eigen vector of m.
  EigenSolver<Matrix3d> solver(m);
  auto e_v = solver.eigenvalues();
  auto e_vec = solver.eigenvectors();
  unsigned int t;
  for(t=0; t<3;t++)
    if(abs(e_v[t].imag()) < 1e-6) break;
  if (t >= 3) { REPORT_ERROR; }
  auto vec_t = e_vec.col(t);
  Vector3d v{
    vec_t[0].real(), 
    vec_t[1].real(), 
    vec_t[2].real(), 
  };

  // solve the equation of `(I - v.T * v) * cos + [v] * sin + v.T * v = m`
  // i.e. A cos + B sin = X 
  Matrix3d A = Matrix3d::Identity() - v * v.transpose();
  Matrix3d B{
    {   0 , -v[2],  v[1]},
    { v[2],    0 , -v[0]},
    {-v[1],  v[0],    0 }
  };
  MatrixXd T(9, 2), X = (m - v * v.transpose()).reshaped();
  T << A.reshaped(), B.reshaped();
  Vector2d c_s = T.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(X);

  // Done, got and return!
  double theta = std::acos(c_s[0]);
  return Quat{v, theta};
} 
#endif 

void test(){
  Quat q1{1,2,3,4};
  Quat q2({1,1,1}, PI/3);

  std::cout << "q1 = " << q1 << ", norm = " << q1.norm() << std::endl;
  std::cout << "q2 = " << q2 << ", norm = " << q2.norm() << std::endl;
  std::cout << "q1 + q2 = " << q1 + q2 << std::endl;
  std::cout << "12 * q1 = " << q1 * 12 << std::endl;
  std::cout << "q1.normalize()" << q1.normalize() << std::endl; 

  Matrix3d m = q2.to_mat();
  std::cout << "q2.to_mat(): m = " << std::endl << m << std::endl << std::endl;
  std::cout << "m.T * m = " << std::endl << m.transpose() * m << std::endl << std::endl; 
  std::cout << "mat_to_quat(m): " << mat_to_quat(m) << std::endl << std::endl;
}

int main(){
  test();
  return 0;
}
