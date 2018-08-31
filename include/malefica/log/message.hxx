#ifndef MALEFICA_DEBUG_MESSAGE_HXX
#define MALEFICA_DEBUG_MESSAGE_HXX

#include "formatter.hxx"

#include <malefica/types.hxx>

#include <string>

namespace malefica
{
  namespace log
  {
    enum class category : int
    {
      general,
      app,
      engine,
      files,
      error,
      assert,
      profile,
      test
    };

    enum class level : std::int16_t
    {
      trace,
      debug,
      info,
      warning,
      error,
      fatal
    };

    inline std::string to_string(category c) noexcept
    {
      std::string category_string("app");
      switch (c)
      {
        case category::general:
          category_string = "general";
          break;
        case category::app:
          category_string = "app";
          break;
        case category::engine:
          category_string = "engine";
          break;
        case category::files:
          category_string = "files";
          break;
        case category::error:
          category_string = "error";
          break;
        case category::assert:
          category_string = "assert";
          break;
        case category::profile:
          category_string = "profile";
          break;
        case category::test:
          category_string = "test";
          break;
      }
      return category_string;
    }

    inline std::string to_string(level l) noexcept
    {
      std::string level_string("info");
      switch (l)
      {
        case level::trace:
          level_string = "trace";
          break;
        case level::debug:
          level_string = "debug";
          break;
        case level::info:
          level_string = "info";
          break;
        case level::warning:
          level_string = "warning";
          break;
        case level::error:
          level_string = "error";
          break;
        case level::fatal:
          level_string = "fatal";
          break;
      }
      return level_string;
    }

    class message
    {
    public:
      message() noexcept : m_level(level::trace), m_category(category::general), m_message() {}

      message(level l, const std::string& msg) : m_level(l), m_category(category::general), m_message(msg) {}
      message(level l, category c, const std::string& msg) : m_level(l), m_category(c), m_message(msg) {}

      message(const message& msg) : m_level(msg.m_level), m_category(msg.m_category), m_message(msg.m_message) {}
      message(message&& msg) : m_level(std::move(msg.m_level)), m_category(std::move(msg.m_category)), m_message(std::move(msg.m_message)) {}

      inline message& operator=(const message& other)
      {
        message(other).swap(*this);
        return *this;
      }

      inline message& operator=(message&& other)
      {
        message(std::move(other)).swap(*this);
        return *this;
      }

      inline level get_level() const noexcept { return m_level; }
      inline category get_category() const noexcept { return m_category; }
      inline std::string get_message() const noexcept { return m_message; }

      inline void swap(message& rhs) noexcept
      {
        using std::swap;
        swap(m_level, rhs.m_level);
        swap(m_category, rhs.m_category);
        swap(m_message, rhs.m_message);
      }

      inline bool equals(const message& other) const noexcept
      {
        return (m_level == other.m_level) && (m_message == other.m_message) && (m_category == other.m_category);
      }

    private:
      level m_level;
      category m_category;
      std::string m_message;
    };

    inline bool operator==(const message& lhs, const message& rhs) { return lhs.equals(rhs); }
    inline bool operator!=(const message& lhs, const message& rhs) { return !(lhs == rhs); }

    namespace detail
    {
      template <typename... Args>
      static inline message create_message(const char* file, const char* func, int line, const std::string& fmt, const Args&... args)
      {
        return message{malefica::log::level::info, malefica::log::detail::create_function_prefix(file, func, line) + malefica::log::format(fmt, args...)};
      }

      template <typename... Args>
      static inline message create_message(const char* file, const char* func, int line, level level, const std::string& fmt, const Args&... args)
      {
        return message{level, malefica::log::detail::create_function_prefix(file, func, line) + malefica::log::format(fmt, args...)};
      }

      template <typename... Args>
      static inline message
      create_message(const char* file, const char* func, int line, category channel, level level, const std::string& fmt, const Args&... args)
      {
        return message{level, channel, malefica::log::detail::create_function_prefix(file, func, line) + malefica::log::format(fmt, args...)};
      }
    } // namespace detail

  } // namespace log

} // namespace malefica

#endif // MALEFICA_DEBUG_MESSAGE_HXX