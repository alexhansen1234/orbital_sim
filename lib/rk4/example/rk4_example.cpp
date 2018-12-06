#include "rk4.hpp"

typedef double systype;

int main(int argc, char ** argv)
{
  System<systype, 4> sys;

  auto lambda1 = [](systype x, systype y, systype z, systype w) { return -0.5*x + 0.5*y - 0.5*z + 0.5*w; };
  auto lambda2 = [](systype x, systype y, systype z, systype w) { return  0.5*x - 0.5*y + 0.5*z + 0.5*w; };
  auto lambda3 = [](systype x, systype y, systype z, systype w) { return -0.5*x + 0.5*y - 0.5*z + 0.5*w; };
  auto lambda4 = [](systype x, systype y, systype z, systype w) { return  0.5*x - 0.5*y + 0.5*z - 0.5*w; };

  sys.setRow(0, lambda1);
  sys.setRow(1, lambda2);
  sys.setRow(2, lambda3);
  sys.setRow(3, lambda4);

  auto v = sys.rk4range(0.02, 0, 100000, 1, 2, 3, 4);

   // for(auto r : v)
   // {
   //   for(auto s : r)
   //     std::cout << s << " ";
   //   std::cout << "\n";
   // }
   for(auto r : *v.rbegin())
    std::cout << r << " ";
   std::cout << "\n";

  // volatile systype ti=0, tf=1000, dt=0.02;
  // volatile systype x0 = 1, y0 = 2, z0 = 3, w0 = 4;
  //
  // auto s = sys.rk4(dt, x0, y0, z0, w0);
  // int i=1;
  //
  // for(systype t = ti; t < tf; t += dt)
  // {
  //
  //   std::tie(x0, y0, z0, w0) = s;
  //
  //   std::cout << i << ". ";
  //   std::cout << "(" << x0 << ",";
  //   std::cout << y0 << ",";
  //   std::cout << z0 << ",";
  //   std::cout << w0 << ")\n";
  //
  //   s = sys.rk4(dt,x0,y0,z0,w0);
  //
  //   i += 1;
  // }

  // Example of a non-linear system
  //
  // System<systype, 3> sys;
  // auto lambda1 = [](systype x, systype y, systype z) { return 3*x + y; };
  // auto lambda2 = [](systype x, systype y, systype z) { return y - x + y*y*y*y + z*z*z*z; };
  // auto lambda3 = [](systype x, systype y, systype z) { return y + z*z*z*z + 3 + y*y*y*y; };
  //
  //
  // sys.setRow(0, lambda1);
  // sys.setRow(1, lambda2);
  // sys.setRow(2, lambda3);
  //
  // systype ti=0, tf=1, dt=0.0001;
  // systype x0 = 0, y0 = 1, z0 = 1;
  //
  // auto s = sys.rk4(dt, x0, y0, z0);
  // int i=1;
  //
  // std::cout << "0. t = " << ti << " ";
  // std::cout << "(" << x0 << ",";
  // std::cout << y0 << ",";
  // std::cout << z0 << ")\n";
  //
  // for(systype t = ti; t < tf; t += dt)
  // {
  //   x0 = std::get<0>(s);
  //   y0 = std::get<1>(s);
  //   z0 = std::get<2>(s);
  //
  //   std::cout << i << ". " <<  t + dt << " ";
  //   std::cout << "(" << x0 << ",";
  //   std::cout << y0 << ",";
  //   std::cout << z0 << ")\n";
  //
  //   s = sys.rk4(dt,x0,y0,z0);
  //
  //   i += 1;
  // }
  return 0;
}
