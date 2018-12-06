#include "rk4.hpp"
#include <cmath>
// Gravitational Constant [ m^3 kg^-1 s^2]
const double G = 6.67408e-11;

// Mass of earth [kg]
const double m1 = 5.972e24;

auto lambda1 = [](double x, double dx, double y, double dy, double z, double dz) -> double
{
  return dx;
};

auto lambda2 = [](double x, double dx, double y, double dy, double z, double dz) -> double
{
  return -G*m1*x/(x*x+y*y+z*z)/sqrt(x*x+y*y+z*z);
};

auto lambda3 = [](double x, double dx, double y, double dy, double z, double dz) -> double
{
  return dy;
};

auto lambda4 = [](double x, double dx, double y, double dy, double z, double dz) -> double
{
  return -G*m1*y/(x*x+y*y+z*z)/sqrt(x*x+y*y+z*z);
};

auto lambda5 = [](double x, double dx, double y, double dy, double z, double dz) -> double
{
  return dz;
};

auto lambda6 = [](double x, double dx, double y, double dy, double z, double dz) -> double
{
  return -G*m1*z/(x*x+y*y+z*z)/sqrt(x*x+y*y+z*z);
};

System<double, 6> sys;

void sys_init()
{
  sys.setRow(0, lambda1);
  sys.setRow(1, lambda2);
  sys.setRow(2, lambda3);
  sys.setRow(3, lambda4);
  sys.setRow(4, lambda5);
  sys.setRow(5, lambda6);
}

std::vector<double> iterate(double h, double x, double dx, double y, double dy, double z, double dz)
{
  std::vector<double> res(6);
  auto s = sys.rk4(h, x, dx, y, dy, z, dz);
  std::tie(res[0], res[1], res[2], res[3], res[4], res[5]) = s;
  return res;
}

std::vector<std::array<double, 6>> iterate_range(double h, double ti, double tf, double x, double dx, double y, double dy, double z, double dz)
{
  auto res = sys.rk4range(h, ti, tf, x, dx, y, dy, z, dz);
  return res;
}
