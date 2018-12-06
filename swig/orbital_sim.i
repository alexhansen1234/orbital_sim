%module orbital_sim

%include "Quaternion.i"
%include "rk4.i"

%{
  #include "sv_swig.hpp"
%}

%include "sv_swig.hpp";
