#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include <cmath>
#include <sstream>
#include <ostream>

#include "Vector3.hpp"

template<class T>
class Quaternion
{
private:

public:
  T w,x,y,z;

  Quaternion<T>();
  Quaternion<T>(const T w, const T x, const T y, const T z);
  Quaternion<T>(const Quaternion<T> & q);
  Quaternion<T>(const T & theta, const Vector3<T> & axis);

  Quaternion<T> vector();
  Quaternion<T> scalar();

  T mag2 ();
  T mag  ();

  // Returns a rotation vector which rotates a quaternion thetad degrees
  // about an axis defined by the vector (axisx, axisy, axisz)
  static Quaternion<T> rotation(const T & thetad, const T & axisx, const T & axisy, const T & axisz);

  // Negation
  Quaternion<T> operator - ();

  // Conjugation
  Quaternion<T> operator ~ ();

  Quaternion<T> & operator = (const Quaternion<T>&);
  Quaternion<T> & operator = (const int&);
  Quaternion<T> & operator = (const float&);
  Quaternion<T> & operator = (const double&);

  Quaternion<T> operator +  (const Quaternion<T>&);
  Quaternion<T> operator +  (const int&);
  Quaternion<T> operator +  (const float&);
  Quaternion<T> operator +  (const double&);

  template<typename U>
  friend Quaternion<U> operator + (const int &, const Quaternion<U> &);
  template<typename U>
  friend Quaternion<U> operator + (const float &, const Quaternion<U> &);
  template<typename U>
  friend Quaternion<U> operator + (const double &, const Quaternion<U> &);


  Quaternion<T> & operator += (const Quaternion<T>&);
  Quaternion<T> & operator += (const int&);
  Quaternion<T> & operator += (const float&);
  Quaternion<T> & operator += (const double&);

  Quaternion<T> operator -  (const Quaternion<T>&);
  Quaternion<T> operator -  (const int&);
  Quaternion<T> operator -  (const float&);
  Quaternion<T> operator -  (const double&);

  template<typename U>
  friend Quaternion<U> operator - (const int &, const Quaternion<U> &);
  template<typename U>
  friend Quaternion<U> operator - (const float &, const Quaternion<U> &);
  template<typename U>
  friend Quaternion<U> operator - (const double &, const Quaternion<U> &);


  Quaternion<T> & operator -= (const Quaternion<T>&);
  Quaternion<T> & operator -= (const int&);
  Quaternion<T> & operator -= (const float&);
  Quaternion<T> & operator -= (const double&);

  Quaternion<T> operator /  (const Quaternion<T>&);
  Quaternion<T> operator /  (const int&);
  Quaternion<T> operator /  (const float&);
  Quaternion<T> operator /  (const double&);

  template<typename U>
  friend Quaternion<U> operator / (const int &, const Quaternion<U> &);
  template<typename U>
  friend Quaternion<U> operator / (const float &, const Quaternion<U> &);
  template<typename U>
  friend Quaternion<U> operator / (const double &, const Quaternion<U> &);

  Quaternion<T> & operator /= (const Quaternion<T>&);
  Quaternion<T> & operator /= (const int&);
  Quaternion<T> & operator /= (const float&);
  Quaternion<T> & operator /= (const double&);

  Quaternion<T> operator *  (const Quaternion<T>&);
  Quaternion<T> operator *  (const int&);
  Quaternion<T> operator *  (const float&);
  Quaternion<T> operator *  (const double&);

  template<typename U>
  friend Quaternion<U> operator * (const int &, const Quaternion<U> &);
  template<typename U>
  friend Quaternion<U> operator * (const float &, const Quaternion<U> &);
  template<typename U>
  friend Quaternion<U> operator * (const double &, const Quaternion<U> &);


  Quaternion<T> & operator *= (const Quaternion<T>&);
  Quaternion<T> & operator *= (const int&);
  Quaternion<T> & operator *= (const float&);
  Quaternion<T> & operator *= (const double&);

  // This is for printing in Python using SWIG
  std::string __repr__ () const
  {
    std::ostringstream out;
    out << "( " << this->w << " , " << this->x << " , " << this->y << " , " << this->z << " )";
    return out.str();
  }

  template<typename U>
  friend std::ostream& operator<<(std::ostream &out, const Quaternion<U>& c);
};

template<class T>
Quaternion<T>::Quaternion()
{
  w = 0;
  x = 0;
  y = 0;
  z = 0;
}

template<class T>
Quaternion<T>::Quaternion(const T w1, const T x1, const T y1, const T z1)
{
  w = w1;
  x = x1;
  y = y1;
  z = z1;
}

template<class T>
Quaternion<T>::Quaternion(const T & thetad, const Vector3<T> & axis)
{
  T theta = thetad * acos(-1) / 360.0;
  T mag = sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
  Vector3<T> unit = Vector3<T>(axis.x / mag, axis.y / mag, axis.z / mag);
  w = cos(theta);
  x = unit.x * sin(theta);
  y = unit.y * sin(theta);
  z = unit.z * sin(theta);
}

