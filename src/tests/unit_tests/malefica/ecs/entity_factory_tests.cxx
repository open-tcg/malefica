#include <malefica/ecs/entity_factory.hxx>

#include <catch.hpp>
#include <iostream>

struct position final
{
  explicit position(int x_pos = 0, int y_pos = 0) : x(x_pos), y(y_pos) {}

  int x;
  int y;
};

struct velocity final
{
  explicit velocity(int x_pos = 0, int y_pos = 0) : x(x_pos), y(y_pos) {}

  int x;
  int y;
};

TEST_CASE("test entity factory", "[ecs]")
{
  SECTION("test factory creation and basic methods")
  {
    malefica::ecs::entity_factory factory{};
    REQUIRE(factory.empty());

    auto empty_entity = factory.create();
    REQUIRE_FALSE(factory.empty());
    REQUIRE(factory.size() == 1);

    auto pos_entity = factory.create<position, velocity>();
    REQUIRE(factory.size() == 2);

    REQUIRE(factory.size<position>() == 1);
    REQUIRE(factory.size<velocity>() == 1);

    auto pos_entity_2 = factory.create<position>(position{1, 2});
    REQUIRE(factory.size<position>() == 2);
  }

  SECTION("test entity creation and destroying")
  {
    malefica::ecs::entity_factory factory{};
    auto entity = factory.create();
    REQUIRE_FALSE(factory.empty());
    factory.destroy(entity);
    REQUIRE(factory.empty());

    auto entity_1 = factory.create();
    auto entity_2 = factory.create();
    factory.destroy(entity_1);
    auto entity_3 = factory.create();
    REQUIRE(entity_2 != entity_3);
    REQUIRE(factory.size() == 2);
  }

  SECTION("test validation of entities")
  {
    malefica::ecs::base_entity_factory<std::uint64_t> factory{};
    auto entity = factory.create();
    REQUIRE(factory.valid(entity));

    auto version = factory.version(entity);
    REQUIRE(version == 0);

    auto current_version = factory.current_version(entity);
    REQUIRE(current_version == version);

    factory.destroy(entity);
    REQUIRE_FALSE(factory.valid(entity));

    current_version = factory.current_version(entity);
    REQUIRE(current_version != version);

    entity = factory.create();
    version = factory.version(entity);

    REQUIRE(version == 1);
  }

  SECTION("test assignment to entity components")
  {
    malefica::ecs::entity_factory factory{};
    auto entity = factory.create();

    {
      auto& val = factory.assign<velocity>(entity, 1, 2);
      REQUIRE(val.x == 1);
      REQUIRE(val.y == 2);
    }

    {
      auto& val = factory.assign<position>(entity);
      REQUIRE(val.x == 0);
      REQUIRE(val.y == 0);
    }

    REQUIRE(factory.has<position, velocity>(entity));

    position pos{};
    velocity vel{};

    std::tie(pos, vel) = factory.get<position, velocity>(entity);
    REQUIRE(pos.x == 0);
    REQUIRE(pos.y == 0);

    REQUIRE(vel.x == 1);
    REQUIRE(vel.y == 2);

    factory.remove<velocity>(entity);
    REQUIRE(factory.has<position>(entity));
    REQUIRE_FALSE(factory.has<velocity>(entity));

    auto pos_entity = factory.create<position>();
    REQUIRE(factory.size<position>() == 2);

    factory.reset<position>();
    REQUIRE(factory.empty<position>());

    REQUIRE_FALSE(factory.has<position>(entity));
    REQUIRE_FALSE(factory.has<position>(pos_entity));
  }
}