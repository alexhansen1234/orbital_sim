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


public:
  T rk4(T h, ith_T<Ignore>... values)
  {
    std::array<std::array<T, n>, 4> kvals;

    std::size_t equationIndex;

    equationIndex = 0;
    for( auto & k : kvals[0])
    {
      k = h * (this->rowVector)[equationIndex](values...);
      equationIndex += 1;
    }

    //  equationIndex = 0;
    //  for( auto & k : kvals[1])
    //  {
    //    k = h * (this->rowVector)[equationIndex](values... + kvals[0]);
    //    equationIndex += 1;
    // }



    return kvals[0][1];
  }

  System() {}

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
  auto lambda2 = [](double x, double y) { return x - y; };

  sys.setRow(0, lambda1);
  sys.setRow(1, lambda2);

  double one, two;

  std::cout << sys.rk4(0.2,1,2) << "\n";

  return 0;
}
