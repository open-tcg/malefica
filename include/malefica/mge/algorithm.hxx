#ifndef MALEFICA_MGE_ALGORITHM_HXX
#define MALEFICA_MGE_ALGORITHM_HXX

#if __cplusplus > 201402L

#include <algorithm>

namespace mge
{
  using std::clamp;
} // namespace mge

#else

#include <cassert>

namespace mge
{

  template <typename T>
  const T& clamp(const T& value, const T& low, const T& high)
  {
    assert(!(high < low));
    return (value < low) ? low : (high < value) ? high : value;
  }

  template <typename T, typename Compare>
  const T& clamp(const T& value, const T& low, const T& high, Compare compare)
  {
    assert(!compare(high, low));
    return compare(value, low) ? low : compare(high, value) ? high : value;
  }
} // namespace mge

#endif

#endif // MALEFICA_MGE_ALGORITHM_HXX
