#ifndef MALEFICA_MGE_LOG_LOGGING_HXX
#define MALEFICA_MGE_LOG_LOGGING_HXX

#include <spdlog/spdlog.h>

#include "message.hxx"

#include <malefica/mge/types.hxx>

namespace mge
{
  namespace log
  {
    namespace detail
    {
      using logger_ptr = std::shared_ptr<spdlog::logger>;

      inline logger_ptr get_logger(category type) noexcept
      {
        std::string logger_name(to_string(type));
        auto logger = spdlog::get(logger_name);
        if (logger == nullptr)
        {
          logger = spdlog::stdout_color_mt(logger_name);
          logger->set_level(spdlog::level::trace);
        }
        return logger;
      }

      inline spdlog::level::level_enum get_level(level l) noexcept
      {
        spdlog::level::level_enum spd_level = spdlog::level::off;

        switch (l)
        {
          case level::trace:
            spd_level = spdlog::level::trace;
            break;
          case level::debug:
            spd_level = spdlog::level::debug;
            break;
          case level::info:
            spd_level = spdlog::level::info;
            break;
          case level::warning:
            spd_level = spdlog::level::warn;
            break;
          case level::error:
            spd_level = spdlog::level::err;
            break;
          case level::fatal:
            spd_level = spdlog::level::critical;
            break;
        }

        return spd_level;
      }
    } // namespace detail

    class static_logger final
    {
      struct log_creater final
      {
      public:
        log_creater() : m_message() {}
        log_creater(log_creater&&) = default;
        log_creater(const log_creater&) = delete;

        ~log_creater() { static_logger::log(message(m_level, m_category, m_message)); }

        log_creater& operator<<(category c)
        {
          m_category = c;
          return *this;
        }

        log_creater& operator<<(level p)
        {
          m_level = p;
          return *this;
        }

        template <typename T>
        log_creater& operator<<(T&& entry)
        {
          std::ostringstream ss;
          ss << std::forward<T>(entry);
          m_message.append(ss.str());

          return *this;
        }

        template <typename T>
        log_creater& operator<<(const T& entry)
        {
          std::ostringstream ss;
          ss << entry;
          m_message.append(ss.str());

          return *this;
        }

      private:
        std::string m_message;
        category m_category = category::app;
        level m_level = level::info;
      };

    public:
      static inline void log(const message& msg)
      {
        auto logger = detail::get_logger(msg.get_category());
        logger->log(detail::get_level(msg.get_level()), msg.get_message());
      }

      static inline log_creater out() { return log_creater{}; }

    private:
      static_logger() = delete;
      ~static_logger() = delete;

      static_logger(const static_logger&) = delete;
      static_logger& operator=(const static_logger&) = delete;

      static_logger(static_logger&&) = delete;
      static_logger& operator=(static_logger&&) = delete;
    };

    inline void set_level(level l) { spdlog::set_level(detail::get_level(l)); }
    inline void set_level(category c, level l) { detail::get_logger(c)->set_level(detail::get_level(l)); }

  } // namespace log

} // namespace mge

#ifndef MGE_LOG
#define MGE_LOG() ::mge::log::static_logger::out() << ::mge::log::detail::create_function_prefix(__FILE__, __FUNCTION__, __LINE__)
#endif // MGE_LOG

#ifndef MGE_PRINTF
#define MGE_PRINTF(...) ::mge::log::static_logger::log(::mge::log::detail::create_message(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__));
#endif // MGE_PRINTF

// MGE_LOG() << wge::log::category::test << wge::log::level::fatal << "test message";
// MGE_PRINTF(wge::log::level::info, "this %s a multi parameter %s with %i parameters", "is", "string", 3);

#endif /* MALEFICA_MGE_LOG_LOGGING_HXX */
