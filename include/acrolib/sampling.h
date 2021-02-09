#pragma once

#include <vector>

#include <acrolib/math.h>

namespace acro
{
/** \brief Get a uniform grid without saving all the grid points explicitly.
 *
 * When constructed, the object behaves as a very basic vector that contains
 * all the grid points. For example, you can loop over them:
 *
 * ```
 * GridSamples samples({{1, 2}, {0.3, 0.4, 0.5}});
 * for (size_t i=0; i < samples.size(); ++i)
 *    auto sample = samples[i];
 * ```
 *
 * (Notice that range based for loops are not supported yet.)
 *
 * Supported types to represent grid points (`SampleType`) are:
 *  - `Eigen::VectorXd`
 *  - `std::vector<double>`
 *
 * **/
template <typename SampleType>
class GridSamples
{
  std::vector<std::vector<double>> sample_ranges_;
  std::vector<std::size_t> sample_range_sizes_;
  std::size_t total_sample_count_{ 1 };
  std::size_t sample_count_{ 0 };
  std::size_t n_;

public:
  GridSamples(const std::vector<std::vector<double>>& sample_ranges);

  SampleType operator[](std::size_t ind) const;

  std::size_t size() const
  {
    return total_sample_count_;
  }
};

struct Limits
{
  double lower, upper;
};

/** \brief Given joint limits for every dimension and a desired resolution,
 * calculate the specific values that need to be sampled along every dimension.
 * 
 * For example, given limits {{0, 1}, {0, 2}} with a resolution of 0.5 we get:
 * { {0.0, 0.5, 1.0} ,  {0.0, 0.5, 1.0, 1.5, 2.0} }
 * Note that this includes the boundaries. We assume the limits are closed intervals.
 * 
 * **/
std::vector<std::vector<double>> calculateRangesFromLimits(const std::vector<Limits>& limits, double resolution);

/** \brief Create a simple 1D range, similar to NumPy's and Matlab's linspace. **/
template <typename T>
std::vector<T> range(T lower_bound, T upper_bound, int num_samples)
{
  std::vector<T> r;
  if (num_samples == 1)
  {
    r = { lower_bound };
  }
  else
  {
    r.resize(num_samples);
    T increment = (upper_bound - lower_bound) / (num_samples - 1);
    for (int i = 0; i < num_samples; ++i)
    {
      r[i] = lower_bound + i * increment;
    }
  }
  return r;
}

}  // namespace acro
