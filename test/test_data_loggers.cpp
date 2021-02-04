#include <acrolib/data_loggers.h>
#include <acrolib/extern/npy.h>

#include <cassert>
#include <iostream>
#include <fstream>
#include <Eigen/Dense>

const std::string TEST_FILE = R"(one,two,three
1,2,3
4,5,6
hello,3,0
)";

using namespace acro;
using namespace std;

bool testFileLogger()
{
  Logger log("test.csv");

  log.header("one,two,three");

  Eigen::VectorXd q1(3);
  q1 << 1, 2, 3;
  log.log(q1);
  log.nextLine();

  vector<double> q2{ 4, 5, 6 };
  log.log(q2);
  log.nextLine();

  log.log("hello");
  log.log(3);
  log.log(false);
  log.nextLine();

  return true;
}

bool checkLoggedFile()
{
  // read the file again and compare result
  std::ifstream file("test.csv");
  assert(file.is_open());

  std::stringstream buffer;
  buffer << file.rdbuf();
  assert(buffer.str() == TEST_FILE);

  return true;
}

bool testNumPyLogger()
{
  // log a 5 by 3 matrix to a file
  NumPyLogger log("mat.npy", 5, 3);

  for (int row{ 0 }; row < 5; ++row)
  {
    Eigen::Vector3d v(9, 9, (double)row);
    log.log(v);
  }

  log.finish();

  return true;
}

bool checkLoggedNumPyFile()
{
  // read the file again and compare result
  // you can also read the same file using NumPy and hopefully get the same result
  bool fortran_order;
  vector<unsigned long> shape;
  vector<double> data;
  npy::LoadArrayFromNumpy("mat.npy", shape, fortran_order, data);

  assert(fortran_order == false);
  assert(shape.at(0) == 5);
  assert(shape.at(1) == 3);

  vector<double> expected_data{ 9, 9, 0, 9, 9, 1, 9, 9, 2, 9, 9, 3, 9, 9, 4 };

  for (size_t k{ 0 }; k < data.size(); ++k)
  {
    assert(data[k] == expected_data[k]);
  }

  return true;
}

int main()
{
  assert(testFileLogger());
  assert(checkLoggedFile());

  assert(testNumPyLogger());
  assert(checkLoggedNumPyFile());

  return 0;
}
