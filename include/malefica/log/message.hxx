#ifndef MALEFICA_LOG_MESSAGE_HXX
#define MALEFICA_LOG_MESSAGE_HXX

#include <malefica/log/formatter.hxx>

#include <cstdint>
#include <string>

namespace malefica
{
  namespace log
  {
    enum class category : int
    {
      application,
      error,
      assert,
      system,
      audio,
      render,
      video,
      input,
      network,
      ai,
      profiling,
      test,
      malefica
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

    class message
    {
    public:
      message() noexcept : m_level(level::trace), m_category(), m_message() {}

      message(level l, const std::string& msg) : m_level(l), m_category(category::application), m_message(msg) {}
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
        return message{malefica::log::level::info, create_function_prefix(file, func, line) + format(fmt, args...)};
      }

      template <typename... Args>
      static inline message create_message(const char* file, const char* func, int line, level level, const std::string& fmt, const Args&... args)
      {
        return message{level, create_function_prefix(file, func, line) + format(fmt, args...)};
      }

      template <typename... Args>
      static inline message
      create_message(const char* file, const char* func, int line, category channel, level level, const std::string& fmt, const Args&... args)
      {
        return message{level, channel, create_function_prefix(file, func, line) + format(fmt, args...)};
      }
    }

  } /*log*/

} /*malefica*/

#endif /*MALEFICA_LOG_MESSAGE_HXX*/