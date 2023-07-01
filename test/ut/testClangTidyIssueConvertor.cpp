#define BOOST_TEST_DYN_LINK
#include <boost/property_tree/json_parser.hpp>
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

  boost::property_tree::ptree outputFile;
  boost::property_tree::read_json(
      "./resources/clang_tidy_report_sonarqube_test-generation.txt",
      outputFile);

  const boost::property_tree::ptree issues = outputFile.get_child("issues");
  BOOST_CHECK_EQUAL(issues.size(), 22);
  const boost::property_tree::ptree firstIssue = issues.front().second;

  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("engineId"), "clang-tidy");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("ruleId"),
                    "cppcoreguidelines-special-member-functions");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("severity"), "MAJOR");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("type"), "CODE_SMELL");
  BOOST_CHECK_EQUAL(
      firstIssue.get<std::string>("primaryLocation.message"),
      "class 'IssueReportConvertor' defines a non-default destructor but does "
      "not define a copy constructor, a copy assignment operator, a move "
      "constructor or a move assignment operator ");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("primaryLocation.filePath"),
                    "\/home\/runner\/work\/cpp-coso\/cpp-coso\/src\/report\/."
                    "\/IssueReportConvertor.hpp");
  BOOST_CHECK_EQUAL(
      firstIssue.get<uint64_t>("primaryLocation.textRange.startLine"), 17);
  BOOST_CHECK_EQUAL(
      firstIssue.get<uint64_t>("primaryLocation.textRange.startColumn"), 6);
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
