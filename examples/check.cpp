//  Copyright (c) 2024- David Lucius Severus
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
#include "../include/snowball.hpp"

#include <algorithm>
#include <string>
#include <vector>

class string_factory
{
  std::vector<std::string> __buf;

public:
  ~string_factory(void) = default;
  string_factory(void) {}
  string_factory(const string_factory &) = default;
  string_factory(string_factory &&) = default;
  bool
  append(const char *str)
  {
    try {
      __buf.emplace_back(str);
      std::reverse(__buf.back().begin(), __buf.back().end());
    } catch ( ... ) {
      return false;
    }
    return true;
  }
  std::string &
  at(size_t n)
  {
    return __buf.at(n);
  }
  void
  invert()
  {
    std::reverse(__buf.begin(), __buf.end());
  }
};

int
main(void)
{
  sb::verify_debug();
  sb::test_case("String factory test");
  string_factory fac;
  for ( int i = 0; i < 1000; ++i )
    sb::check(fac, &string_factory::append, "Test", true);
  sb::test_case("Checking at() accesses:");
  sb::check_nothrow(fac, &string_factory::at, 0);
  sb::check("Test" == fac.at(0));
  sb::check("tseT" == fac.at(0));
  sb::check_nothrow(fac, &string_factory::at, 10);
  sb::check_nothrow(fac, &string_factory::at, 20);
  sb::check_nothrow(fac, &string_factory::at, 60);
  sb::check_nothrow(fac, &string_factory::at, (2 << 20));
  sb::test_case("Checking invert():");
  sb::check_nothrow(fac, &string_factory::invert);
  return 0;
}