template<class T>
Quaternion<T>::Quaternion(const Quaternion<T> & q)
{
  w = q.w;
  x = q.x;
  y = q.y;
  z = q.z;
}

template<class T>
Quaternion<T> Quaternion<T>::rotation(const T & thetad, const T & axisx, const T & axisy, const T & axisz)
{
  T theta = thetad * acos(-1) / 360.0;
  T mag = sqrt(axisx * axisx + axisy * axisy + axisz * axisz);
  return Quaternion<T>( cos( theta ),
                        axisx / mag * sin(theta),
                        axisy / mag * sin(theta),
                        axisz / mag * sin(theta) );
}

template<class T>
Quaternion<T> Quaternion<T>::scalar ()
{
  return Quaternion<T>(this->w, 0, 0, 0);
}

template<class T>
Quaternion<T> Quaternion<T>::vector ()
{
  return Quaternion<T>(0, this->x, this->y, this->z);
}

template<class T>
Quaternion<T> & Quaternion<T>::operator = (const Quaternion<T> &q)
{
  w = q.w;
  x = q.x;
  y = q.y;
  z = q.z;
  return * this;
}

template<class T>
Quaternion<T> Quaternion<T>::operator + (const Quaternion<T>& q)
{
  return Quaternion<T>(this->w + q.w, this->x + q.x, this->y + q.y, this->z + q.z);
}

template<class T>
Quaternion<T> Quaternion<T>::operator + (const int& q)
{
    return Quaternion<T>(this->w + q, this->x, this->y, this->z);
}

template<class T>
Quaternion<T> Quaternion<T>::operator + (const float& q)
{
    return Quaternion<T>(this->w + q, this->x, this->y, this->z);
}

template<class T>
Quaternion<T> Quaternion<T>::operator + (const double& q)
{
    return Quaternion<T>(this->w + q, this->x, this->y, this->z);
}

template<class T>
Quaternion<T> operator + (const int & lhs, const Quaternion<T>& rhs)
{
  return Quaternion<T>(lhs + rhs.w, rhs.x, rhs.y, rhs.z);
}

template<class T>
Quaternion<T> operator + (const float & lhs, const Quaternion<T>& rhs)
{
  return Quaternion<T>(lhs + rhs.w, rhs.x, rhs.y, rhs.z);
}

template<class T>
Quaternion<T> operator + (const double & lhs, const Quaternion<T>& rhs)
{
  return Quaternion<T>(lhs + rhs.w, rhs.x, rhs.y, rhs.z);
}

template<class T>
Quaternion<T> & Quaternion<T>::operator += (const int& q)
{
  this->w = this->w + q;
  return *this;
}

template<class T>
Quaternion<T> & Quaternion<T>::operator += (const float& q)
{
  this->w = this->w + q;
  return *this;
}

template<class T>
Quaternion<T> & Quaternion<T>::operator += (const double& q)
{
  this->w = this->w + q;
  return *this;
}

template<class T>
Quaternion<T> & Quaternion<T>::operator += (const Quaternion<T>& q)
{
  this->w += q.w;
  this->x += q.x;
  this->y += q.y;
  this->z += q.z;
  return *this;
}

template<class T>
Quaternion<T> Quaternion<T>::operator - ()
{
    return Quaternion<T>(-this->w, -this->x, -this->y, -this->z);
}

template<class T>
Quaternion<T> Quaternion<T>::operator - (const Quaternion<T> & q)
{
    return Quaternion<T>(this->w - q.w, this->x - q.x, this->y - q.y, this->z - q.z);
}

template<class T>
Quaternion<T> Quaternion<T>::operator - (const int & q)
{
    return Quaternion<T>(this->w - q, this->x, this->y, this->z);
}

template<class T>
Quaternion<T> Quaternion<T>::operator - (const float & q)
{
    return Quaternion<T>(this->w - q, this->x, this->y, this->z);
}

template<class T>
Quaternion<T> Quaternion<T>::operator - (const double & q)
{
    return Quaternion<T>(this->w - q, this->x, this->y, this->z);
}

template<class T>
Quaternion<T> operator - (const int & lhs, const Quaternion<T>& rhs)
{
  return Quaternion<T>(lhs + rhs.w, rhs.x, rhs.y, rhs.z);
}

template<class T>
Quaternion<T> operator - (const float & lhs, const Quaternion<T>& rhs)
{
  return Quaternion<T>(lhs + rhs.w, rhs.x, rhs.y, rhs.z);
}

template<class T>
Quaternion<T> operator - (const double & lhs, const Quaternion<T>& rhs)
{
  return Quaternion<T>(lhs + rhs.w, rhs.x, rhs.y, rhs.z);
}

template<class T>
Quaternion<T> & Quaternion<T>::operator -= (const Quaternion<T>& q)
{
  this->w -= q.w;
  this->x -= q.x;
  this->y -= q.y;
  this->z -= q.z;
  return *this;
}

