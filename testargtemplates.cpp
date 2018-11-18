#include <iostream>
#include <vector>
#include <array>
#include <tuple>

template <typename T, std::size_t n, typename = std::make_index_sequence<n>>
class System;

template <typename T, std::size_t n, std::size_t... Ignore>
class System<T, n, std::index_sequence<Ignore...>>
{
    template <size_t > using ith_T = T;

private:
  std::array<T (*)(ith_T<Ignore>... values), n> rowVector;

  template <std::size_t... Is>
  T call_func_with_tuple(T (* f)(ith_T<Ignore>... values), const std::tuple<ith_T<Ignore>...>& tuple, std::index_sequence<Is...>)
  {
    return f(std::get<Is>(tuple)...);
  }

public:

  T rk4(T h, ith_T<Ignore>... values)
  {
    std::array<std::array<T, n>, 4> kvals;

    std::size_t equationIndex;

    std::tuple<ith_T<Ignore>...> original_params(values...);
    std::tuple<ith_T<Ignore>...> updated_params(values...);

    equationIndex = 0;
    for( auto & k : kvals[0])
    {
      k = h * (this->rowVector)[equationIndex](values...);
      equationIndex += 1;
    }

    std::get<0>(updated_params) = std::get<0>(original_params) + 0.5*kvals[0][0];
    std::get<1>(updated_params) = std::get<1>(original_params) + 0.5*kvals[0][1];

    equationIndex = 0;
    for( auto & k : kvals[1])
    {
      k = h * this->call_func_with_tuple( this->rowVector[equationIndex], updated_params, std::index_sequence_for<ith_T<Ignore>...>());
      equationIndex += 1;
    }

    std::get<0>(updated_params) = std::get<0>(original_params) + 0.5*kvals[1][0];
    std::get<1>(updated_params) = std::get<1>(original_params) + 0.5*kvals[1][1];

    equationIndex = 0;
    for( auto & k : kvals[2])
    {
      k = h * this->call_func_with_tuple( this->rowVector[equationIndex], updated_params, std::index_sequence_for<ith_T<Ignore>...>());
      equationIndex += 1;
    }

    std::get<0>(updated_params) = std::get<0>(original_params) + kvals[2][0];
    std::get<1>(updated_params) = std::get<1>(original_params) + kvals[2][1];

    equationIndex = 0;
    for( auto & k : kvals[3])
    {
      k = h * this->call_func_with_tuple( this->rowVector[equationIndex], updated_params, std::index_sequence_for<ith_T<Ignore>...>());
      equationIndex += 1;
    }

    std::cout << "k1 = " << kvals[0][0] << "\n";
    std::cout << "k2 = " << kvals[1][0] << "\n";
    std::cout << "k3 = " << kvals[2][0] << "\n";
    std::cout << "k4 = " << kvals[3][0] << "\n";

    std::cout << "l1 = " << kvals[0][1] << "\n";
    std::cout << "l2 = " << kvals[1][1] << "\n";
    std::cout << "l3 = " << kvals[2][1] << "\n";
    std::cout << "l4 = " << kvals[3][1] << "\n";


    std::cout << std::get<0>(original_params) + (kvals[0][0] + 2*kvals[1][0] + 2*kvals[2][0] + kvals[3][0])/6 << "\n";
    std::cout << std::get<1>(original_params) + (kvals[0][1] + 2*kvals[1][1] + 2*kvals[2][1] + kvals[3][1])/6 << "\n";

    //return std::get<0>(original_params) + (kvals[0][0] + 2*kvals[1][0] + 2*kvals[2][0] + kvals[3][0])/6;
    return std::get<1>(original_params) + (kvals[0][1] + 2*kvals[1][1] + 2*kvals[2][1] + kvals[3][1])/6;
  }

  // Class Constructor
  System() {}

  // Set equations for the derivative of the ith variable
  void setRow (std::size_t Index, T (* f)(ith_T<Ignore>... values))
  {
    if(Index < n)
    {
      rowVector[Index] = f;
    }
  }

};

int main(int argc, char ** argv)
{
  System<double, 2> sys;

  auto lambda1 = [](double x, double y) { return x + y; };
  auto lambda2 = [](double x, double y) { return -2*x - y; };

  sys.setRow(0, lambda1);
  sys.setRow(1, lambda2);


  sys.rk4(0.2,1,2);
  sys.rk4(0.2,1.57607,1.16547);
  sys.rk4(0.2,2.08931,0.284473);
  return 0;
}
