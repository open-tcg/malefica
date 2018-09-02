#ifndef MALEFICA_MTG_CARDCOLORS_HXX
#define MALEFICA_MTG_CARDCOLORS_HXX

#include <malefica/mge/types.hxx>

namespace mtg
{

  enum class color_type : uint8_t
  {
    colorless = 0,
    white = 1 << 0,
    blue = 1 << 1,
    black = 1 << 2,
    red = 1 << 3,
    green = 1 << 4
  };

} // namespace mtg

#endif /*MALEFICA_MTG_CARDCOLORS_HXX*/