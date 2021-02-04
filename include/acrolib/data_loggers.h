#pragma once

#include <fstream>
#include <string>
#include <Eigen/Dense>
#include <vector>

namespace acro
{

  /** \brief Write data to (csv) files.
   * 
   * Opens a file on construction.
   * File is closed in destructor.
   * 
   * How to use it?
   * 1) Use `header` to add a header such as "field1,field2,field2"
   *    or something. This is useful for pandas an similar libraries
   *    that can use this header.
   * 2) Log some data to it with `log`.
   * 3) Use `nextline` to add a new row.
   * 
   * */
class Logger
{
  std::ofstream os_;
  bool line_emtpy_{ true };
  const char separator_{ ',' };

  /** Add a separator the the stream, except when the line is still empty. **/
  void separate();

public:
  Logger(const std::string& filename);
  ~Logger();

  // a logger can't be copied
  Logger(Logger const&) = delete;
  Logger& operator=(Logger const&) = delete;

  /** Write a single string to an empty line, useful to add an header at the start. **/
  void header(const std::string& header);

  /** Start logging on a new line. **/
  void nextLine();

  // Log some vector like types
  void log(const Eigen::VectorXd& v);
  void log(const Eigen::Ref<Eigen::VectorXd>& v);
  void log(const std::vector<double>& v);

  /** Allow logging of any type that can be written to the stream. **/
  template <class T>
  void log(T value)
  {
    separate();
    os_ << value;
  }
};

class NumPyLogger
{
  const std::string filename_;
  const size_t num_samples_;
  const size_t num_dof_;

  std::vector<double> data_;

public:
  /** Provide an estimate of the data size for efficiency.
   *
   * The num_dof should be respected, the num_samples not,
   * it will just write the samples that where logged to the file.
   * **/
  NumPyLogger(const std::string& filename, size_t rows, size_t cols);
  ~NumPyLogger() = default;

  void log(const Eigen::VectorXd& v);
  void finish();
};
}  // namespace acro
