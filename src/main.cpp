#include "./Application.hpp"

// STL stream import
#include <iostream>

/**
 * @brief entry of application
 *
 * @param argc The number of argument of process launch command
 * @param argv The process launch command arguments array
 * @return int The process exit code
 */
int32_t main(int argc, char *argv[]) {
  const uint8_t APP_NAME_EXE_OFFSET = 1;
  std::list<std::string> args(argv + APP_NAME_EXE_OFFSET, argv + argc);
  return Application::run(args);
}
