#ifndef MALEFICA_THREAD_QUEUE_HXX
#define MALEFICA_THREAD_QUEUE_HXX

#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

namespace malefica
{
  namespace thread
  {
    template <typename T>
    class queue final
    {
    public:
      typedef T value_type;
      typedef std::queue<value_type> container_type;
      typedef typename container_type::size_type size_type;

      queue() : m_container(), m_mutex(), m_condition(), m_processing_stopped(false){};
      queue(const queue&) = delete;
      queue& operator=(const queue&) = delete;

      ~queue() { stop(); }

      void push(const value_type& val)
      {
        value_type tmp(val);
        push(std::move(tmp));
      }

      void push(value_type&& val)
      {
        {
          std::unique_lock<std::mutex> lock(m_mutex);
          m_container.push(std::move(val));
        }

        m_condition.notify_one();
      }

      T pop()
      {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (m_container.empty() && !m_processing_stopped)
        {
          m_condition.wait(lock);
        }

        if (m_processing_stopped) return T();

        auto val = m_container.front();
        m_container.pop();
        return val;
      }

      inline void stop()
      {
        {
          std::unique_lock<std::mutex> lock(m_mutex);
          m_processing_stopped = true;
        }
        m_condition.notify_all();
      }

    private:
      container_type m_container;

      std::mutex m_mutex;
      std::condition_variable m_condition;
      bool m_processing_stopped;
    };
  } /*thread*/
} /*malefica*/

#endif /*MALEFICA_THREAD_QUEUE_HXX*/
