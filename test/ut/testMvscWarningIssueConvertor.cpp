#define BOOST_TEST_DYN_LINK
#include <boost/property_tree/json_parser.hpp>
#include <boost/test/unit_test.hpp>

#include "../../src/Application.hpp"

BOOST_AUTO_TEST_SUITE(testsMvscWarningkConvertor)

BOOST_AUTO_TEST_CASE(testConvertMvscWarningToSonarQube) {

  BOOST_CHECK(
      (Application::run({"mvsc-warning", "./resources/mvsc-warning-report.txt",
                         "./resources/mvsc-warning-sonarqube-report.json"}) ==
       EXIT_SUCCESS));

  boost::property_tree::ptree outputFile;
  boost::property_tree::read_json(
      "./resources/mvsc-warning-sonarqube-report.json", outputFile);

  const boost::property_tree::ptree issues = outputFile.get_child("issues");
  BOOST_CHECK_EQUAL(issues.size(), 30);
  const boost::property_tree::ptree firstIssue = issues.front().second;

  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("engineId"), "mvsc-warning");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("ruleId"), "C4514");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("severity"), "MAJOR");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("type"), "CODE_SMELL");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("primaryLocation.message"),
                    "unreferenced inline function has been removed");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("primaryLocation.filePath"),
                    "D:\\a\\cpp-coso\\cpp-"
                    "coso\\src\\report\/ClangTidyIssueReportConvertor.hpp");
  BOOST_CHECK_EQUAL(
      firstIssue.get<uint64_t>("primaryLocation.textRange.startLine"), 17);
  BOOST_CHECK_EQUAL(
      firstIssue.get<uint64_t>("primaryLocation.textRange.startColumn"), 2);
}

BOOST_AUTO_TEST_SUITE_END()
