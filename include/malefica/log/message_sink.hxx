#ifndef MALEFICA_LOG_MESSAGE_SINK_HXX
#define MALEFICA_LOG_MESSAGE_SINK_HXX

#include <malefica/log/message.hxx>

namespace malefica
{
  namespace log
  {
    class message_sink_base
    {
    public:
      virtual ~message_sink_base() {}

      virtual void process_message(const message& msg) = 0;
    };

    class stdout_sink : public message_sink_base
    {
    public:
      stdout_sink() = default;
      virtual ~stdout_sink() = default;

      virtual void process_message(const message& msg) override;
    };

  } /*log*/
} /*malefica*/

#endif /*MALEFICA_LOG_MESSAGE_SINK_HXX*/