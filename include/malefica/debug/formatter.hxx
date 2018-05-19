#ifndef MALEFICA_DEBUG_FORMATTER_HXX
#define MALEFICA_DEBUG_FORMATTER_HXX

#include <tinyformat.h>

namespace malefica
{
  namespace debug
  {
    namespace detail
    {
      inline std::string format(const std::string& fmt) noexcept { return fmt; }

      template <typename... Args>
      std::string format(const std::string& format, const Args&... args) noexcept
      {
        return tfm::format(format.c_str(), args...);
      }

      inline std::string create_basename_from_path(const std::string& path)
      {
        std::string base_path = path.substr(path.find_last_of("/\\") + 1);
        return base_path.substr(0, base_path.find_last_of('.'));
      }

      inline std::string create_function_prefix(const char* file, const char* func, int line)
      {
        std::ostringstream buf;
        buf << "[" << create_basename_from_path(file) << "::" << func << "].(" << line << ") ";
        return buf.str();
      }

    } // namespace detail

    template <typename... Args>
    inline std::string format(const std::string& fmt, const Args&... args) noexcept
    {
      return detail::format(fmt, args...);
    }

    inline std::string format(const std::string& fmt) noexcept { return detail::format(fmt); }

  } // namespace debug

} // namespace malefica

#endif /*MALEFICA_DEBUG_FORMATTER_HXX*/