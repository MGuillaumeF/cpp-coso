#define BOOST_TEST_DYN_LINK
#include <boost/property_tree/json_parser.hpp>
#include <boost/test/unit_test.hpp>

#include "../../src/Application.hpp"

BOOST_AUTO_TEST_SUITE(testsGccWarningkConvertor)

BOOST_AUTO_TEST_CASE(testConvertGccWarningToSonarQube) {

  BOOST_CHECK(
      (Application::run({"gcc-warning", "./resources/gcc-warning-report.txt",
                         "./resources/gcc-warning-sonarqube-report.json"}) ==
       EXIT_SUCCESS));

  boost::property_tree::ptree outputFile;
  boost::property_tree::read_json(
      "./resources/gcc-warning-sonarqube-report.json", outputFile);

  const boost::property_tree::ptree issues = outputFile.get_child("issues");
  BOOST_CHECK_EQUAL(issues.size(), 1);
  const boost::property_tree::ptree firstIssue = issues.front().second;

  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("engineId"), "gcc-warning");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("ruleId"), "-Wtype-limits");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("severity"), "MAJOR");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("type"), "CODE_SMELL");
  BOOST_CHECK_EQUAL(
      firstIssue.get<std::string>("primaryLocation.message"),
      "comparison of unsigned expression in ‘>= 0’ is always true ");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("primaryLocation.filePath"),
                    "/home/runner/work/cpp-coso/cpp-coso/test/ut/"
                    "testBoostTestFwkResultConvertor.cpp");
  BOOST_CHECK_EQUAL(
      firstIssue.get<uint64_t>("primaryLocation.textRange.startLine"), 44);
  BOOST_CHECK_EQUAL(
      firstIssue.get<uint64_t>("primaryLocation.textRange.startColumn"), 72);
}

BOOST_AUTO_TEST_SUITE_END()
