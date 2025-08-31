//  Copyright (c) 2024- David Lucius Severus
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
#include "../include/snowball.hpp"

#include <exception>
#include <stdexcept>

int
returns_5(void)
{
  return 5;
}

void
doesnt_throw(void)
{
  return;
}
void
throws(void)
{
  throw std::logic_error{ "sample throw" };
}

struct obj {
  int member = 5;

  obj &
  set_broken(int b)
  {
    member = static_cast<int>(reinterpret_cast<long long>(&b));     // permissive compilation ;c
    return *this;
  }
  obj &
  set(int b)
  {
    member = b;
    return *this;
  }
  int
  get(void)
  {
    return member;
  }
  bool
  operator!=(const obj &o)
  {
    return (member != o.member);
  }
};

bool
all_zero(int a, long b, char c)
{
  return !a and !b and !c;
}

void
callback()
{
  std::printf("custom callback\n");
}

int
main(void)
{
  sb::require_callback(&callback);
  sb::test_case("Equality check by value");
  sb::require(0 == 0);
  sb::test_case("Function calling");
  sb::require(&all_zero, 0, (long)0, (char)0);
  sb::test_case("Function calling inline execution");
  sb::require(&returns_5, 5);
  sb::test_case("Object testing");
  obj object;
  sb::require(object, &obj::set, 1, 1, &obj::get);
  sb::require(object, &obj::set, 1, object);
  sb::test_case("Checking if output is false");
  sb::require_false(&returns_5, 435);
  sb::test_case("Checking if functions throw");
  sb::require_throw(&throws);
  sb::require_throw(&doesnt_throw);
  return 0;
}
