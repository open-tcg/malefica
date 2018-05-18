#include <malefica/log/message_dispatcher.hxx>

#include <catch.hpp>

#include <chrono>
#include <thread>

#include <iostream>

class test_message_sink : public malefica::log::message_sink_base
{
public:
  typedef std::vector<malefica::log::message> container_type;

  explicit test_message_sink(container_type& container) : malefica::log::message_sink_base(), m_container(container) {}

  virtual void process_message(const malefica::log::message& msg) override final { m_container.push_back(msg); }

private:
  container_type& m_container;
};

#ifndef TEST_LOG_MACRO
#define TEST_LOG_MACRO(...) malefica::log::detail::create_message(__FILE__, __FUNCTION__, __LINE__, __VA_ARGS__);
#endif // TEST_LOG_MACRO

TEST_CASE("test dispatcher for log messages", "[log]")
{
  using container_type = typename test_message_sink::container_type;

  SECTION("test message creation with channel")
  {
    auto msg =
        malefica::log::detail::create_message(__FILE__, __FUNCTION__, __LINE__, malefica::log::category::input, malefica::log::level::error, "test %s message", "first");
    REQUIRE(msg.get_level() == malefica::log::level::error);
    REQUIRE(msg.get_category() == malefica::log::category::input);

    auto msg_string = msg.get_message();
    REQUIRE_THAT(msg_string, Catch::Matchers::EndsWith("test first message"));
  }

  SECTION("test message creation without channel")
  {
    auto msg = malefica::log::detail::create_message(__FILE__, __FUNCTION__, __LINE__, malefica::log::level::error, "test %ind message", 2);
    REQUIRE(msg.get_level() == malefica::log::level::error);
    REQUIRE(msg.get_category() == malefica::log::category::application);

    auto msg_string = msg.get_message();
    REQUIRE_THAT(msg_string, Catch::Matchers::EndsWith("test 2nd message"));
  }

  SECTION("test message creation with macros")
  {
    auto msg = TEST_LOG_MACRO(malefica::log::level::debug, "test without channel");
    REQUIRE(msg.get_level() == malefica::log::level::debug);
    REQUIRE(msg.get_category() == malefica::log::category::application);

    auto msg_string = msg.get_message();
    REQUIRE_THAT(msg_string, Catch::Matchers::Contains("test without channel"));
  }

  SECTION("test channel based message creation with macros")
  {
    auto msg = TEST_LOG_MACRO(malefica::log::category::render, malefica::log::level::debug, "test %s channel", "with");
    REQUIRE(msg.get_level() == malefica::log::level::debug);
    REQUIRE(msg.get_category() == malefica::log::category::render);

    auto msg_string = msg.get_message();
    REQUIRE_THAT(msg_string, Catch::Matchers::Contains("test with channel"));
  }

  using namespace std::chrono_literals;
  constexpr auto sleep_time = 20ms;

  SECTION("test message dispatcher creation")
  {
    container_type msg_container;
    malefica::log::message_dispatcher dispatcher;

    dispatcher.register_sink(new test_message_sink(msg_container));

    const malefica::log::message msg{malefica::log::level::debug, malefica::log::category::application, "test_message"};
    dispatcher.send_message(msg);

    std::this_thread::sleep_for(sleep_time);

    REQUIRE_FALSE(msg_container.empty());
    REQUIRE(msg_container.front() == msg);
  }

  SECTION("test message dispatcher multi message input")
  {
    container_type msg_container;
    malefica::log::message_dispatcher dispatcher;

    dispatcher.register_sink(new test_message_sink(msg_container));

    const malefica::log::message first_msg{malefica::log::level::debug, malefica::log::category::render, "test_message"};
    const malefica::log::message second_msg{malefica::log::level::info, malefica::log::category::system, "2nd_test_message"};

    dispatcher.send_message(malefica::log::message{first_msg});
    dispatcher.send_message(malefica::log::message{second_msg});

    std::this_thread::sleep_for(sleep_time);

    REQUIRE_FALSE(msg_container.empty());
    REQUIRE(msg_container.size() == 2);
    REQUIRE(msg_container.at(0) == first_msg);
    REQUIRE(msg_container.at(1) == second_msg);
  }

  SECTION("test message dispatcher with multiple sinks")
  {
    container_type first_msg_container;
    container_type second_msg_container;
    malefica::log::message_dispatcher dispatcher;

    dispatcher.register_sink(new test_message_sink(first_msg_container));
    dispatcher.register_sink(new test_message_sink(second_msg_container));

    const malefica::log::message first_msg{malefica::log::level::debug, "test_message"};
    const malefica::log::message second_msg{malefica::log::level::info, "2nd_test_message"};

    dispatcher.send_message(malefica::log::message{malefica::log::level::fatal, malefica::log::category::assert, "test fatal message"});
    dispatcher.send_message(malefica::log::message{malefica::log::level::info, malefica::log::category::test, "test info message"});
    dispatcher.send_message(malefica::log::message{malefica::log::level::trace, malefica::log::category::application, "test trace message"});
    dispatcher.send_message(malefica::log::message{malefica::log::level::debug, malefica::log::category::error, "test debug message"});

    std::this_thread::sleep_for(sleep_time);
    REQUIRE(first_msg_container == second_msg_container);
  }
}