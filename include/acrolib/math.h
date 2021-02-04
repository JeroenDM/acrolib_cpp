#include <vector>

namespace acro
{
/**
 * Convert a decimal number to a number into a mixed radix number,
 * with variable base, specified in the bases vector.
 *
 * This is useful to represent uniform grid samples without saving all the grid points explicitly.
 * For example, let's say we want to get a uniform grid on [0,1] x [0,2].
 * With a resolution of 0.5 we want 3 grid points for the first dimension and 5 for the second.
 *
 * We get the grid points by converting all decimal numbers from 0 to (3 * 5 -1 = 14)
 * to mixed radix number with based [3, 5].
 * 
 * 0 -> 00
 * 1 -> 01
 * 2 -> 02
 * ...
 * 4 -> 04
 * 5 -> 10
 * 6 -> 11
 * ...
 * 13 -> 23
 * 14 -> 24
 * **/
inline std::vector<size_t> convertBase(size_t n, const std::vector<size_t>& bases)
{
  std::vector<size_t> digits(bases.size());
  // magic unsigend integer reverse loop from stack overflow
  for (size_t i = bases.size(); i-- > 0;)
  {
    digits[i] = n % bases[i];
    n /= bases[i];
  }
  return digits;
}

}  // namespace acro
