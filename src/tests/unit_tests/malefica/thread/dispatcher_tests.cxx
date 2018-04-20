#include <malefica/thread/dispatcher.hxx>

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

#include <catch.hpp>

class test_dispatcher final : public malefica::thread::dispatcher<int>
{
public:
  test_dispatcher() : malefica::thread::dispatcher<int>(), m_counter(0) {}

  unsigned int processed_events() const { return m_counter; }

protected:
  virtual void process_event(int&&) override { ++m_counter; }

private:
  unsigned int m_counter;
};

TEST_CASE("test dispatcher processing", "[thread]")
{
  using namespace std::chrono_literals;

  SECTION("testing simple dispatcher processing")
  {
    test_dispatcher dispatcher{};

    unsigned int event_count = 5;
    for (unsigned int i = 0; i < event_count; ++i)
    {
      dispatcher.queue_event(i);
    }

    std::this_thread::sleep_for(6ms);
    REQUIRE(dispatcher.processed_events() == event_count);
  }
}