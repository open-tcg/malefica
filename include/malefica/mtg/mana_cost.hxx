#ifndef MALEFICA_MTG_MANACOST_HXX
#define MALEFICA_MTG_MANACOST_HXX

#include <functional>
#include <unordered_map>

#include "mana_types.hxx"

namespace mtg
{
  class mana_cost
  {
  public:
    using amount_type = mge::int32_t;

  public:
    using container_type = std::unordered_map<mana, amount_type, mana_hash>;

    static mana_cost from_string(const std::string& manacost);

    inline void add(const mana& type, amount_type amount) noexcept { m_container[type] += amount; }

    inline bool has_white() const noexcept
    {
      static const auto func = [](const mana& m) -> int { return m.has_white(); };
      return check_for_each(func);
    }

    bool has_blue() const noexcept
    {
      static const auto func = [](const mana& m) -> int { return m.has_blue(); };
      return check_for_each(func);
    }

    bool has_black() const noexcept
    {
      static const auto func = [](const mana& m) -> int { return m.has_black(); };
      return check_for_each(func);
    }

    bool has_red() const noexcept
    {
      static const auto func = [](const mana& m) -> int { return m.has_red(); };
      return check_for_each(func);
    }

    bool has_green() const noexcept
    {
      static const auto func = [](const mana& m) -> int { return m.has_green(); };
      return check_for_each(func);
    }

    bool has_waste() const noexcept
    {
      static const auto func = [](const mana& m) -> int { return m.has_waste(); };
      return check_for_each(func);
    }

    bool has_x() const noexcept
    {
      static const auto func = [](const mana& m) -> int { return m.is_x(); };
      return check_for_each(func);
    }

    bool has_snow() const noexcept
    {
      static const auto func = [](const mana& m) -> int { return m.is_snow(); };
      return check_for_each(func);
    }

    bool has_phyrexian() const noexcept
    {
      static const auto func = [](const mana& m) -> int { return m.is_phyrexian(); };
      return check_for_each(func);
    }

    inline bool no_cost() const noexcept { return m_container.empty(); }

    amount_type converted() const noexcept;

  private:
    mana_cost() = default;

    bool check_for_each(const std::function<bool(const mana&)>& function_ptr) const noexcept;
    container_type m_container{};
  };
} // namespace mtg

#endif /*MALEFICA_MTG_MANACOST_HXX*/