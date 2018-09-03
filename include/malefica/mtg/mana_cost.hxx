#ifndef MALEFICA_MTG_MANACOST_HXX
#define MALEFICA_MTG_MANACOST_HXX

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

    bool has_white() const noexcept;
    bool has_blue() const noexcept;
    bool has_black() const noexcept;
    bool has_red() const noexcept;
    bool has_green() const noexcept;
    bool has_waste() const noexcept;

    bool has_x() const noexcept;
    bool has_snow() const noexcept;

    bool has_phyrexian() const noexcept;

    inline bool no_cost() const noexcept { return m_container.empty(); }

    amount_type converted() const noexcept;

  private:
    mana_cost() = default;

    container_type m_container{};
  };
} // namespace mtg

#endif /*MALEFICA_MTG_MANACOST_HXX*/