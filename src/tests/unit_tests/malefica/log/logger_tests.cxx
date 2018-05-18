#include <malefica/log/logger.hxx>

#include "../mocks/message_container.hxx"

#include <chrono>
#include <thread>

#include <catch.hpp>

struct message_content
{
  malefica::log::category category;
  malefica::log::level level;
  std::string msg;
};

TEST_CASE("test log macro", "[log]")
{
  using namespace std::chrono_literals;
  constexpr auto sleep_time = 10ms;

  SECTION("test macro without channel")
  {
    malefica::log::static_logger::instance().remove_all_sinks();
    mocks::message_container message_container;
    malefica::log::static_logger::instance().register_sink(new mocks::message_sink(message_container));

    std::vector<message_content> content{message_content{malefica::log::category::application, malefica::log::level::debug, "debug test message"},
                                         message_content{malefica::log::category::application, malefica::log::level::trace, "trace test message"},
                                         message_content{malefica::log::category::application, malefica::log::level::error, "error test message"}};

    for (auto& data : content)
    {
      MALEFICA_PRINTF(data.level, data.msg);
    }

    std::this_thread::sleep_for(sleep_time);

    REQUIRE(message_container.size() == content.size());
    for (mocks::message_container::size_type idx = 0; idx < content.size(); ++idx)
    {
      auto message_under_test = message_container.at(idx);
      REQUIRE(message_under_test.get_category() == malefica::log::category::application);
      REQUIRE(message_under_test.get_level() == content.at(idx).level);
      REQUIRE_THAT(message_under_test.get_message(), Catch::Matchers::EndsWith(content.at(idx).msg));
    }

    malefica::log::static_logger::instance().remove_all_sinks();
  }

  SECTION("test printf like macro call")
  {
    malefica::log::static_logger::instance().remove_all_sinks();
    mocks::message_container message_container;
    malefica::log::static_logger::instance().register_sink(new mocks::message_sink(message_container));

    MALEFICA_PRINTF(malefica::log::level::info, "this %s a multi parameter %s with %i parameters", "is", "string", 3);
    std::this_thread::sleep_for(sleep_time);

    REQUIRE(message_container.size() == 1);

    auto message_under_test = message_container.at(0);
    REQUIRE(message_under_test.get_category() == malefica::log::category::application);
    REQUIRE(message_under_test.get_level() == malefica::log::level::info);
    REQUIRE_THAT(message_under_test.get_message(), Catch::Matchers::EndsWith("this is a multi parameter string with 3 parameters"));

    malefica::log::static_logger::instance().remove_all_sinks();
  }

  SECTION("test printf like macro call with category")
  {
    malefica::log::static_logger::instance().remove_all_sinks();
    mocks::message_container message_container;
    malefica::log::static_logger::instance().register_sink(new mocks::message_sink(message_container));

    const auto category = malefica::log::category::system;

    MALEFICA_PRINTF(category, malefica::log::level::info, "testing %i %s like %s", 1, "printf", "message");
    std::this_thread::sleep_for(sleep_time);

    REQUIRE(message_container.size() == 1);

    auto message_under_test = message_container.at(0);
    REQUIRE(message_under_test.get_category() == category);
    REQUIRE(message_under_test.get_level() == malefica::log::level::info);
    REQUIRE_THAT(message_under_test.get_message(), Catch::Matchers::EndsWith("testing 1 printf like message"));

    malefica::log::static_logger::instance().remove_all_sinks();
  }

  SECTION("test stream like macro call")
  {
    malefica::log::static_logger::instance().remove_all_sinks();
    mocks::message_container message_container;
    malefica::log::static_logger::instance().register_sink(new mocks::message_sink(message_container));

    const auto category = malefica::log::category::render;
    const auto level = malefica::log::level::trace;

    MALEFICA_LOG() << category << "test string " << 3 << level;

    std::this_thread::sleep_for(sleep_time);

    REQUIRE(message_container.size() == 1);

    auto message_under_test = message_container.at(0);
    REQUIRE(message_under_test.get_category() == category);
    REQUIRE(message_under_test.get_level() == level);
    REQUIRE_THAT(message_under_test.get_message(), Catch::Matchers::EndsWith("test string 3"));

    malefica::log::static_logger::instance().remove_all_sinks();
  }
}