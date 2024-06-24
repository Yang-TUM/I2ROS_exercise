// Copyright 2021 TU Munich, Introduction To ROS, Markus Ryll

#include "calculator.h"

class MyMath {
 private:
  const double kPi = 3.14156;

 public:
  double Sum_(double a, double b) {
        return a + b;
    }

  double Square_(double a) {
        return a * a;
    }

  /* Add here the following functions:
  	* subtration
  	* division
  	* overloaded function to sum_ that sums a vector
    * surface of circle
    * circumference of circle
    * Vector product (3 * 3)
    * Matrix multiplication (2 x 2)
    * sin(a)
  */
};

int main() {
  MyMath math_;

  // Implement Input

  std::cout << "Sum is =  " << math_.Sum_(1.0, 1.0) << std::endl;

  return 0;
}
