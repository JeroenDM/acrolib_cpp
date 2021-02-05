#include "acrolib/sampling.h"

#include <Eigen/Core>

namespace acro
{
template <typename SampleType>
GridSamples<SampleType>::GridSamples(const std::vector<std::vector<double>>& sample_ranges)
  : sample_ranges_(sample_ranges), n_(sample_ranges.size())
{
  for (auto& r : sample_ranges_)
    sample_range_sizes_.push_back(r.size());

  for (auto& s : sample_range_sizes_)
    total_sample_count_ *= s;
}

template <typename SampleType>
SampleType GridSamples<SampleType>::operator[](std::size_t ind) const
{
  SampleType sample(n_);
  auto s = convertBase(ind, sample_range_sizes_);
  for (std::size_t dim{ 0 }; dim < n_; ++dim)
  {
    sample[dim] = sample_ranges_.at(dim).at(s[dim]);
  }
  return sample;
}

template class GridSamples<Eigen::VectorXd>;
template class GridSamples<std::vector<double>>;

std::vector<std::vector<double>> calculateRangesFromLimits(const std::vector<Limits>& limits, double resolution)
{
  // calculate the specific sample levels for each dimension
  std::vector<std::vector<double>> sample_ranges(limits.size());
  for (size_t k{ 0 }; k < limits.size(); ++k)
  {
    double value = limits.at(k).lower;
    while (value <= limits.at(k).upper)
    {
      sample_ranges.at(k).push_back(value);
      value += resolution;
    }
  }

  return sample_ranges;
}

}  // namespace acro
