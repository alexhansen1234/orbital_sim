#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <string>
#include <ostream>

template<class T>
class Vector3
{
public:
  T x,y,z;

  Vector3<T>();
  Vector3<T>(const T x1, const T y1, const T z1);

  T mag();
  T mag2();
  Vector3<T> unit();

  template<typename U>
  friend std::ostream& operator<<(std::ostream &out, const Vector3<U>& v);
};

template<typename T>
std::ostream& operator<<(std::ostream &out, const Vector3<T>& v)
{
     out << "(" << v.x << "," << v.y << "," << v.z << ")";
     return out;
}

template<typename T>
Vector3<T>::Vector3()
{
  x = 0;
  y = 0;
  z = 0;
}

template<typename T>
Vector3<T>::Vector3(const T x1, const T y1, const T z1)
{
  x = x1;
  y = y1;
  z = z1;
}

template<typename T>
T Vector3<T>::mag2()
{
  return this->x * this->x + this->y * this->y + this->z * this->z;
}

template<typename T>
T Vector3<T>::mag()
{
  return sqrt( this->mag2() );
}

template<typename T>
Vector3<T> Vector3<T>::unit()
{
  T m = this->mag();
  return Vector3<T>(this->x / m, this->y / m, this->z / m);
}
#endif
