//  Copyright (c) 2024- David Lucius Severus
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
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
