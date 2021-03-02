#include <vector>

#include <acrolib/math.h>
#include <acrolib/sampling.h>

#include <Eigen/Core>

namespace acro
{
/** \brief Simple linear time nearest neighbour calculation. **/
double calcNearestNeighbour(const std::vector<double>& sample, const std::vector<std::vector<double>>& other_samples);
double calcNearestNeighbour(const Eigen::VectorXd& sample, const std::vector<Eigen::VectorXd>& other_samples);

/** \brief Approximately calculate the dispersion (the largest Euclidian ball that fits in between samples).
 *
 * It takes two sample vectors. The first one is the one for which we want to calculate the dispersion.
 * The second one is used to approximately calculate the dispersion.
 * For every sample in a, we calculate the nearest neighbour in b.
 * The maximum of all these nearest neighbors approximates the dispresion if the samples in b
 * cover the complete sample volume sufficiently.
 *
 * max (i=1..len(reference)) [ min (j=1...len(samples)) [ || xi -pj || ]]
 *
 * */
double calcDispersion(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b);
double calcDispersion(const std::vector<Eigen::VectorXd>& a, const std::vector<Eigen::VectorXd>& b);

/** \brief Dispersion calculation that takes a GridSamples object as reference samples.
 *
 * This object can return any grid sample without actually saving all the grid points in a vector.
 * This is way more memory efficient.
 * **/
double calcDispersion(const std::vector<std::vector<double>>& a, const GridSamples<std::vector<double>>& b);
double calcDispersion(const std::vector<Eigen::VectorXd>& a, const GridSamples<Eigen::VectorXd>& b);

/** \brief Simple but potentially very wrong disperion calculation.
 *
 * You can use the samples themself as a reference grid to approximate the dispersion,
 * but this is only a good approximate for uniform random samples that are known to cover
 * the whole space somewhat evenly.
 * */
double calcDispersion(const std::vector<std::vector<double>>& a);
}  // namespace acro
