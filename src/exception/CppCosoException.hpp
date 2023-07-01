#ifndef __CPP_COSO_EXCEPTION_HPP__
#define __CPP_COSO_EXCEPTION_HPP__

#include <exception>
#include <string>
#include <string_view>

/**
 * Exception class for all CppCoso
 */
class CppCosoException : public std::exception {
public:
  /** Constructor
   *  @param message The message exception
   */
  explicit CppCosoException(const char *const message) : m_message(message) {}

  /** Constructor
   *  @param message The error message.
   */
  explicit CppCosoException(const std::string_view &message)
      : m_message(message) {}

  /**
   * @brief The explanation of exceptn cause
   * @see std::exception
   *
   * @return const char* The message of exception
   */
  const char *what() const noexcept override { return m_message.c_str(); }

private:
  /** Error message.
   */
  std::string m_message = "Cpp COSO error";
};
#endif