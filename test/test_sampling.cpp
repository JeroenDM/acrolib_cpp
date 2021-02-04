#include <acrolib/sampling.h>

#include <cassert>
#include <iostream>
#include <Eigen/Core>

using namespace acro;
using namespace std;

bool test1()
{
    vector<vector<double>> ranges {{1.1, 2.2}, {0.5, 1.5, 2.5}};

    GridSamples<Eigen::VectorXd> sampler(ranges);

    for (size_t k{0}; k < sampler.size(); ++k)
    {
        cout << sampler[k].transpose() << endl;
    }

    return true;
}

bool test2()
{
    vector<vector<double>> ranges {{1.1, 2.2}, {0.5, 1.5, 2.5}};

    GridSamples<vector<double>> sampler(ranges);

    for (size_t k{0}; k < sampler.size(); ++k)
    {
        auto sample = sampler[k];
        cout << sample[0] << " " << sample[1] << endl;
    }

    return true;
}


int main()
{
    assert(test1());
    assert(test2());
}
