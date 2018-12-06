#ifndef RK4_HPP
#define RK4_HPP

#include <iostream>
#include <vector>
#include <array>
#include <tuple>

template <std::size_t index, typename T, std::size_t n, typename... Ts>
struct update_tuple
{
  void operator() (std::tuple<Ts...> & saveto, std::tuple<Ts...> & original, std::array<T,n> arr)
  {
    std::get<index>(saveto) = std::get<index>(original) + arr[index];
    update_tuple<index-1, T, n, Ts...>{}(saveto, original, arr);
  }
};

template <typename T, std::size_t n, typename... Ts>
struct update_tuple<0, T, n, Ts...>
{
  void operator() (std::tuple<Ts...> & saveto, std::tuple<Ts...> & original, std::array<T,n> arr)
  {
    std::get<0>(saveto) = std::get<0>(original) + arr[0];
  }
};

template <std::size_t index, typename T, std::size_t n, typename... Ts>
struct copy_tuple_to_array
{
  void operator() (std::tuple<Ts...> & from, std::array<T, n> & to)
  {
    to[index] = std::get<index>(from);
    copy_tuple_to_array<index-1, T, n, Ts...>{}(from, to);
  }
};

template <typename T, std::size_t n, typename... Ts>
struct copy_tuple_to_array<0, T, n, Ts...>
{
  void operator() (std::tuple<Ts...> & from, std::array<T, n> & to)
  {
    to[0] = std::get<0>(from);
  }
};

template <typename T, std::size_t n, typename = std::make_index_sequence<n>>
class System;

template <typename T, std::size_t n, std::size_t... Ignore>
class System<T, n, std::index_sequence<Ignore...>>
{
  template <size_t > using ith_T = T;

private:
  std::array<T (*)(ith_T<Ignore>...values), n> rowVector;

  template <std::size_t... Is>
  T call_func_with_tuple(T (* f)(ith_T<Ignore>... values), const std::tuple<ith_T<Ignore>...>& tuple, std::index_sequence<Is...>)
  {
    return f(std::get<Is>(tuple)...);
  }

  template <std::size_t... Is>
  auto call_func_with_tuple(System<T, n> & sys, const std::tuple<ith_T<Ignore>...>& tuple, T arg, std::index_sequence<Is...>)
  {
    return sys.rk4(arg, std::get<Is>(tuple)...);
  }

public:
  auto rk4(T h, ith_T<Ignore>... values)
  {
    std::array<std::array<T, n>, 4> kvals;
    std::array<T, n> sum_kvals;
    std::size_t equationIndex;

    std::tuple<ith_T<Ignore>...> original_params(values...);
    std::tuple<ith_T<Ignore>...> updated_params(values...);

    equationIndex = 0;
    for( auto & k : kvals[0])
    {
      k = 0.5 * h * (this->rowVector)[equationIndex](values...);
      equationIndex += 1;
    }

    update_tuple<n-1, T, n, ith_T<Ignore>...>{}(updated_params, original_params, kvals[0]);

    equationIndex = 0;
    for( auto & k : kvals[1])
    {
      k = 0.5 * h * this->call_func_with_tuple( this->rowVector[equationIndex], updated_params, std::index_sequence_for<ith_T<Ignore>...>());
      equationIndex += 1;
    }

    update_tuple<n-1, T, n, ith_T<Ignore>...>{}(updated_params, original_params, kvals[1]);

    equationIndex = 0;
    for( auto & k : kvals[2])
    {
      k = h * this->call_func_with_tuple( this->rowVector[equationIndex], updated_params, std::index_sequence_for<ith_T<Ignore>...>());
      equationIndex += 1;
    }

    update_tuple<n-1, T, n, ith_T<Ignore>...>{}(updated_params, original_params, kvals[2]);

    equationIndex = 0;
    for( auto & k : kvals[3])
    {
      k = h * this->call_func_with_tuple( this->rowVector[equationIndex], updated_params, std::index_sequence_for<ith_T<Ignore>...>());
      equationIndex += 1;
    }

    // Update

    for( int i=0; i < n; ++i)
    {
      sum_kvals[i] = (2*kvals[0][i] + 4*kvals[1][i] + 2*kvals[2][i] + kvals[3][i])/6;
    }

    update_tuple<n-1, T, n, ith_T<Ignore>...>{}(original_params, original_params, sum_kvals);

    return original_params;
  }

  std::vector<std::array<T,n>> rk4range(T h, T ti, T tf, ith_T<Ignore> ... values)
  {
    std::vector<std::array<T,n>> res( std::size_t( abs( int((tf - ti)/h) ) ) );

    std::tuple<ith_T<Ignore>...> res_tuple(values...);

    copy_tuple_to_array<n-1, T, n, ith_T<Ignore>...>{}( res_tuple, res[0] );

    for(std::size_t i = 1; ti < tf; ti += h)
    {
      //res_tuple = this->rk4(h, std::get< std::make_index_sequence<n> >(res_tuple));
      res_tuple = this->call_func_with_tuple( *this, res_tuple, h, std::index_sequence_for<ith_T<Ignore>...>());
      copy_tuple_to_array<n-1, T, n, ith_T<Ignore>...>{}( res_tuple, res[i] );
      i += 1;
    }

    return res;
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
#endif /* RK4_HPP */
