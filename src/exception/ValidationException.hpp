#ifndef __VALIDATION_EXCEPTION_HPP__
#define __VALIDATION_EXCEPTION_HPP__

#include "./CppCosoException.hpp"

/**
 * Exception class for validation error
 */
class ValidationException : public CppCosoException {
public:
  /** Constructor
   *  @param message The message exception
   */
  explicit ValidationException(const char *const message)
      : CppCosoException(message) {}

  /** Constructor
   *  @param message The error message.
   */
  explicit ValidationException(const std::string_view &message)
      : CppCosoException(message) {}

private:
  /** Error message.
   */
  std::string m_message = "Conversion error";
};
#endif