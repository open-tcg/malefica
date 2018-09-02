
#include <malefica/mtg/mana_types.hxx>

namespace mtg
{
  const mana::flag_type mana::color_mask = mana::flag_type{(1 << white_pos) | (1 << blue_pos) | (1 << black_pos) | (1 << red_pos) | (1 << green_pos)};

  const mana mana_types::white(1 << mana::white_pos, "W");
  const mana mana_types::blue(1 << mana::blue_pos, "U");
  const mana mana_types::black(1 << mana::black_pos, "B");
  const mana mana_types::red(1 << mana::red_pos, "R");
  const mana mana_types::green(1 << mana::green_pos, "G");
  const mana mana_types::waste(1 << mana::waste_pos, "C");

  const mana mana_types::white_blue(1 << mana::white_pos | 1 << mana::blue_pos, "W/U");
  const mana mana_types::white_black(1 << mana::white_pos | 1 << mana::black_pos, "W/B");
  const mana mana_types::blue_black(1 << mana::blue_pos | 1 << mana::black_pos, "U/B");
  const mana mana_types::blue_red(1 << mana::blue_pos | 1 << mana::red_pos, "U/R");
  const mana mana_types::black_red(1 << mana::black_pos | 1 << mana::red_pos, "B/R");
  const mana mana_types::black_green(1 << mana::black_pos | 1 << mana::green_pos, "B/G");
  const mana mana_types::red_white(1 << mana::red_pos | 1 << mana::white_pos, "R/W");
  const mana mana_types::red_green(1 << mana::red_pos | 1 << mana::green_pos, "R/G");
  const mana mana_types::green_white(1 << mana::green_pos | 1 << mana::white_pos, "G/W");
  const mana mana_types::green_blue(1 << mana::green_pos | 1 << mana::blue_pos, "G/B");

  const mana mana_types::white_or_2(1 << mana::generic_pos | 1 << mana::white_pos | 1 << mana::or_2_generic_pos, "2/W");
  const mana mana_types::blue_or_2(1 << mana::generic_pos | 1 << mana::blue_pos | 1 << mana::or_2_generic_pos, "2/U");
  const mana mana_types::black_or_2(1 << mana::generic_pos | 1 << mana::black_pos | 1 << mana::or_2_generic_pos, "2/B");
  const mana mana_types::red_or_2(1 << mana::generic_pos | 1 << mana::red_pos | 1 << mana::or_2_generic_pos, "2/R");
  const mana mana_types::green_or_2(1 << mana::generic_pos | 1 << mana::green_pos | 1 << mana::or_2_generic_pos, "2/G");

  const mana mana_types::phyrexian_white(1 << mana::white_pos | 1 << mana::or_2_life_pos, "P/W");
  const mana mana_types::phyrexian_blue(1 << mana::blue_pos | 1 << mana::or_2_life_pos, "P/U");
  const mana mana_types::phyrexian_black(1 << mana::black_pos | 1 << mana::or_2_life_pos, "P/B");
  const mana mana_types::phyrexian_red(1 << mana::red_pos | 1 << mana::or_2_life_pos, "P/R");
  const mana mana_types::phyrexian_green(1 << mana::green_pos | 1 << mana::or_2_life_pos, "P/G");

  const mana mana_types::generic(1 << mana::generic_pos, "");
  const mana mana_types::snow(1 << mana::generic_pos | 1 << mana::is_snow_pos, "S");
  const mana mana_types::variable(1 << mana::generic_pos | 1 << mana::is_x_pos, "X");

} // namespace mtg
