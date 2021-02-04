#include <acrolib/dispersion.h>

#include <limits>

namespace acro
{
    double calcDispersion(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b)
{
  // vector<double> mins;
  // mins.reserve(a.size());

  double current_dispersion{ 0.0 };
  for (size_t ai{ 0 }; ai < a.size(); ++ai)
  {
    double current_min{ std::numeric_limits<double>::max() };
    double current_norm{ 0.0 };
    for (size_t bi{ 0 }; bi < b.size(); ++bi)
    {
      if (ai == bi)
        continue;

      current_norm = l2Norm(a[ai], b[bi]);

      if (current_norm < current_min)
        current_min = current_norm;
    }
    // mins.push_back(current_min);
    if (current_min > current_dispersion)
      current_dispersion = current_min;
  }
  // assert(mins.size() == a.size());
  return current_dispersion;
}

double calcDispersion(const std::vector<std::vector<double>>& a, const GridSamples<std::vector<double>>& b)
{
  // vector<double> mins;
  // mins.reserve(a.size());

  double current_dispersion{ 0.0 };
  for (size_t ai{ 0 }; ai < a.size(); ++ai)
  {
    double current_min{ std::numeric_limits<double>::max() };
    double current_norm{ 0.0 };
    for (size_t bi{ 0 }; bi < b.size(); ++bi)
    {
      if (ai == bi)
        continue;

      current_norm = l2Norm(a[ai], b[bi]);

      if (current_norm < current_min)
        current_min = current_norm;
    }
    // mins.push_back(current_min);
    if (current_min > current_dispersion)
      current_dispersion = current_min;
  }
  // assert(mins.size() == a.size());
  return current_dispersion;
}
}
