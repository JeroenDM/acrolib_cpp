#include <acrolib/sampling.h>
#include <acrolib/test_utils.h>

#include <cassert>
#include <iostream>
#include <Eigen/Core>

using namespace acro;
using namespace std;

void testRangeCalculation()
{
  vector<vector<double>> expected_ranges{ { 0.0, 0.5, 1.0, 1.5, 2.0 }, { 0.0, 0.5, 1.0 } };
  vector<Limits> limits{ { 0, 2 }, { 0, 1 } };
  auto sample_ranges = calculateRangesFromLimits(limits, 0.5);

  assert(sample_ranges.size() == expected_ranges.size());
  for (size_t dim{ 0 }; dim < sample_ranges.size(); ++dim)
  {
    assert(sample_ranges[dim].size() == expected_ranges[dim].size());
    for (size_t i{ 0 }; i < sample_ranges[dim].size(); ++i)
    {
      ASSERT_EQ(sample_ranges[dim][i], expected_ranges[dim][i]);
    }
  }
}

void test1()
{
  vector<vector<double>> ranges{ { 1.1, 2.2 }, { 0.5, 1.5, 2.5 } };

  GridSamples<Eigen::VectorXd> sampler(ranges);

  for (size_t k{ 0 }; k < sampler.size(); ++k)
  {
    cout << sampler[k].transpose() << endl;
  }
}

void test2()
{
  vector<vector<double>> ranges{ { 1.1, 2.2 }, { 0.5, 1.5, 2.5 } };

  GridSamples<vector<double>> sampler(ranges);

  for (size_t k{ 0 }; k < sampler.size(); ++k)
  {
    auto sample = sampler[k];
    cout << sample[0] << " " << sample[1] << endl;
  }
}

int main()
{
  test1();
  test2();
}
