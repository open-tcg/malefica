#ifndef MALEFICA_UNIT_TESTS_MOCKS_MESSAGE_CONTAINER_HXX
#define MALEFICA_UNIT_TESTS_MOCKS_MESSAGE_CONTAINER_HXX

#include <malefica/log/message.hxx>
#include <malefica/log/message_sink.hxx>

#include <mutex>
#include <vector>

namespace mocks
{
  class message_container
  {
    typedef std::recursive_mutex mutex_type;

  public:
    typedef std::vector<malefica::log::message> container_type;
    typedef typename container_type::size_type size_type;

    inline void push_back(malefica::log::category category, malefica::log::level level, const std::string& msg)
    {
      std::scoped_lock<mutex_type> lock(m_mutex);
      m_container.push_back(malefica::log::message{level, category, msg});
    }

    inline void push_back(const malefica::log::message& msg)
    {
      std::scoped_lock<mutex_type> lock(m_mutex);
      m_container.push_back(msg);
    }

    inline const malefica::log::message& at(size_type idx) const
    {
      std::scoped_lock<mutex_type> lock(m_mutex);
      return m_container.at(idx);
    }

    inline bool empty() const noexcept
    {
      std::scoped_lock<mutex_type> lock(m_mutex);
      return m_container.empty();
    }

    inline size_type size() const noexcept
    {
      std::scoped_lock<mutex_type> lock(m_mutex);
      return m_container.size();
    }

    inline void clear()
    {
      std::scoped_lock<mutex_type> lock(m_mutex);
      m_container.clear();
    }

    inline bool equal(const container_type& other) const noexcept
    {
      std::scoped_lock<mutex_type> lock(m_mutex);
      return m_container == other;
    }
    inline bool equal(const message_container& other) const noexcept
    {
      std::scoped_lock<mutex_type> lock(m_mutex);
      return equal(other.m_container);
    }

    message_container() : m_container(), m_mutex() {}

  private:
    container_type m_container;
    mutable mutex_type m_mutex;
  };

  inline bool operator==(const message_container& lhs, const message_container::container_type& rhs) { return lhs.equal(rhs); }
  inline bool operator==(const message_container::container_type& lhs, const message_container& rhs) { return rhs == lhs; }
  inline bool operator==(const message_container& lhs, const message_container& rhs) { return lhs.equal(rhs); }

  inline bool operator!=(const message_container& lhs, const message_container::container_type& rhs) { return !(lhs == rhs); }
  inline bool operator!=(const message_container::container_type& lhs, const message_container& rhs) { return !(lhs == rhs); }
  inline bool operator!=(const message_container& lhs, const message_container& rhs) { return !(lhs == rhs); }

  class message_sink : public malefica::log::message_sink_base
  {
  public:
    message_sink(message_container& container) : m_container(container) {}
    ~message_sink() = default;

    virtual inline void process_message(const malefica::log::message& msg) override { m_container.push_back(msg); }

  private:
    message_container& m_container;
  };
}

#endif /*MALEFICA_UNIT_TESTS_MOCKS_MESSAGE_CONTAINER_HXX*/
