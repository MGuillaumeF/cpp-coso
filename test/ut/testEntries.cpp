#ifndef OS_WINDOWS
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define OS_WINDOWS
#endif
#endif

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#ifndef OS_WINDOWS
#include <boost/test/tools/output_test_stream.hpp>
#endif

#include <iostream>

#include "../../src/Application.hpp"

BOOST_AUTO_TEST_SUITE(testsApplicationEntries)

void checkApplicationEntryRun(const std::list<std::string> &arguments,
                              const int32_t &exit_code) {
  BOOST_CHECK(Application::run(arguments) == exit_code);
}

void checkApplicationEntryRun(const std::list<std::string> &arguments,
                              const int32_t &exit_code, const std::string &cout,
                              const std::string &cerr) {
#ifndef OS_WINDOWS
  boost::test_tools::output_test_stream outputStream;
  std::streambuf *oldCout = std::cout.rdbuf(outputStream.rdbuf());

  boost::test_tools::output_test_stream errorStream;
  std::streambuf *oldCerr = std::cerr.rdbuf(errorStream.rdbuf());
#endif

  checkApplicationEntryRun(arguments, exit_code);

#ifndef OS_WINDOWS
  BOOST_CHECK(outputStream.is_equal(cout));
  BOOST_CHECK(errorStream.is_equal(cerr));

  std::cout.rdbuf(oldCout);
  std::cerr.rdbuf(oldCerr);
#endif
}

BOOST_AUTO_TEST_CASE(testCLIEntries) {
  // VERSION TEST
  checkApplicationEntryRun({"--version"}, 0, "0.2.3\n", "");
  checkApplicationEntryRun({"-v"}, 0, "0.2.3\n", "");

  // HELP MESSAGE TEST
  const std::string HELP_MESSAGE =
      "CPP-COSO - MANUAL\r\n"
      "[OPTIONS]\r\n"
      "-h, --help       display help message\r\n"
      "-v, --version    display version of application\r\n"
      "[EXAMPLES]\r\n"
      "cpp-coso cppcheck-report.xml cppcheck-sonarqube-report.json\r\n"
      "cpp-coso clang-tidy clang-tidy-report.txt "
      "clang-tidy-sonarqube-report.json\r\n"
      "cpp-coso boost-test boost-test-log-report.xml "
      "boost-test-results-report.xml boost-test-sonarqube-report.json\n";

  checkApplicationEntryRun({"-h"}, 0, HELP_MESSAGE, "");
  checkApplicationEntryRun({"--help"}, 0, HELP_MESSAGE, "");

  const std::string BAD_TOOL_MESSAGE =
      "Bad usage of tool : \nunknown entry reports format, accepted format : "
      "cppcheck, clang-tidy, boost-test\n";
  const std::string BAD_TOOL_CLANG_TIDY_CPP_CHECK_MESSAGE =
      "Bad usage of tool : "
      "\narguments list error, accepted format :"
      "\n[EXAMPLES]"
      "\ncpp-coso cppcheck-report.xml cppcheck-sonarqube-report.json"
      "\ncpp-coso clang-tidy clang-tidy-report.txt "
      "clang-tidy-sonarqube-report.json\n";
  const std::string BAD_TOOL_BOOST_TEST_MESSAGE =
      "Bad usage of tool : "
      "\narguments list error, accepted format :"
      "\n[EXAMPLE]"
      "\ncpp-coso boost-test boost-test-log-report.xml "
      "boost-test-results-report.xml "
      "boost-test-sonarqube-report.json\n";

  checkApplicationEntryRun({}, EXIT_FAILURE, "", BAD_TOOL_MESSAGE);
  checkApplicationEntryRun({"bad-tool"}, EXIT_FAILURE, "", BAD_TOOL_MESSAGE);
  checkApplicationEntryRun({"clang-tidy"}, EXIT_FAILURE, "",
                           BAD_TOOL_CLANG_TIDY_CPP_CHECK_MESSAGE);
  checkApplicationEntryRun({"cppcheck"}, EXIT_FAILURE, "",
                           BAD_TOOL_CLANG_TIDY_CPP_CHECK_MESSAGE);
  checkApplicationEntryRun({"boost-test"}, EXIT_FAILURE, "",
                           BAD_TOOL_BOOST_TEST_MESSAGE);
}

BOOST_AUTO_TEST_SUITE_END()
