#include <acrolib/data_loggers.h>
#include <acrolib/extern/npy.h>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <vector>

namespace acro
{
Logger::Logger(const std::string& filename)
{
  os_.open(filename);
  assert(os_.is_open());
  os_ << std::setprecision(16);
}

Logger::~Logger()
{
  // os_ << std::endl;
  os_.close();
}

void Logger::separate()
{
  if (line_emtpy_)
    line_emtpy_ = false;
  else
    os_ << separator_;
}

void Logger::header(const std::string& header)
{
  if (line_emtpy_)
    os_ << header << "\n";
  else
    std::cerr << "Cannot write header, line already constains data\n";
}

void Logger::nextLine()
{
  os_ << "\n";
  line_emtpy_ = true;
}

void Logger::log(const Eigen::VectorXd& v)
{
  for (unsigned int i{ 0 }; i < v.size(); ++i)
  {
    log(v[i]);
  }
}

void Logger::log(const Eigen::Ref<Eigen::VectorXd>& v)
{
  for (unsigned int i{ 0 }; i < v.size(); ++i)
  {
    log(v[i]);
  }
}

void Logger::log(const std::vector<double>& v)
{
  for (auto value : v)
  {
    log(value);
  }
}

NumPyLogger::NumPyLogger(const std::string& filename, size_t rows, size_t cols)
  : filename_(filename), num_samples_(rows), num_dof_(cols)
{
  data_.reserve(rows * cols);
}

void NumPyLogger::log(const Eigen::VectorXd& v)
{
  assert((size_t)v.size() == num_dof_);
  data_.insert(data_.end(), v.data(), v.data() + num_dof_);
}

void NumPyLogger::finish()
{
  const long unsigned shape[] = { data_.size() / num_dof_, num_dof_ };
  npy::SaveArrayAsNumpy(filename_, false, 2, shape, data_);
  data_.clear();
}

}  // namespace acro
