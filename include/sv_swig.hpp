#ifndef SV_HPP
#define SV_HPP

#include "Quaternion.hpp"

const double G = 6.67408e-11;
const double M = 5.972e24;

class Satellite
{
private:
  static int id_counter;
  int id;
  Quaternion<double> position;
  Quaternion<double> velocity;
public:
  Satellite(Quaternion<double>, Quaternion<double>);
  void time_step(double);
  Quaternion<double> get_position(void);
  Quaternion<double> get_velocity(void);
  int get_id(void);
  void set_position(Quaternion<double>);
  void set_velocity(Quaternion<double>);
};

#endif /* SV_HPP */
