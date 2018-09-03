#include <malefica/mge/exception.hxx>
#include <malefica/mtg/mana_cost.hxx>

#include <catch.hpp>

TEST_CASE("testing mana cost", "[mana][mtg]")
{
  SECTION("test no cost mana cost")
  {
    auto cost = mtg::mana_cost::from_string("");
    REQUIRE(cost.no_cost());

    REQUIRE_FALSE(cost.has_blue());
  }

  SECTION("test simple mana creation from string")
  {
    {
      auto cost = mtg::mana_cost::from_string("{G}");
      REQUIRE(cost.has_green());
      REQUIRE(cost.converted() == 1);

      REQUIRE_FALSE(cost.has_white());
      REQUIRE_FALSE(cost.no_cost());
    }

    {
      auto cost = mtg::mana_cost::from_string("{U}{B}");
      REQUIRE(cost.has_blue());
      REQUIRE(cost.has_black());
      REQUIRE(cost.converted() == 2);
    }

    {
      auto cost = mtg::mana_cost::from_string("{C}{W}{R}");
      REQUIRE(cost.has_red());
      REQUIRE(cost.has_white());
      REQUIRE(cost.has_waste());
      REQUIRE(cost.converted() == 3);
    }
  }

  SECTION("test generic mana costs from string")
  {
    {
      auto generic_cost = mtg::mana_cost::from_string("{3}");
      REQUIRE(generic_cost.converted() == 3);

      REQUIRE_FALSE(generic_cost.has_x());
      REQUIRE_FALSE(generic_cost.no_cost());
      REQUIRE_FALSE(generic_cost.has_waste());
    }
  }

  SECTION("test special mana costs from string")
  {
    {
      auto snow_cost = mtg::mana_cost::from_string("{S}{S}");
      REQUIRE(snow_cost.has_snow());
      REQUIRE(snow_cost.converted() == 2);
    }
    {
      auto x_cost = mtg::mana_cost::from_string("{X}");
      REQUIRE(x_cost.has_x());
      REQUIRE(x_cost.converted() == 0);

      REQUIRE_FALSE(x_cost.no_cost());
      REQUIRE_FALSE(x_cost.has_snow());
    }
  }

  SECTION("test hybrid mana creation from string")
  {
    {
      auto cost = mtg::mana_cost::from_string("{R/W}");
      REQUIRE(cost.has_red());
      REQUIRE(cost.has_white());
      REQUIRE(cost.converted() == 1);

      REQUIRE_FALSE(cost.has_green());
      REQUIRE_FALSE(cost.has_black());
    }

    {
      auto cost = mtg::mana_cost::from_string("{G/U}");
      REQUIRE(cost.has_blue());
      REQUIRE(cost.has_green());

      REQUIRE_FALSE(cost.has_red());
    }
  }

  SECTION("test mono color hybrid from string")
  {
    {
      auto cost = mtg::mana_cost::from_string("{2/G}");
      REQUIRE(cost.has_green());
      REQUIRE(cost.converted() == 2);
    }

    {
      auto cost = mtg::mana_cost::from_string("{2/W}{2/W}{2/W}");
      REQUIRE(cost.converted() == 6);
    }
  }

  SECTION("test phyrexian mana from string")
  {
    {
      auto cost = mtg::mana_cost::from_string("{P/U}");
      REQUIRE(cost.has_blue());
    }

    {
      auto cost = mtg::mana_cost::from_string("{P/G}");
      REQUIRE(cost.has_green());
    }
  }

  SECTION("test parse invalid string") { REQUIRE_THROWS_AS(mtg::mana_cost::from_string("{Q}"), mge::invalid_argument); }
}