%module Quaternion

%include <std_string.i>

%ignore *::operator=;
%ignore operator=;
%ignore operator!;

%{
#include "../include/Quaternion.hpp"
%}

%include "../include/Quaternion.hpp";

%template(quatd) Quaternion<double>;

%rename(__add__) Quaternion<double>::operator+;

%template(quatf) Quaternion<float>;

%rename(__add__) Quaternion<float>::operator+;
