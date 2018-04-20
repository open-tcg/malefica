#include <malefica/log/logger.hxx>

namespace malefica
{
  namespace log
  {

    static_logger& static_logger::instance()
    {
      static static_logger l;
      return l;
    }

    static_logger::static_logger() : m_dispatcher(){};
    static_logger::~static_logger() {}

    void static_logger::log(const message& msg) { m_dispatcher.send_message(msg); }
    void static_logger::log(message&& msg) { m_dispatcher.send_message(std::move(msg)); }

    void static_logger::register_sink(message_sink_base* sink_ptr) { m_dispatcher.register_sink(sink_ptr); }
    void static_logger::remove_all_sinks() { m_dispatcher.remove_all_sinks(); }

  } // log
} // malefica