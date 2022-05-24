#ifndef __CONVERSION_EXCEPTION_HPP__
#define __CONVERSION_EXCEPTION_HPP__

#include "./CppCosoException.hpp"

/**
 * Exception class for conversion error
 */
class ConversionException : public CppCosoException {
public:
  /** Constructor
   *  @param message The message exception
   */
  explicit ConversionException(const char *const message)
      : CppCosoException(message) {}

  /** Constructor
   *  @param message The error message.
   */
  explicit ConversionException(const std::string_view &message)
      : CppCosoException(message) {}

private:
  /** Error message.
   */
  std::string m_message = "Conversion error";
};
#endif