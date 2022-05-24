#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__

#include <algorithm>
#include <list>
#include <string>

/**
 * @brief class to run application
 */
class Application {

public:
  /**
   * @brief Method to run application
   *
   * @param args The argument list array
   * @return int32_t The result state of conversion
   */
  static int32_t run(const std::list<std::string> &args);
};
#endif
