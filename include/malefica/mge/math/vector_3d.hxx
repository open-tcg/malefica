#ifndef MALEFICA_MGE_MATH_VECTOR_3D_HXX
#define MALEFICA_MGE_MATH_VECTOR_3D_HXX

#include <cmath>

#include <algorithm>
#include <array>
#include <type_traits>

#include <malefica/mge/algorithm.hxx>

namespace mge
{
  namespace math
  {
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    class vector_3d_base
    {
    public:
      using value_type = T;

      explicit vector_3d_base() noexcept : m_array{0, 0, 0} {}
      vector_3d_base(value_type x, value_type y, value_type z) noexcept : m_array{x, y, z} {}
      vector_3d_base(const vector_3d_base& v) noexcept : m_array(v.m_array) {}
      vector_3d_base(vector_3d_base&& v) noexcept : m_array(std::move(v.m_array)) {}

      vector_3d_base& operator=(const vector_3d_base& rhs) noexcept
      {
        vector_3d_base(rhs).swap(*this);
        return *this;
      }
      vector_3d_base& operator=(vector_3d_base&& rhs) noexcept
      {
        vector_3d_base(std::move(rhs)).swap(*this);
        return *this;
      }

      value_type x() const noexcept { return m_array[0]; }
      value_type& x() noexcept { return m_array[0]; }

      value_type y() const noexcept { return m_array[1]; }
      value_type& y() noexcept { return m_array[1]; }

      value_type z() const noexcept { return m_array[2]; }
      value_type& z() noexcept { return m_array[2]; }

      inline bool operator==(const vector_3d_base& v) const noexcept { return (m_array == v.m_array); }
      inline bool operator!=(const vector_3d_base& v) const noexcept { return (m_array != v.m_array); }

      inline float scalar_product(const vector_3d_base& rhs) const noexcept
      {
        return (m_array[0] * rhs.m_array[0]) + (m_array[1] * rhs.m_array[1]) + (m_array[2] * rhs.m_array[2]);
      }
      inline vector_3d_base cross_product(const vector_3d_base& rhs) const noexcept
      {
        return vector_3d_base(m_array[1] * rhs.m_array[2] - rhs.m_array[1] * m_array[2],
                              rhs.m_array[0] * m_array[2] - m_array[0] * rhs.m_array[2],
                              m_array[0] * rhs.m_array[1] - rhs.m_array[0] * m_array[1]);
      }

      inline float operator*(const vector_3d_base& rhs) const noexcept { return scalar_product(rhs); }
      inline vector_3d_base operator^(const vector_3d_base& rhs) const noexcept { return cross_product(rhs); }

      inline vector_3d_base operator+(const vector_3d_base& rhs) const noexcept
      {
        return vector_3d_base(m_array[0] + rhs.m_array[0], m_array[1] + rhs.m_array[1], m_array[2] + rhs.m_array[2]);
      }
      inline vector_3d_base operator-(const vector_3d_base& rhs) const noexcept
      {
        return vector_3d_base(m_array[0] - rhs.m_array[0], m_array[1] - rhs.m_array[1], m_array[2] - rhs.m_array[2]);
      }
      inline vector_3d_base operator-(void) const noexcept { return vector_3d_base(-m_array[0], -m_array[1], -m_array[2]); }

      inline vector_3d_base operator*(float scalar) const noexcept { return vector_3d_base(m_array[0] * scalar, m_array[1] * scalar, m_array[2] * scalar); }
      inline vector_3d_base operator/(float scalar) const noexcept { return vector_3d_base(m_array[0] / scalar, m_array[1] / scalar, m_array[2] / scalar); }
      friend vector_3d_base operator*(float k, const vector_3d_base& v) { return v * k; }

      inline vector_3d_base& operator/=(const float scalar) noexcept
      {
        *this = *this / scalar;
        return *this;
      }

      inline vector_3d_base& operator*=(const float scalar) noexcept
      {
        *this = *this * scalar;
        return *this;
      }

      inline vector_3d_base& operator+=(const vector_3d_base& v) noexcept
      {
        *this = *this + v;
        return *this;
      }

      inline vector_3d_base& operator-=(const vector_3d_base& v) noexcept
      {

        *this = *this - v;
        return *this;
      }

      inline float length() const noexcept { return std::sqrt(m_array[0] * m_array[0] + m_array[1] * m_array[1] + m_array[2] * m_array[2]); }

      inline vector_3d_base& normalize() noexcept
      {
        auto len = length();
        if (len != 0.0f)
        {
          (*this) *= (1.0f / len);
        }
        return *this;
      }

      inline vector_3d_base direction() const noexcept { return vector_3d_base(*this).normalize(); }

      inline float angle() const noexcept { return angle(vector_3d_base(1, 1)); }
      inline float angle(const vector_3d_base& other) const noexcept
      {
        auto scalar = scalar_product(other);
        auto norm_lhs = length();
        auto norm_rhs = other.length();

        return std::acos(scalar / (norm_lhs * norm_rhs));
      }

      inline vector_3d_base& clamp(const vector_3d_base& min, const vector_3d_base& max)
      {
        m_array[0] = mge::clamp(m_array[0], min.m_array[0], max.m_array[0]);
        m_array[1] = mge::clamp(m_array[1], min.m_array[1], max.m_array[1]);
        m_array[2] = mge::clamp(m_array[2], min.m_array[2], max.m_array[2]);
        return *this;
      }

      void swap(vector_3d_base& other)
      {
        using std::swap;
        swap(m_array, other.m_array);
      }

      inline value_type* data() noexcept { return m_array.data(); }
      inline const value_type* data() const noexcept { return m_array.data(); }

    private:
      std::array<value_type, 3> m_array;
    };

    template <typename T>
    inline void swap(vector_3d_base<T>& lhs, vector_3d_base<T>& rhs)
    {
      lhs.swap(rhs);
    }

    template <typename T>
    vector_3d_base<T>& clamp(vector_3d_base<T>& vec, const vector_3d_base<T>& min, const vector_3d_base<T>& max)
    {
      return vec.clamp(min, max);
    }

    typedef vector_3d_base<float> vector_3d;

  } // namespace math

} // namespace mge

#endif // MALEFICA_MGE_MATH_VECTOR_3D_HXX
