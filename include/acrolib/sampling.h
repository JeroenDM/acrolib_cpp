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

  SampleType operator[](std::size_t ind);

  std::size_t size() const
  {
    return total_sample_count_;
  }
};

}  // namespace acro
