#include "../include/snowball.hpp"

#include <iostream>

void
print(int number)
{
  std::cout << number  << std::endl;
}

int
main(void)
{
  sb::fuzz(print, 1000);
}
