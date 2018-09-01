#ifndef MALEFICA_MATH_VECTOR_2D_HXX
#define MALEFICA_MATH_VECTOR_2D_HXX

#include <cmath>

#include <algorithm>
#include <type_traits>

#include <malefica/algorithm.hxx>

namespace malefica
{
  namespace math
  {
    template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
    class vector_2d_base
    {
    public:
      using value_type = T;

      explicit vector_2d_base() noexcept : m_x(0), m_y(0) {}
      explicit vector_2d_base(value_type x, value_type y) noexcept : m_x(x), m_y(y) {}

      vector_2d_base(const vector_2d_base& other) : m_x(other.m_x), m_y(other.m_y) {}
      vector_2d_base(vector_2d_base&& other) : m_x(std::move(other.m_x)), m_y(std::move(other.m_y)) {}

      inline vector_2d_base& operator=(const vector_2d_base& other)
      {
        vector_2d_base(other).swap(*this);
        return *this;
      }

      inline vector_2d_base& operator=(vector_2d_base&& other)
      {
        vector_2d_base(std::move(other)).swap(*this);
        return *this;
      }

      value_type x() const noexcept { return m_x; }
      value_type& x() noexcept { return m_x; }

      value_type y() const noexcept { return m_y; }
      value_type& y() noexcept { return m_y; }

      inline bool operator==(const vector_2d_base& v) const noexcept { return m_x == v.m_x && m_y == v.m_y; }
      inline bool operator!=(const vector_2d_base& v) const noexcept { return !(*this == v); }

      inline float operator^(const vector_2d_base& v) const noexcept { return cross_product(v); }
      inline float operator*(const vector_2d_base& v) const noexcept { return scalar_product(v); }

      inline float scalar_product(const vector_2d_base& v) const noexcept { return (m_x * v.m_x) + (m_y * v.m_y); }
      inline float cross_product(const vector_2d_base& v) const noexcept { return (m_x * v.m_y) - (m_y * v.m_x); }

      inline vector_2d_base operator*(float s) const noexcept { return vector_2d_base(m_x * s, m_y * s); }
      inline vector_2d_base operator/(float s) const noexcept { return vector_2d_base(m_x / s, m_y / s); }
      inline vector_2d_base operator+(const vector_2d_base& v) const noexcept { return vector_2d_base(m_x + v.m_x, m_y + v.m_y); }
      inline vector_2d_base operator-(const vector_2d_base& v) const noexcept { return vector_2d_base(m_x - v.m_x, m_y - v.m_y); }
      friend vector_2d_base operator*(float k, const vector_2d_base& v) { return v * k; }
      inline vector_2d_base operator-(void) const noexcept { return vector_2d_base(-m_x, -m_y); }

      inline vector_2d_base& operator/=(const float scalar) noexcept
      {
        *this = *this / scalar;
        return *this;
      }

      inline vector_2d_base& operator*=(const float scalar) noexcept
      {
        *this = *this * scalar;
        return *this;
      }

      inline vector_2d_base& operator+=(const vector_2d_base& v) noexcept
      {
        *this = *this + v;
        return *this;
      }

      inline vector_2d_base& operator-=(const vector_2d_base& v) noexcept
      {

        *this = *this - v;
        return *this;
      }

      inline float length() const noexcept { return std::sqrt(m_x * m_x + m_y * m_y); }
      inline vector_2d_base& normalize() noexcept
      {
        auto len = length();
        if (len != 0.0f)
        {
          (*this) *= (1.0f / len);
        }
        return *this;
      }

      inline vector_2d_base direction() const noexcept { return vector_2d_base(*this).normalize(); }

      inline float angle() const noexcept { return angle(vector_2d_base(1, 1)); }
      inline float angle(const vector_2d_base& other) const noexcept
      {
        auto scalar = scalar_product(other);
        auto cross = cross_product(other);

        return std::atan2(cross, scalar);
      }

      inline vector_2d_base& rotate(float angle)
      {
        value_type tmp_x = m_x;
        m_x = m_x * std::cos(angle) - m_y * std::sin(angle);
        m_y = tmp_x * std::sin(angle) + m_y * std::cos(angle);
        return *this;
      }

      inline vector_2d_base& rotate(const vector_2d_base& center, float angle) noexcept
      {
        auto tmp = vector_2d_base(*this - center).rotate(angle);
        *this = center + tmp;
        return *this;
      }

      inline vector_2d_base& clamp(const vector_2d_base& min, const vector_2d_base& max)
      {
        m_x = malefica::clamp(m_x, min.m_x, max.m_x);
        m_y = malefica::clamp(m_y, min.m_y, max.m_y);
        return *this;
      }

      inline void swap(vector_2d_base& other)
      {
        using std::swap;
        swap(m_x, other.m_x);
        swap(m_y, other.m_y);
      }

    private:
      value_type m_x;
      value_type m_y;
    };

    template <typename T>
    inline void swap(vector_2d_base<T>& lhs, vector_2d_base<T>& rhs)
    {
      lhs.swap(rhs);
    }

    template <typename T>
    vector_2d_base<T>& clamp(vector_2d_base<T>& vec, const vector_2d_base<T>& min, const vector_2d_base<T>& max)
    {
      return vec.clamp(min, max);
    }

    typedef vector_2d_base<float> vector_2d;

  } // namespace math

} // namespace malefica

#endif // MALEFICA_MATH_VECTOR_2D_HXX
