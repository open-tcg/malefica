
#include <malefica/log/message.hxx>

#include <catch.hpp>

#include <utility>

TEST_CASE("test debug message structure", "[log][core]")
{

  SECTION("test message creation with channel")
  {
    auto msg = malefica::log::detail::create_message(
        __FILE__, __FUNCTION__, __LINE__, malefica::log::category::test, malefica::log::level::error, "test %s message", "first");
    REQUIRE(msg.get_level() == malefica::log::level::error);
    REQUIRE(msg.get_category() == malefica::log::category::test);

    auto msg_string = msg.get_message();
    REQUIRE_THAT(msg_string, Catch::Matchers::Contains("test first message"));
  }

  SECTION("test message creation without channel")
  {
    auto msg = malefica::log::detail::create_message(__FILE__, __FUNCTION__, __LINE__, malefica::log::level::error, "test %ind message", 2);
    REQUIRE(msg.get_level() == malefica::log::level::error);
    REQUIRE(msg.get_category() == malefica::log::category::general);

    auto msg_string = msg.get_message();
    REQUIRE_THAT(msg_string, Catch::Matchers::Contains("test 2nd message"));
  }

  SECTION("test message copy and assignment")
  {
    auto msg = malefica::log::detail::create_message(__FILE__, __FUNCTION__, __LINE__, "test %s message", "copy");
    REQUIRE(msg.get_level() == malefica::log::level::info);
    REQUIRE(msg.get_category() == malefica::log::category::general);
    REQUIRE_THAT(msg.get_message(), Catch::Matchers::Contains("test copy message"));

    malefica::log::message msg_copy(msg);
    REQUIRE(msg_copy == msg);

    auto new_msg = malefica::log::detail::create_message(__FILE__, __FUNCTION__, __LINE__, "this is a new message");
    REQUIRE(new_msg.get_level() == malefica::log::level::info);
    REQUIRE(new_msg.get_category() == malefica::log::category::general);
    REQUIRE_THAT(new_msg.get_message(), Catch::Matchers::Contains("this is a new message"));

    msg_copy = new_msg;
    REQUIRE(msg_copy == new_msg);

    new_msg = malefica::log::detail::create_message(__FILE__, __FUNCTION__, __LINE__, "test %s message", "other");
    REQUIRE(new_msg != msg_copy);
  }

  SECTION("test message move")
  {
    auto msg = malefica::log::detail::create_message(__FILE__, __FUNCTION__, __LINE__, "test message move");
    REQUIRE(msg.get_level() == malefica::log::level::info);
    REQUIRE(msg.get_category() == malefica::log::category::general);
    REQUIRE_THAT(msg.get_message(), Catch::Matchers::Contains("test message move"));

    malefica::log::message msg_move(std::move(msg));
    REQUIRE(msg_move.get_level() == malefica::log::level::info);
    REQUIRE(msg_move.get_category() == malefica::log::category::general);
    REQUIRE_THAT(msg_move.get_message(), Catch::Matchers::Contains("test message move"));

    msg = std::move(msg_move);
    REQUIRE(msg.get_level() == malefica::log::level::info);
    REQUIRE(msg.get_category() == malefica::log::category::general);
    REQUIRE_THAT(msg.get_message(), Catch::Matchers::Contains("test message move"));
  }
}
