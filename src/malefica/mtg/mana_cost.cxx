#include <malefica/mtg/mana_cost.hxx>
#include <malefica/mtg/mana_types.hxx>

#include <malefica/mge/exception.hxx>
#include <malefica/mge/log/logging.hxx>

#include <iostream>

namespace mtg
{
  bool mana_cost::check_for_each(const std::function<bool(const mana&)>& func) const noexcept
  {
    for (auto& mana : m_container)
    {
      if (func(mana.first))
      {
        return true;
      }
    }
    return false;
  }

  mana_cost::amount_type mana_cost::converted() const noexcept
  {
    amount_type costs = 0;
    for (auto& mana : m_container)
    {
      costs += (mana.second * mana.first.cost_multiplicator());
    }
    return costs;
  }

  mana_cost mana_cost::from_string(const std::string& manacost_str)
  {
    mana_cost result_costs{};
    if (!manacost_str.empty())
    {
      static const char start_delimiter('{');
      static const char stop_delimiter('}');

      mge::size_t start_pos = 0;
      mge::size_t stop_pos = 0;

      while (start_pos != std::string::npos && stop_pos != std::string::npos)
      {
        start_pos = manacost_str.find(start_delimiter, start_pos);
        auto pos_after_start_delimeter = start_pos + 1;
        stop_pos = manacost_str.find(stop_delimiter, stop_pos);

        if (start_pos != std::string::npos && stop_pos != std::string::npos)
        {
          try
          {
            auto mana_str = manacost_str.substr(pos_after_start_delimeter, stop_pos - pos_after_start_delimeter);
            auto type = mana_types::from_string(mana_str);

            amount_type amount = 1;
            if (type == mana_types::generic)
            {
              amount = std::stoi(mana_str);
            }
            result_costs.add(type, amount);
          }
          catch (std::exception& e)
          {
            throw mge::invalid_argument("couldn't parse string: " + manacost_str + " error: " + e.what());
          }

          ++start_pos;
          ++stop_pos;
        }
      }
    }
    return result_costs;
  }
} // namespace mtg