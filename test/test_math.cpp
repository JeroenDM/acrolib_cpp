#include <acrolib/math.h>

#include <cassert>
#include <iostream>

using namespace acro;
using namespace std;

// See example explanation in math.h.
// clang-format off
const vector<vector<size_t>> ALLDIGITS ={
    {0, 0},
    {0, 1},
    {0, 2},
    {0, 3},
    {0, 4},
    {1, 0},
    {1, 1},
    {1, 2},
    {1, 3},
    {1, 4},
    {2, 0},
    {2, 1},
    {2, 2},
    {2, 3},
    {2, 4}
};
// clang-format on

bool testFromDocString()
{
  const vector<size_t> bases{ 3, 5 };

  for (size_t n{ 0 }; n < 15; ++n)
  {
    auto digits = convertBase(n, bases);
    assert(digits.size() == 2);
    assert(digits.at(0) == ALLDIGITS.at(n).at(0));
    assert(digits.at(1) == ALLDIGITS.at(n).at(1));
  }

  return true;
}

int main()
{
  assert(testFromDocString());

  return 0;
}