template<class T>
Quaternion<T> & Quaternion<T>::operator -= (const int& q)
{
  this->w -= q;
  return *this;
}

template<class T>
Quaternion<T> & Quaternion<T>::operator -= (const float& q)
{
  this->w -= q;
  return *this;
}

template<class T>
Quaternion<T> & Quaternion<T>::operator -= (const double& q)
{
  this->w -= q;
  return *this;
}

template<typename T>
Quaternion<T> Quaternion<T>::operator ~ ()
{
    return Quaternion<T>(this->w, -this->x, -this->y, -this->z);
}

template<typename T>
Quaternion<T> Quaternion<T>::operator * (const Quaternion<T>& q)
{
    return Quaternion<T>
    (
        this->w * q.w - this->x * q.x - this->y * q.y - this->z * q.z,
        this->y * q.z - this->z * q.y + this->w * q.x + this->x * q.w,
        this->z * q.x - this->x * q.z + this->w * q.y + this->y * q.w,
        this->x * q.y - this->y * q.x + this->w * q.z + this->z * q.w
    );
}

template<class T>
Quaternion<T> Quaternion<T>::operator * (const int & q)
{
  return Quaternion<T>(this->w * q, this->x * q, this->y * q, this->z * q);
}

template<class T>
Quaternion<T> Quaternion<T>::operator * (const float & q)
{
  return Quaternion<T>(this->w * q, this->x * q, this->y * q, this->z * q);
}

template<class T>
Quaternion<T> Quaternion<T>::operator * (const double & q)
{
  return Quaternion<T>(this->w * q, this->x * q, this->y * q, this->z * q);
}

template<class T>
Quaternion<T> & Quaternion<T>::operator *= (const Quaternion<T>& q)
{
  *this = *this * q;
  return *this;
}

template<class T>
Quaternion<T> & Quaternion<T>::operator *= (const int& q)
{
  this->w *= q;
  this->x *= q;
  this->y *= q;
  this->z *= q;
  return *this;
}

template<class T>
Quaternion<T> & Quaternion<T>::operator *= (const float& q)
{
  this->w *= q;
  this->x *= q;
  this->y *= q;
  this->z *= q;
  return *this;
}

template<class T>
Quaternion<T> & Quaternion<T>::operator *= (const double& q)
{
  this->w *= q;
  this->x *= q;
  this->y *= q;
  this->z *= q;
  return *this;
}


template<typename T>
Quaternion<T> operator / (const int & lhs, const Quaternion<T> & rhs)
{
  return Quaternion<T>(lhs, 0, 0, 0) / rhs;
}

template<typename T>
Quaternion<T> operator / (const float & lhs, const Quaternion<T> & rhs)
{
  return Quaternion<T>(lhs, 0, 0, 0) / rhs;
}


template<typename T>
Quaternion<T> operator / (const double & lhs, const Quaternion<T> & rhs)
{
  return Quaternion<T>(lhs, 0, 0, 0) / rhs;
}

template<typename T>
Quaternion<T> Quaternion<T>::operator / (const int & q)
{
  return Quaternion<T>(this->w / q, this->x / q, this->y / q, this->z /q);
}

template<typename T>
Quaternion<T> Quaternion<T>::operator / (const float & q)
{
  return Quaternion<T>(this->w / q, this->x / q, this->y / q, this->z /q);
}

template<typename T>
Quaternion<T> Quaternion<T>::operator / (const double & q)
{
  return Quaternion<T>(this->w / q, this->x / q, this->y / q, this->z /q);
}

template<typename T>
Quaternion<T> Quaternion<T>::operator / (const Quaternion<T>& rhs)
{
  T mag2 = rhs.w*rhs.w + rhs.x*rhs.x + rhs.y*rhs.y + rhs.z*rhs.z;
  return *this * Quaternion<T>(rhs.w, -rhs.x, -rhs.y, -rhs.z) / mag2;
}

template<typename T>
Quaternion<T> & Quaternion<T>::operator /= (const Quaternion<T>& rhs)
{
  *this = *this / rhs;
  return * this;
}

template<typename T>
Quaternion<T> & Quaternion<T>::operator /= (const int& rhs)
{
  *this = *this / rhs;
  return * this;
}

template<typename T>
Quaternion<T> & Quaternion<T>::operator /= (const float& rhs)
{
  *this = *this / rhs;
  return * this;
}

template<typename T>
Quaternion<T> & Quaternion<T>::operator /= (const double& rhs)
{
  *this = *this / rhs;
  return * this;
}

template<typename T>
std::ostream& operator<<(std::ostream &out, const Quaternion<T>& c)
{
     out << "( " << c.w << " , " << c.x << " , " << c.y << " , " << c.z << " )";
     return out;
}

template<typename T>
T Quaternion<T>::mag()
{
  return sqrt(this->mag2());
}

template<typename T>
T Quaternion<T>::mag2()
{
    return this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w;
}
#endif
