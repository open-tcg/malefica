#include <malefica/mtg/mana_types.hxx>

#include <catch.hpp>

TEST_CASE("testing mana primitives", "[mana][mtg]")
{
  SECTION("test simple mana_types")
  {
    {
      auto mana = mtg::mana_types::white;
      REQUIRE(mana.is_white());
      REQUIRE(mana.is_monocolored());

      REQUIRE_FALSE(mana.is_green());
      REQUIRE_FALSE(mana.is_hybrid());
      REQUIRE_FALSE(mana.is_phyrexian());
    }

    {
      auto mana = mtg::mana_types::waste;
      REQUIRE(mana.is_waste());
      REQUIRE(mana.is_colorless());

      REQUIRE_FALSE(mana.is_blue());
      REQUIRE_FALSE(mana.has_green());
      REQUIRE_FALSE(mana.is_snow());
      REQUIRE_FALSE(mana.is_x());
    }
  }

  SECTION("test hybrid mana_types")
  {
    {
      auto mana = mtg::mana_types::black_red;
      REQUIRE(mana.has_black());
      REQUIRE(mana.has_red());
      REQUIRE(mana.is_hybrid());
      REQUIRE(mana.is_multicolored_hybrid());

      REQUIRE_FALSE(mana.is_black());
      REQUIRE_FALSE(mana.is_red());
      REQUIRE_FALSE(mana.has_generic());
      REQUIRE_FALSE(mana.is_phyrexian());
    }

    {
      auto mana = mtg::mana_types::green_blue;
      REQUIRE(mana.has_blue());
      REQUIRE(mana.has_green());
      REQUIRE(mana.is_hybrid());

      REQUIRE_FALSE(mana.is_black());
      REQUIRE_FALSE(mana.is_red());
    }
  }
}