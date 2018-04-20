#ifndef MALEFICA_LOG_LOGGER_HXX
#define MALEFICA_LOG_LOGGER_HXX

#include <malefica/log/message.hxx>
#include <malefica/log/message_dispatcher.hxx>
#include <malefica/log/message_sink.hxx>

#include <sstream>

namespace malefica
{
  namespace log
  {
    class message_dispatcher;

    class static_logger final
    {
      struct log_creater final
      {
      public:
        log_creater() : m_message() {}
        log_creater(log_creater&&) = default;
        log_creater(const log_creater&) = delete;

        ~log_creater() { static_logger::instance().log(message(m_level, m_category, m_message)); }

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
        category m_category = category::application;
        level m_level = level::info;
      };

    public:
      static static_logger& instance();

      void log(const message& msg);
      void log(message&& msg);

      void register_sink(message_sink_base* sink_ptr);
      void remove_all_sinks();

      static inline auto out() { return log_creater{}; }

    private:
      static_logger();
      ~static_logger();

      static_logger(const static_logger&) = delete;
      static_logger& operator=(const static_logger&) = delete;

      static_logger(static_logger&&) = delete;
      static_logger& operator=(static_logger&&) = delete;

      message_dispatcher m_dispatcher;
    };

  } // log
} // malefica

#ifndef MALEFICA_LOG
#define MALEFICA_LOG() ::malefica::log::static_logger::out() << ::malefica::log::detail::create_function_prefix(__FILE__, __FUNCTION__, __LINE__)
#endif // MALEFICA_LOG

#ifndef MALEFICA_PRINTF
#define MALEFICA_PRINTF(...) ::malefica::log::static_logger::instance().log(::malefica::log::detail::create_message(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__));
#endif // MALEFICA_PRINTF

#endif /*MALEFICA_LOG_LOGGER_HXX*/