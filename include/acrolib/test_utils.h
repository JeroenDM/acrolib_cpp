#pragma once

#include <cassert>
#include <cmath>
#include <limits>

namespace acro
{
constexpr double EPS = std::numeric_limits<double>::epsilon();

void ASSERT_EQ(double a, double b, double abs_tol = EPS)
{
  assert(abs(a - b) < abs_tol);
}
}  // namespace acro
