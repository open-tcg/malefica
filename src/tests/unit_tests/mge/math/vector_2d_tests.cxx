#include <malefica/mge/math/vector_2d.hxx>

#include <catch.hpp>

TEST_CASE("testing 2d vector operations", "[math][mge]")
{
  SECTION("calculation of angle between two vectors")
  {
    mge::math::vector_2d vector_a(3, 4);
    mge::math::vector_2d vector_b(4, 3);

    auto angle = vector_a.angle(vector_b);
    REQUIRE(angle == Approx(-0.283794));

    vector_a = mge::math::vector_2d(7, 1);
    vector_b = mge::math::vector_2d(5, 5);

    angle = vector_a.angle(vector_b);
    REQUIRE(angle == Approx(0.64350111));
  }

  SECTION("clamping of a vector")
  {
    mge::math::vector_2d vector_a(1, 8);
    mge::math::vector_2d vector_min(2, 2);
    mge::math::vector_2d vector_max(3, 3);

    vector_a.clamp(vector_min, vector_max);
    REQUIRE(vector_a.x() == 2);
    REQUIRE(vector_a.y() == 3);
  }
}