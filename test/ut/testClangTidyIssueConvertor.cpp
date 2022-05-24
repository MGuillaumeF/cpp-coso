#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../../src/Application.hpp"
#include "../../src/exception/ConversionException.hpp"
#include "../../src/report/ClangTidyIssueReportConvertor.hpp"

const std::string CLANG_TIDY_WEBSERVER_RESOURCES_DIR = "./resources/boost/";

BOOST_AUTO_TEST_SUITE(testsClangTidyConvertor)

BOOST_AUTO_TEST_CASE(testClangTidyToSonarQube) {

  BOOST_CHECK(
      (Application::run(
           {"clang-tidy", "./resources/clang_tidy_report.txt",
            "./resources/clang_tidy_report_sonarqube_test-generation.txt"}) ==
       EXIT_SUCCESS));
}

bool conversionExceptionMessage(const ConversionException &ex) {
  const std::string errorMessage = "The file \"./not_exist.txt\" not exist";
  BOOST_CHECK_EQUAL(ex.what(), errorMessage);
  return true;
}

BOOST_AUTO_TEST_CASE(bad_file_not_found) {
  BOOST_CHECK_EXCEPTION(ClangTidyIssueReportConvertor::getInstance()->convert(
                            {"./not_exist.txt"}, "./not_writed_result.json"),
                        ConversionException, conversionExceptionMessage);
  ClangTidyIssueReportConvertor::getInstance().reset();
}

BOOST_AUTO_TEST_SUITE_END()
