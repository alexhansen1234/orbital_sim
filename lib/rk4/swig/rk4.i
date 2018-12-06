%module rk4

%include <std_vector.i>
%include <std_array.i>

%{
  #include "rk4_swig.hpp"
%}

%include "rk4_swig.hpp";

%template(system) System<double,6>;
%template(doubleVector) std::vector<double>;
%template(doubleArray) std::array<double,6>;
%template(doubleVectorArray) std::vector<std::array<double,6>>;
