#include <cstdio>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>


#define USE_EIGEN3
#ifdef USE_EIGEN3
#include <eigen3/Eigen/Eigenvalues>
#include <eigen3/Eigen/Dense>
using namespace Eigen;
#endif

class Quat{
public:
  double x, y, z, w;

  Quat ()
    : x(0), y(0), z(0), w(0){}

  Quat(double x_, double y_, double z_, double w_)
    : x(x_), y(y_), z(z_), w(w_) { }

  Quat(Vector3d v)
    : x(0), y(v[0]), z(v[1]), w(v[2]) { }

  Quat (Vector3d v, double theta){
    this->x = cos(theta/2);
    double norm = v.norm();
    this->y = sin(theta/2) * v[0] / norm;
    this->z = sin(theta/2) * v[1] / norm;
    this->w = sin(theta/2) * v[2] / norm;
  }

  double norm(){
    return sqrt(x*x + y*y + z*z + w*w);
  }

  Quat normalize(){
    return *this / this->norm();
  }

  Quat conj(){
    return {x, -y, -z, -w};
  }

  Quat inv(){
    double l = x*x + y*y + z*z + w*w;
    if (l < 1e-6) {} // got a bug
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
    // assert *this is normalized
    return (*this * p) * this->inv();
  }

  Vector3d rot(Vector3d v){
    Quat p(v);
    return (this->rot(p)).to_vec();
  }

  double to_eular(){
    Quat n = normalize();
    return acos(n.x); // there symetry
  }

  std::vector<std::vector<double>> to__mat(){
    std::vector<std::vector<double>> ret{
      {1 - 2*(z*z + w*w), y*z - w*x, 2*(y*w + z*x)},
      {2*(y*z + w*x), 1 - 2*(x*x + w*w), 2*(z*w - x*y)},
      {2*(y*w - z*x), 2*(z*w + y*x), 1 - 2*(y*y + z*z)}
    };
    return ret;
  }

  Matrix3d to_mat(){
    Matrix3d ret{
      {1-2*(z*z+w*w), y*z - w*x,     2*(y*w+z*x)  },
      {2*(y*z+w*x),   1-2*(x*x+w*w), 2*(z*w-x*y)  },
      {2*(y*w-z*x),   2*(z*w+y*x),   1-2*(y*y+z*z)}
    };
    return ret;
  }

  Vector3d to_vec(){
    return Vector3d{y, z, w};
  }
};

std::ostream& operator<<(std::ostream& out, const Quat p){
  out <<  "(" << p.x << "," << p.y << "i," << p.z << "j," << p.w << "k)";
  return out;
}

Quat mat_to_quat(Matrix3d m){
  EigenSolver<Matrix3d> solver(m);
  auto eigen_values = solver.eigenvalues();
  auto eigen_vectors = solver.eigenvectors();
  unsigned int t;
  for(t=0; t<3;t++)
    if(abs(eigen_values[t].imag()) < 1e-6) break;

  auto vec_t = eigen_vectors.col(t);
  Vector3d v{
    vec_t[0].real(), 
    vec_t[1].real(), 
    vec_t[2].real(), 
  };
  Matrix3d A = Matrix3d::Identity() - v * v.transpose();
  Matrix3d B{
    {    0, -v[2],  v[1]},
    { v[2],     0, -v[0]},
    {-v[1],  v[0],     0}
  };
  MatrixXd T(9, 2), X = (m - v * v.transpose()).reshaped();
  T << A.reshaped(), B.reshaped();
  Vector2d c_s = T.bdcSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(X);
  double theta = std::acos(c_s[0]);

  return Quat{v, theta};
} 

void test(){
  Quat q{1,2,3,4};
  Quat p{5,6,7,8};
  Quat t({1,1,1}, 0);
  mat_to_quat(q.normalize().to_mat());
  mat_to_quat(p.normalize().to_mat());
  mat_to_quat(t.normalize().to_mat());
  // std::cout << q - p.conj() << std::endl;
  // std::cout << t << std::endl;
}

int main(){
  test();
  return 0;
}
