#include <iostream>
#include <utility>
#include <cstddef>
#include <vector>
#include <cstdarg>


template <class Type, std::size_t N>
class System
{
// Abbreviations:
//  STM - State Transfer Matrix

// Generate the typelist for all functions in STM

private:
  // Holds Rows of our STM
  std::vector<Type (*)(Type args)> v();

public:

  // Constructor
  System<Type,N>();

  // Sets Rows of our State Transfer Matrix
  void setFunction(int index, Type (*)(Type... args));

  //T rk4(T (*)(Types ... args), T h, Types ... args);
};

template<class Type, std::size_t N>
System<Type,N>::System()
{

}
//
// template<class Type, unsigned int N>
// void System<Type,N>::setFunction(int index, Type (* f)(Type...[N] args))
// {
//   this->v[index] = f;
// }

// template<class T, class ... Types>
// T System<T,Types...>::rk4( T (* f)(Types ... args), T h, Types ... args)
// {
//   T k1 = h * f(args);
//   T k2 = h *
//
// }

// template<typename T>
// T rk4t(T (* f)(T t, ...), T h, T t, ...)
// {
//   va_list args;
//   va_start(args, h);
//
//   T k1 = f(t + h/2, args);
// }

template<typename T>
T rk4(T (* y)(T t), T h, T y0)
{
  T k1 = y(y0);
  T y1 = y0 + k1*h/2;
  T k2 = y(y0);
  T y2 = y0 + k2*h/2;
  T k3 = y(y0);
  T y3 = y0 + k3*h;
  T k4 = y(y0);

  return y0 + (k1+2*k2+2*k3+k4)*h/6;
}

template<typename T>
void rk4vec(std::vector<T> & ystar, T (* y)(T), T y0, T h=0.2)
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
  ArgList<int, 2> a;
  std::cout << a.f(0);
  //std::vector<double> result(100, sizeof(double));
  //System<double, 2> sys;

  //auto lambda1 = [](double x, double y) -> double { return x + y; };
  // auto lambda2 = [](double x, double y) -> double { return x - y; };
  // sys.setFunction(0, lambda1);
  // sys.setFunction(1, lambda2);

  int n = 100;
  double h = 0.02;
  double t = 0;
  std::vector<double> result(100, sizeof(double));
  result[0] = 3;

  //rk4vec<double>(result, [](double a)->double { return -1/a; }, 3, 0.02);

  for( auto & v : result)
  {
    *(&v + 1) = rk4<double>( [](double a)->double { return -2*a; }, h, v);
  }

  for( auto & v : result)
  {
    std::cout << v << "\n";
  }
}
