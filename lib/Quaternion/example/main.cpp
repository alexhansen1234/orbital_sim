#include <iostream>
#include "Quaternion.hpp"

void test1();

int main(int argc, char ** argv)
{
  double dtheta = 15;
  Quaternion<double> point(0, 8000.0, 0.0, 0.0);
  Quaternion<double> q1(dtheta, Vector3<double>(0, 1, 0));

  int i = 0;
  std::cout << point << "\n";

  for(i = 1; i <= 360/dtheta; ++i)
  {
    point = (q1 * point) * ~q1;
    std::cout << (q1 * point) * ~q1 << "\n";
  }

  point = Quaternion<double>(0, 8000.0, 0.0, 0.0);
  q1 = Quaternion<double>(dtheta, Vector3<double>(0, 0, 1));

  i = 0;
  std::cout << point << "\n";

  for(i = 1; i <= 360/dtheta; ++i)
  {
    point = (q1 * point) * ~q1;
    std::cout << point << "\n";
  }

  point = Quaternion<double>(0, 0.0, 8000.0, 0.0);
  q1 = Quaternion<double>(dtheta, Vector3<double>(1, 0, 0));

  i = 0;
  std::cout << point << "\n";

  for(i = 1; i <= 360/dtheta; ++i)
  {
    point = (q1 * point) * ~q1;
    std::cout << point << "\n";
  }

  test1();

  return 0;
}

void test1()
{
  Quaternion<double> q1(1, 2, 3, 4);
  Quaternion<double> q2(1,-1, 2,-4);
  Quaternion<double> q3 = q1;
  Quaternion<float> q4(1,2,3,4);
  Quaternion<double> q5 = Quaternion<double>::rotation(180, 0, 1, 0);
  Quaternion<double> q6 = Quaternion<double>(q5);
  double scale = 2;
  std::cout << "Q1 =    " << q1 << "\n";
  std::cout << "Q2 =    " << q2 << "\n";
  std::cout << "Q1+Q2 = " << q1 + q2 << "\n";
  std::cout << "Q1-Q2 = " << q1 - q2 << "\n";
  std::cout << "-Q3 =   " << -q3 << "\n";
  std::cout << "Q1*Q2 = " << q1 * q2 << "\n";
  std::cout << "~Q1 (conjugate) = " << ~q1 << "\n";
  std::cout << "Q1/Q2 = " << q1/q2 << "\n";
  std::cout << "1/Q2 =   " << 1.0f/q2 << "\n";
  std::cout << "q1.mag()  = " << q1.mag() << "\n";
  std::cout << "q1.mag2() = " << q1.mag2() << "\n";
  std::cout << "(q1 += 1) += 1) = " << ((q1 += 1) += 1) << "\n";
  q3 = q2 = q1;
  q3 -= (q1*q2);
  q3 *= (q1 *= q2);
  q3 *= 4;
  q3 /= 4;
  q3 /= q1;
  q3 /= 1.2f;
  q3 *= (1.2f + q1);
  q3 /= (1.234232f - q2.mag() - 2.32342/~q1);
  q4 *= scale;
  q1 = Quaternion<double>(1,2,3,4);
  std::cout << q1*q1 << "\n";
  std::cout << q4 << "\n";
  std::cout << (q3 + q2 * (q1 += q2)) << "\n";
  std::cout << q5 * q6 * ~q5 << "\n";
}
