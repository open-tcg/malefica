#ifndef MALEFICA_MTG_MANAPRIMITIVES_HXX
#define MALEFICA_MTG_MANAPRIMITIVES_HXX

#include <bitset>
#include <string>

#include <malefica/mge/types.hxx>

namespace mtg
{
  class mana
  {
    using flag_type = std::bitset<16>;

    static constexpr mge::uint8_t generic_pos = 0;
    static constexpr mge::uint8_t white_pos = 1;
    static constexpr mge::uint8_t blue_pos = 2;
    static constexpr mge::uint8_t black_pos = 3;
    static constexpr mge::uint8_t red_pos = 4;
    static constexpr mge::uint8_t green_pos = 5;
    static constexpr mge::uint8_t waste_pos = 6;

    static const flag_type color_mask;

    static constexpr mge::uint8_t is_x_pos = 9;
    static constexpr mge::uint8_t or_2_generic_pos = 10;
    static constexpr mge::uint8_t or_2_life_pos = 11;
    static constexpr mge::uint8_t is_snow_pos = 12;

  public:
    using value_type = mge::uint16_t;

    inline constexpr bool has_generic() const noexcept { return m_type_flags[generic_pos]; }
    inline constexpr bool has_white() const noexcept { return m_type_flags[white_pos]; }
    inline constexpr bool has_blue() const noexcept { return m_type_flags[blue_pos]; }
    inline constexpr bool has_black() const noexcept { return m_type_flags[black_pos]; }
    inline constexpr bool has_red() const noexcept { return m_type_flags[red_pos]; }
    inline constexpr bool has_green() const noexcept { return m_type_flags[green_pos]; }
    inline constexpr bool has_waste() const noexcept { return m_type_flags[waste_pos]; }

    inline bool is_white() const noexcept { return !is_hybrid() && has_white(); }
    inline bool is_blue() const noexcept { return !is_hybrid() && has_blue(); }
    inline bool is_black() const noexcept { return !is_hybrid() && has_black(); }
    inline bool is_red() const noexcept { return !is_hybrid() && has_red(); }
    inline bool is_green() const noexcept { return !is_hybrid() && has_green(); }
    inline bool is_waste() const noexcept { return !is_hybrid() && has_waste(); }

    inline constexpr bool is_x() const noexcept { return m_type_flags[is_x_pos]; }
    inline constexpr bool is_snow() const noexcept { return m_type_flags[is_snow_pos]; }

    inline bool is_colorless() const noexcept { return color_count() == 0; }
    inline bool is_monocolored() const noexcept { return color_count() == 1; }

    inline bool is_hybrid() const noexcept { return (is_multicolored_hybrid() || is_monocolored_hybrid()); }
    inline bool is_multicolored_hybrid() const noexcept { return color_count() > 1; }
    inline constexpr bool is_monocolored_hybrid() const noexcept { return m_type_flags[or_2_generic_pos]; }
    inline constexpr bool is_phyrexian() const noexcept { return m_type_flags[or_2_life_pos]; }

  private:
    mana(value_type flags, const std::string& representation) noexcept : m_type_flags{flags}, m_str_representation(representation) {}
    inline mge::size_t color_count() const noexcept { return (m_type_flags & color_mask).count(); }

    friend struct mana_types;

    const flag_type m_type_flags;
    const std::string m_str_representation;
  };

  struct mana_types
  {
    static const mana white;
    static const mana blue;
    static const mana black;
    static const mana red;
    static const mana green;
    static const mana waste;

    static const mana white_blue;
    static const mana white_black;
    static const mana blue_black;
    static const mana blue_red;
    static const mana black_red;
    static const mana black_green;
    static const mana red_white;
    static const mana red_green;
    static const mana green_white;
    static const mana green_blue;

    static const mana white_or_2;
    static const mana blue_or_2;
    static const mana black_or_2;
    static const mana red_or_2;
    static const mana green_or_2;

    static const mana phyrexian_white;
    static const mana phyrexian_blue;
    static const mana phyrexian_black;
    static const mana phyrexian_red;
    static const mana phyrexian_green;

    static const mana generic;
    static const mana snow;
    static const mana variable;
  };

} // namespace mtg

#endif /*MALEFICA_MTG_MANAPRIMITIVES_HXX*/