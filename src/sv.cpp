#include "Quaternion.hpp"
#include "rk4_swig.hpp"
#include "sv_swig.hpp"
using quatd = Quaternion<double>;

extern System<double, 6> sys;

int Satellite::id_counter = 0;

Satellite::Satellite(quatd position0, quatd velocity0)
{
  id = Satellite::id_counter;
  Satellite::id_counter += 1;
  position = position0;
  velocity = velocity0;
}

int Satellite::get_id(void)
{
  return this->id;
}

void Satellite::time_step(double delta_t)
{
  auto s = iterate(delta_t, position.x, velocity.x, position.y, velocity.y, position.z, velocity.z);
  this->position = quatd(0, s[0], s[2], s[4]);
  this->velocity = quatd(0, s[1], s[3], s[5]);
}

quatd Satellite::get_position(void)
{
  return this->position;
}

quatd Satellite::get_velocity(void)
{
  return this->velocity;
}

void Satellite::set_position(quatd position)
{
  this->position = position;
}

void Satellite::set_velocity(quatd velocity)
{
  this->velocity = velocity;
}
