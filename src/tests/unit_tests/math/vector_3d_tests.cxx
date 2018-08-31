#include <malefica/math/vector_3d.hxx>

#include <catch.hpp>

TEST_CASE("testing 3d vector operations", "[math][core]")
{
  SECTION("calculation of angle between two vectors")
  {
    malefica::math::vector_3d vector_a(3, 4, 0);
    malefica::math::vector_3d vector_b(4, 4, 2);

    auto angle = vector_a.angle(vector_b);
    REQUIRE(angle == Approx(0.3673).epsilon(0.001));

    vector_a = malefica::math::vector_3d(1, 0, 3);
    vector_b = malefica::math::vector_3d(5, 5, 0);

    angle = vector_a.angle(vector_b);
    REQUIRE(angle == Approx(1.34528292));
  }

  SECTION("testing const access of a vector")
  {
    const malefica::math::vector_3d vector_const(2, 4, 8);

    REQUIRE(vector_const.x() == 2);
    REQUIRE(vector_const.y() == 4);
    REQUIRE(vector_const.z() == 8);

    malefica::math::vector_3d vector_copy{};
    vector_copy = vector_const;

    REQUIRE(vector_copy == vector_const);
  }

  SECTION("clamping of a vector")
  {
    malefica::math::vector_3d vector_a(1, 4, 8);
    malefica::math::vector_3d vector_min(2, 2, 2);
    malefica::math::vector_3d vector_max(6, 6, 6);

    vector_a = malefica::math::clamp(vector_a, vector_min, vector_max);
    REQUIRE(vector_a.x() == 2);
    REQUIRE(vector_a.y() == 4);
    REQUIRE(vector_a.z() == 6);
  }

  SECTION("test vector operations")
  {
    malefica::math::vector_3d test_vector(3, 2, 7);
    auto direction = test_vector.direction();
    const auto* data = direction.data();

    REQUIRE(data[0] == Approx(0.381).epsilon(0.01));
    REQUIRE(data[1] == Approx(0.254).epsilon(0.01));
    REQUIRE(data[2] == Approx(0.889).epsilon(0.01));

    test_vector -= malefica::math::vector_3d(1, 1, 3);
    REQUIRE(test_vector.x() == 2);
    REQUIRE(test_vector.y() == 1);
    REQUIRE(test_vector.z() == 4);
  }
}