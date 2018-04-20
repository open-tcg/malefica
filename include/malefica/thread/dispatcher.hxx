#ifndef MALEFICA_THREAD_DISPATCHER_HXX
#define MALEFICA_THREAD_DISPATCHER_HXX

#include <malefica/thread/queue.hxx>

#include <memory>
#include <thread>

namespace malefica
{
  namespace thread
  {

    template <class T>
    class dispatcher
    {
    public:
      typedef T value_type;
      typedef queue<value_type> container_type;

      dispatcher() : m_container(), m_worker_thread(&dispatcher::process_event_skeleton, this), m_processing_mutex(), m_stop_thread(false) {}
      virtual ~dispatcher()
      {
        m_stop_thread = true;
        m_container.stop();
        if (m_worker_thread.joinable()) m_worker_thread.join();
      }

      void queue_event(const value_type& val) { m_container.push(val); }
      void queue_event(value_type&& val) { m_container.push(std::move(val)); }

    protected:
      virtual void process_event(value_type&& value) = 0;

    private:
      void process_event_skeleton()
      {
        while (!m_stop_thread)
        {
          value_type value = m_container.pop();
          if (m_stop_thread) return;

          {
            std::scoped_lock<std::recursive_mutex> lock(m_processing_mutex);
            process_event(std::move(value));
          }
        }
      }

      container_type m_container;
      std::thread m_worker_thread;
      mutable std::recursive_mutex m_processing_mutex;
      bool m_stop_thread;
    };

  } /*concurrency*/
} /*malefica*/

#endif /* MALEFICA_THREAD_DISPATCHER_HXX */