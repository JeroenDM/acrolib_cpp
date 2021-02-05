#include <acrolib/dispersion.h>

#include <limits>

namespace acro
{
constexpr double INF{ std::numeric_limits<double>::max() };

double calcNearestNeighbour(const std::vector<double>& sample, const std::vector<std::vector<double>> other_samples)
{
  double d_min{ INF }, d{ 0.0 };
  for (const auto& xi : other_samples)
  {
    d = l2Norm(sample, xi);

    if (d < d_min)
    {
      d_min = d;
    }
  }
  return d_min;
}

double calcDispersion(const std::vector<std::vector<double>>& samples,
                      const std::vector<std::vector<double>>& reference_samples)
{
  double d_max{ 0.0 };  // keeps track of the current maximum dispersion
  double d_min{ 0.0 };  // the current nearest neighbour distance

  // Calculate the maximum of all the nearest neighbors of a sample with the reference grid.
  for (const auto& xi : reference_samples)
  {
    d_min = calcNearestNeighbour(xi, samples);
    if (d_min > d_max)
    {
      d_max = d_min;
    }
  }

  return d_max;
}

double calcDispersion(const std::vector<std::vector<double>>& samples,
                      const GridSamples<std::vector<double>>& reference_samples)
{
  double d_max{ 0.0 };  // keeps track of the current maximum dispersion
  double d_min{ 0.0 };  // the current nearest neighbour distance

  // Calculate the maximum of all the nearest neighbors of a sample with the reference grid.
  // GridSamples does not support range based for loops yet
  for (size_t ix{ 0 }; ix < reference_samples.size(); ++ix)
  {
    d_min = calcNearestNeighbour(reference_samples[ix], samples);
    if (d_min > d_max)
    {
      d_max = d_min;
    }
  }

  return d_max;
}

double calcDispersion(const std::vector<std::vector<double>>& P)
{
  // Calculate the maximum of all the nearest neighbors of a sample with the reference grid.
  double d_max{ 0.0 };
  for (size_t xi{ 0 }; xi < P.size(); ++xi)
  {
    // Calculate all the sample pi that is closest to the current xi
    double d_min{ std::numeric_limits<double>::max() };
    double d{ 0.0 };
    for (size_t pj{ 0 }; pj < P.size(); ++pj)
    {
      if (xi == pj)
        continue;

      d = l2Norm(P[xi], P[pj]);

      if (d < d_min)
        d_min = d;
    }
    if (d_min > d_max)
      d_max = d_min;
  }

  return d_max;
}
}  // namespace acro
