<div align="center">
  <img src="https://github.com/user-attachments/assets/a86cc00a-3f86-413c-b137-67560c49d668" alt="snowball_logo_384" width="300"/>
  
# bbench
### a single header, effective, C++20 unit testing framework
</div>

snowball is a *miniscule* and **highly intuitive** unit library, written in C++20. 


The goal of this library is to massively simplify unit testing while offering efficient and often seamless compilation speeds, all without sacrificing the full functionality expected from other frameworks. The library is delivered as a minimal, header-only file, ensuring it works identically on any platform where a c++ compiler and stl are available. all functions invoked through this library are written entirely in strictly standard-compliant c++, avoiding any preprocessor dependencies, resulting in a clean, lean, and portable testing solution.


To compile the examples from source run `ninja` or `ninja {example name}`, such as `ninja snowball_example_fac`. 


snowball is a platform agnostic library, as such the code will work on any operating system.

## General Usage
```cpp
// Primary functions
       void  snowball::verify_debug    (void);
string_type  snowball::test_case       (const T&    str);
string_type  snowball::test_case       (const char* ptr);
       void  snowball::end_test_case   (void);
       void  snowball::require         (bool (*fn)(Args...), Args &&...);
       void  snowball::require         (const bool);
       void  snowball::require         (Fn &&, const T& expectation, const Args&... inputs);
       void  snowball::require         (object&, Fn&&, const T& input, const T_& expectation, Fn_g&& (getter));
       void  snowball::require         (object&, Fn&&, const T& input, const T_& expectation);
       void  snowball::require_false   (object&, Fn&&, const T& input, const T_& expectation, Fn_g&& (getter));
       void  snowball::require_false   (object&, Fn&&, const T& input, const T_& expectation);
       
       void  snowball::require_throw   (Fn&&);
       void  snowball::require_throw   (Fn&&, Args&&...);
       void  snowball::require_nothrow (Fn&&, Args&&...);
       

       void  snowball::check           (const bool expected);
       void  snowball::check           (Fn&&, const T& expected);
       void  snowball::check           (Object&, Fn&&, const T& input, const T& expected, Fn_g&& (getter));
       void  snowball::check_nothrow   (Object&, Fn&&, const T& input);
       void  snowball::check_nothrow   (Object&, Fn&&);
       void  snowball::check_false     (Fn&&, const T& expected);
       void  snowball::check_false     (Fn&&, const T& expected, const T...& inputs);
       void  snowball::check_false     (Fn&&, const T& expected, const T& input, const T& output, Fn_g&& (getter));
       void  snowball::check_false     (Object&, Fn&&, const T& input, const T& expected);
       void  snowball::check_throw     (Fn&&);
       void  snowball::check_throw     (Fn&&, Args&&...);
       void  snowball::check_nothrow   (Fn&&);
       void  snowball::check_nothrow   (Fn&&, Args&&...);
       void  snowball::fuzz            (Fn&&, size_t);
// T is a templated typename, will bind any valid C++ type
// Fn is a templated function, will bind any valid C++ function
// Args... is a variadic template, will bind any number of arguments
```
## Specific Usage

### Example A
```cpp
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
  // following line causes an error
  sb::require(&factorial, 1, 0);
}
```

### Example B
```cpp
#include "../include/snowball.hpp"

#include <limits>
#include <vector>

void
fill_vec(std::vector<int> &vec)
{
  for ( int i = 0; i < sizeof(vec); i++ )
    vec.at(i) = std::numeric_limits<int>::max();
}

bool
verify_vec(const std::vector<int> &vec)
{
  for ( auto n : vec )
    if ( n != std::numeric_limits<int>::max() )
      return false;
  return true;
}
int
main(void)
{
  sb::verify_debug();
  sb::test_case("Vector fill test");
  std::vector<int> my_vec(1024);
  sb::require_nothrow(&fill_vec, my_vec);
  sb::require(&verify_vec, true, my_vec);
  return 0;
}
```


## Installation

snowball is a single-file header-only library. Just copy the sole file from `include/` and include it in your testing project.


## Misc
no external dependencies, requires C++20, tested with g++.
snowball needs the following headers (and associated .so) to compile properly (normally are distributed with every standard Linux/C++ distribution).

```cpp
#include <cstdio>
#include <cstdlib>
#include <random>
#include <tuple>
#include <type_traits>
#include <utility>

#include <execinfo.h> // TODO: add Windows spec.
#include <exception>
#include <stdexcept>
#include <string>
```

## License
Licensed under the Boost Software License.
