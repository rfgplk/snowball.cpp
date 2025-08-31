#include "../include/snowball.hpp"

unsigned int
factorial(unsigned int number)
{
  return number <= 1 ? number : factorial(number - 1) * number;
}

int
main(void)
{
  sb::test_case("Factorial test case");
  sb::require(&factorial, 1, 1);
  sb::require(&factorial, 2, 2);
  sb::require(&factorial, 6, 3);
  sb::require(&factorial, 3628800, 10);
  // causes error
  sb::require(&factorial, 1, 0);
}
