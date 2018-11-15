#include <iostream>
#include "quaternion.hpp"

Quaternion<double> e(1,0,0,0);
Quaternion<double> i(0,1,0,0);
Quaternion<double> j(0,0,1,0);
Quaternion<double> k(0,0,0,1);

int main(int argc, char ** argv)
{
  double dtheta = 15;
  Quaternion<double> point(0, 1.0, 0.0, 0.0);
  Quaternion<double> q1(dtheta, Vector3<double>(1,1,1));

  std::cout << point << "\n";

  for(int i = 0; i < 360/15; ++i)
  {
    point = (q1 * point) * !q1;
    std::cout << ((q1 * point) * !q1) << "\n";
  }
  return 0;
}

void test1()
{
  Quaternion<double> q1(1, 2, 3, 4);
  Quaternion<double> q2(1,-1, 2,-4);
  Quaternion<double> q3 = q1;
  std::cout << "Q1 =    " << q1 << "\n";
  std::cout << "Q2 =    " << q2 << "\n";
  std::cout << "Q1+Q2 = " << q1 + q2 << "\n";
  std::cout << "Q1-Q2 = " << q1 - q2 << "\n";
  std::cout << "-Q3 =   " << -q3 << "\n";
  std::cout << "Q1*Q2 = " << q1 * q2 << "\n";
  std::cout << "!Q1 (conjugate) = " << !q1 << "\n";
  std::cout << "Q1/Q2 = " << q1/q2 << "\n";
  std::cout << "1/Q2 =   " << 1.0f/q2 << "\n";
  std::cout << "q1.mag()  = " << q1.mag() << "\n";
  std::cout << "q1.mag2() = " << q1.mag2() << "\n";
  std::cout << "(q1 += 1) += 1) = " << ((q1 += 1) += 1) << "\n";
}
