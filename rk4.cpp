#include <iostream>
#include <vector>

template<typename T>
T rk4(T (* y)(T t), T y0, T h=0.2)
{
  T k1 = y(y0);
  T y1 = y0 + k1*h/2;
  T k2 = y(y1);
  T y2 = y0 + k2*h/2;
  T k3 = y(y2);
  T y3 = y0 + k3*h;
  T k4 = y(y3);
  return y0 + (k1+2*k2+2*k3+k4)*h/6;
}

template<typename T>
void rk4vec(std::vector<T> & ystar, T (* y)(T t), T y0, T h=0.2)
{
  ystar[0] = y0;

  T y1, k1, y2, k2, y3, k3, k4;

  for(int i=0; i < ystar.size()-1; ++i)
  {
    k1 = y(ystar[i]);
    y1 = ystar[i] + k1*h/2;

    k2 = y(y1);
    y2 = ystar[i] + k2*h/2;

    k3 = y(y2);
    y3 = ystar[i] + k3*h;

    k4 = y(y3);

    ystar[i+1] = ystar[i] + (k1+2*k2+2*k3+k4)*h/6;
  }
}

int main(int argc, char ** argv)
{
  std::vector<double> result(100, sizeof(double));
  rk4vec<double>(result, [](double a)->double { return -2*a; }, 3, 0.02);

  for( auto v:result)
  {
    std::cout << v << "\n";
  }
}
