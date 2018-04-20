#ifndef MALEFICA_LOG_MESSAGE_DISPATCHER_HXX
#define MALEFICA_LOG_MESSAGE_DISPATCHER_HXX

#include <malefica/thread/dispatcher.hxx>

#include <malefica/log/message.hxx>
#include <malefica/log/message_sink.hxx>

#include <algorithm>
#include <memory>
#include <mutex>

namespace malefica
{
  namespace log
  {
    class message_dispatcher : private thread::dispatcher<message>
    {
    public:
      typedef std::unique_ptr<message_sink_base> sink_ptr_type;

      message_dispatcher() : thread::dispatcher<message>(), m_mutex(), m_sinks() {}

      void send_message(const message& msg) { queue_event(msg); }
      void send_message(message&& msg) { queue_event(std::move(msg)); }

      void register_sink(message_sink_base* sink_ptr)
      {
        if (sink_ptr)
        {
          std::scoped_lock<std::recursive_mutex> lock(m_mutex);
          m_sinks.push_back(sink_ptr_type(sink_ptr));
        }
      };

      void remove_all_sinks()
      {
        std::scoped_lock<std::recursive_mutex> lock(m_mutex);
        m_sinks.clear();
      }

    protected:
      virtual void process_event(message&& msg) override
      {
        std::scoped_lock<std::recursive_mutex> lock(m_mutex);
        std::for_each(m_sinks.begin(), m_sinks.end(), [msg](sink_ptr_type& sink) {
          if (sink) sink->process_message(msg);
        });
      }

    private:
      std::recursive_mutex m_mutex;
      std::vector<sink_ptr_type> m_sinks;
    };

  } /*log*/
} /*malefica*/

#endif /*MALEFICA_LOG_MESSAGE_DISPATCHER_HXX*/