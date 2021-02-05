#include <acrolib/dispersion.h>

#include <acrolib/sampling.h>
#include <acrolib/dispersion.h>

#include <cassert>
// #include <iostream>
#include <limits>
#include <vector>
#include <numeric>

constexpr double EPS = std::numeric_limits<double>::epsilon();

using namespace std;
using namespace acro;

void ASSERT_EQ(double a, double b, double abs_tol = EPS)
{
  assert(abs(a - b) < abs_tol);
}

using Sample = vector<double>;

void testNearestNeighbour()
{
  vector<double> sample{ 1.0, 2.0, 3.0 };
  vector<vector<double>> others{ { -1.0, 2.0, -3.0 }, { 1.0, 2.2, 3.0 }, { 0, 0, 0 } };

  double d = calcNearestNeighbour(sample, others);
  ASSERT_EQ(d, 0.2);
}

void testDispersion()
{
  // some samples with a known dispersion in a 2D grid
  vector<Sample> samples;
  samples.push_back({ 0.25, 0.25 });
  samples.push_back({ 0.50, 0.60 });
  samples.push_back({ 1.25, 0.20 });
  samples.push_back({ 1.75, 0.20 });

  ASSERT_EQ(calcDispersion(samples), 0.5);

  // some samples with a known dispersion in a 2D grid
  vector<Sample> grid;
  vector<vector<double>> ranges{ { 0.0, 0.5, 1.0, 1.5, 2.0 }, { 0.0, 0.5, 1.0 } };
  for (auto x : ranges[0])
  {
    for (auto y : ranges[1])
    {
      grid.push_back({ x, y });
    }
  }

  // the grid point in the upper right corner of the grid is the furthest
  // away from any sample, in this case the sample (1.75, 0.20)
  double expected_dispersion = sqrt(0.8 * 0.8 + 0.25 * 0.25);
  ASSERT_EQ(calcDispersion(samples, grid), expected_dispersion);

  vector<Limits> limits{ { 0, 2 }, { 0, 1 } };
  GridSamples<vector<double>> gs = createGridSamples<vector<double>>(limits, 0.5);

  ASSERT_EQ(calcDispersion(samples, gs), expected_dispersion);
}

int main()
{
  testNearestNeighbour();
  testDispersion();
  return 0;
}
