#ifndef MALEFICA_WGE_EXCEPTION_HXX
#define MALEFICA_WGE_EXCEPTION_HXX

#include <stdexcept>
#include <string>

namespace mge
{

  class exception : public std::exception
  {
  public:
    explicit exception(const char* msg) : m_message(msg) {}
    explicit exception(const std::string& message) : m_message(message) {}
    exception(std::string&& message) : m_message(std::move(message)) {}

    ~exception() noexcept override = default;

    inline const char* what() const noexcept override { return m_message.c_str(); }

  protected:
    std::string m_message;
  };

  class logic_exception : public exception
  {
  public:
    explicit logic_exception(const char* msg) : exception(msg) {}
    explicit logic_exception(const std::string& message) : exception(message) {}
    logic_exception(std::string&& message) : exception(std::move(message)) {}

    ~logic_exception() override = default;
  };

  class invalid_argument : public logic_exception
  {
  public:
    explicit invalid_argument(const char* msg) : logic_exception(msg) {}
    explicit invalid_argument(const std::string& message) : logic_exception(message) {}
    invalid_argument(std::string&& message) : logic_exception(std::move(message)) {}

    ~invalid_argument() override = default;
  };

  class runtime_exception : public exception
  {
  public:
    explicit runtime_exception(const char* msg) : exception(msg) {}
    explicit runtime_exception(const std::string& message) : exception(message) {}
    runtime_exception(std::string&& message) : exception(std::move(message)) {}

    ~runtime_exception() override = default;
  };
} // namespace mge

#endif /*MALEFICA_WGE_EXCEPTION_HXX*/