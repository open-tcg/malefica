#include <malefica/log/message_sink.hxx>

#include <iomanip>
#include <iostream>

namespace malefica
{
  namespace log
  {
    std::string get_category(category c) noexcept
    {
      std::string category_string("application");
      switch (c)
      {
        case category::application:
          category_string = "application";
          break;
        case category::error:
          category_string = "error";
          break;
        case category::assert:
          category_string = "assert";
          break;
        case category::system:
          category_string = "system";
          break;
        case category::audio:
          category_string = "audio";
          break;
        case category::render:
          category_string = "render";
          break;
        case category::video:
          category_string = "video";
          break;
        case category::input:
          category_string = "input";
          break;
        case category::network:
          category_string = "network";
          break;
        case category::ai:
          category_string = "ai";
          break;
        case category::profiling:
          category_string = "profiling";
          break;
        case category::test:
          category_string = "test";
          break;
        case category::malefica:
          category_string = "malefica";
          break;
      }
      return category_string;
    }

    std::string get_level(level l) noexcept
    {
      std::string level_string("info");
      switch (l)
      {
        case level::trace:
          level_string = "trace";
          break;

        case level::debug:
          level_string = "debug";
          break;
        case level::info:
          level_string = "info";
          break;
        case level::warning:
          level_string = "warning";
          break;
        case level::error:
          level_string = "error";
          break;
        case level::fatal:
          level_string = "fatal";
          break;
      }
      return level_string;
    }

    void stdout_sink::process_message(const malefica::log::message& msg)
    {
      auto category_string = get_category(msg.get_category());
      auto level_string = get_level(msg.get_level());

      std::cout << "[" << category_string << "]" << std::setw(20 - category_string.size()) << "(" << level_string << ")" << std::setw(10 - level_string.size())
                << " : " << msg.get_message() << std::endl
                << std::flush;
    }

  } // log
} // malefica