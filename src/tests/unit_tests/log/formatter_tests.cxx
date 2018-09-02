#include <malefica/mge/log/formatter.hxx>

#include <catch.hpp>

#include <string>

TEST_CASE("test printf like string formation", "[log][mge]")
{
  SECTION("test formatting of a string without placeholders")
  {
    const std::string input("test string");
    REQUIRE_THAT(mge::log::format(input), Catch::Matchers::Equals(input));
  }

  SECTION("test formatting of a string with integer placeholder")
  {
    const std::string input("test sting with integer: ");
    const std::string placeholder("%i");
    const int val = 42;

    REQUIRE_THAT(mge::log::format(input + placeholder, val), Catch::Matchers::Equals(input + std::to_string(val)));
  }

  SECTION("test formatting of a string with string placeholder")
  {
    const std::string input("test sting with string: ");
    const std::string placeholder("%s");
    const std::string val("value");

    REQUIRE_THAT(mge::log::format(input + placeholder, val.c_str()), Catch::Matchers::Equals(input + val));
  }

  SECTION("test formatting of a string placeholder with placeholder like value")
  {
    const std::string input("test sting with string: ");
    const std::string placeholder("%s");
    const std::string val("%s");

    REQUIRE_THAT(mge::log::format(input + placeholder, val.c_str()), Catch::Matchers::Equals(input + val));
  }

  SECTION("test formatting of a string multiple placeholders")
  {
    const std::string input("test sting with string: ");
    const std::string placeholder_1("%s");
    const std::string val_1("value");
    const std::string middle_part(" and ");
    const std::string placeholder_2("%i");
    const int val_2(42);

    const std::string placeholder_input(input + placeholder_1 + middle_part + placeholder_2);
    const std::string expected_result(input + val_1 + middle_part + std::to_string(val_2));

    REQUIRE_THAT(mge::log::format(placeholder_input, val_1.c_str(), val_2), Catch::Matchers::Equals(expected_result));
  }
}
