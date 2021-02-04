#include <vector>

#include <acrolib/math.h>
#include <acrolib/sampling.h>

namespace acro
{
double calcDispersion(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b);
double calcDispersion(const std::vector<std::vector<double>>& a, const GridSamples<std::vector<double>>& b);
}  // namespace acro
