#include <acrolib/dispersion.h>

#include <acrolib/sampling.h>
#include <acrolib/dispersion.h>

#include <cassert>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;
using namespace acro;

void ASSERT_EQ(double a, double b, double abs_tol=1e-16)
{
  assert(abs(a - b) < abs_tol);
}


using Sample = vector<double>;

int main()
{
  // some samples with a known dispersion in a 2D grid
  vector<Sample> samples;
  samples.push_back({ 0.25, 0.25 });
  samples.push_back({ 0.50, 0.60 });
  samples.push_back({ 1.25, 0.20 });
  samples.push_back({ 1.75, 0.20 });

  cout << calcDispersion(samples, samples) << endl;
  ASSERT_EQ(calcDispersion(samples, samples), 0.5);

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
  cout << calcDispersion(samples, grid) << endl;
  ASSERT_EQ(calcDispersion(samples, grid), sqrt(2 * 0.25 * 0.25));

  vector<Limits> limits{ { 0, 2 }, { 0, 1 } };
  GridSamples<vector<double>> gs = createGridSamples<vector<double>>(limits, 0.5);
  cout << calcDispersion(samples, gs) << endl;
  ASSERT_EQ(calcDispersion(samples, gs), sqrt(2 * 0.25 * 0.25));

  return 0;
}
