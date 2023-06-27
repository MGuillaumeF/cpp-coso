#include "./Application.hpp"

#include "report/ClangTidyIssueReportConvertor.hpp"
#include "report/CppCheckIssueReportConvertor.hpp"
#include "report/GccCompileWarningIssueReportConvertor.hpp"
#include "report/TestConvertor.hpp"

// boost imports
// STL stream import
#include <fstream>
#include <iostream>
#include <string_view>

// STL data containers import
#include <list>
#include <unordered_set>

// boost imports
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

// generated configuration
#include "config.hpp"

struct StringHash {
  // enables heterogenous lookup
  using is_transparent = void;

  std::size_t operator()(const std::string_view sv) const {
    const std::hash<std::string_view> hasher;
    return hasher(sv);
  }
};

/**
 * @brief Method to run application
 *
 * @param args The argument list array
 * @return int32_t The result state of conversion
 */
int32_t Application::run(const std::list<std::string> &args) {
  // by default if execution don't raise error
  // the exit code is success
  int32_t exitStatus = EXIT_SUCCESS;

  // process args expected
  const uint8_t ARGUMENTS_LINT_SIZE = 3;
  const uint8_t ARGUMENTS_BOOST_TEST_SIZE = 4;

  const std::string VERSION = PROJECT_VERSION;
  const std::string HELP_MESSAGE =
      "CPP-COSO - MANUAL\r\n"
      "[OPTIONS]\r\n"
      "-h, --help       display help message\r\n"
      "-v, --version    display version of application\r\n"
      "[EXAMPLES]\r\n"
      "cpp-coso cppcheck cppcheck-report.xml cppcheck-sonarqube-report.json\r\n"
      "cpp-coso clang-tidy clang-tidy-report.txt "
      "clang-tidy-sonarqube-report.json\r\n"
      "cpp-coso gcc-warning gcc-warning-report.txt "
      "gcc-warning-sonarqube-report.json\r\n"
      "cpp-coso boost-test boost-test-log-report.xml "
      "boost-test-results-report.xml boost-test-sonarqube-report.json";
  try {

    const std::unordered_set<std::string, StringHash, std::equal_to<>>
        unorderedArgs(std::begin(args), std::end(args));
    if (unorderedArgs.contains("--help") || unorderedArgs.contains("-h")) {
      std::cout << HELP_MESSAGE << std::endl;
    } else if (unorderedArgs.contains("--version") ||
               unorderedArgs.contains("-v")) {
      std::cout << VERSION << std::endl;
    } else {
      std::list<std::string> argsCopy(args);
      if (!args.empty()) {
        const std::string reportType = argsCopy.front();
        argsCopy.pop_front();
        if (reportType == "boost-test") {
          if (args.size() == ARGUMENTS_BOOST_TEST_SIZE) {

            const std::string resultsTestsInput = argsCopy.front();
            argsCopy.pop_front();
            const std::string logsTestsInput = argsCopy.front();
            argsCopy.pop_front();
            const std::string formatedTestsOutput = argsCopy.front();
            argsCopy.pop_front();

            const boost::property_tree::ptree sonarBoostTestPtree =
                TestConvertor::boostReportsToSonarReport(logsTestsInput,
                                                         resultsTestsInput);
            boost::property_tree::write_xml(formatedTestsOutput,
                                            sonarBoostTestPtree);
          } else {
            std::cerr << "Bad usage of tool : " << std::endl
                      << "arguments list error, accepted format :" << std::endl
                      << "[EXAMPLE]" << std::endl
                      << "cpp-coso boost-test boost-test-log-report.xml "
                         "boost-test-results-report.xml "
                         "boost-test-sonarqube-report.json"
                      << std::endl;
            exitStatus = EXIT_FAILURE;
          }

        } else if (reportType == "cppcheck" || reportType == "clang-tidy" ||
                   reportType == "gcc-warning") {
          if (args.size() == ARGUMENTS_LINT_SIZE) {
            const std::string inputFile = argsCopy.front();
            argsCopy.pop_front();
            const std::string outputFile = argsCopy.front();
            argsCopy.pop_front();

            if (reportType == "cppcheck") {
              CppCheckIssueReportConvertor::getInstance()->convert({inputFile},
                                                                   outputFile);
              CppCheckIssueReportConvertor::getInstance().reset();

            } else if (reportType == "clang-tidy") {
              ClangTidyIssueReportConvertor::getInstance()->convert({inputFile},
                                                                    outputFile);
              ClangTidyIssueReportConvertor::getInstance().reset();
            } else {
              GccCompileWarningIssueReportConvertor::getInstance()->convert(
                  {inputFile}, outputFile);
              GccCompileWarningIssueReportConvertor::getInstance().reset();
            }
          } else {
            std::cerr
                << "Bad usage of tool : " << std::endl
                << "arguments list error, accepted format :" << std::endl
                << "[EXAMPLES]" << std::endl
                << "cpp-coso cppcheck-report.xml cppcheck-sonarqube-report.json"
                << std::endl
                << "cpp-coso clang-tidy clang-tidy-report.txt "
                   "clang-tidy-sonarqube-report.json"
                << std::endl;
            exitStatus = EXIT_FAILURE;
          }
        } else {
          std::cerr << "Bad usage of tool : " << std::endl
                    << "unknown entry reports format, accepted format : "
                       "cppcheck, clang-tidy, boost-test"
                    << std::endl;
          // change process return value
          exitStatus = EXIT_FAILURE;
        }
      } else {
        std::cerr << "Bad usage of tool : " << std::endl
                  << "unknown entry reports format, accepted format : "
                     "cppcheck, clang-tidy, boost-test"
                  << std::endl;
        // change process return value
        exitStatus = EXIT_FAILURE;
      }
    }
    // catch all exception to have a managed return with error log
  } catch (const std::exception &ex) {
    std::cerr << "Unexpected Fatal Error : " << ex.what() << std::endl;
    // change process return value
    exitStatus = EXIT_FAILURE;
  }
  return exitStatus;
}
