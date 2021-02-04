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
SampleType GridSamples<SampleType>::operator[](std::size_t ind)
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

}  // namespace acro
