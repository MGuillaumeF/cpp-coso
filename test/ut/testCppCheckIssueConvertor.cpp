#define BOOST_TEST_DYN_LINK
#include <boost/property_tree/read_json.hpp>
#include <boost/test/unit_test.hpp>

#include "../../src/Application.hpp"
#include "../../src/report/CppCheckIssueReportConvertor.hpp"

BOOST_AUTO_TEST_SUITE(testsCppCheckConvertor)

BOOST_AUTO_TEST_CASE(testConvertCppCheckToSonarQube) {

  BOOST_CHECK((Application::run({"cppcheck", "./resources/cppcheck_report.xml",
                                 "./resources/cppcheck_report_result.json"}) ==
               EXIT_SUCCESS));

  const boost::property_tree::ptree outputFile;
  boost::property_tree::read_json("./resources/cppcheck_report_result.json",
                                  outputFile);

  const boost::property_tree::ptree issues = outputFile.get_child("issues");
  BOOST_CHECK_EQUAL(issues.size(), 7);
  const boost::property_tree::ptree firstIssue = issues.front().second;

  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("engineId"), "cppcheck-2.4.1");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("ruleId"), "uninitMemberVar");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("severity"), "MAJOR");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("type"), "CODE_SMELL");
  BOOST_CHECK_EQUAL(
      firstIssue.get<std::string>("primaryLocation.message"),
      "Member variable 'user::id_' is not initialized in the constructor.");
  BOOST_CHECK_EQUAL(firstIssue.get<std::string>("primaryLocation.filePath"),
                    "data-management\/src\/model\/user.hxx");
  BOOST_CHECK_EQUAL(
      firstIssue.get<uint64_t>("primaryLocation.textRange.startLine"), 15);
  BOOST_CHECK_EQUAL(
      firstIssue.get<uint64_t>("primaryLocation.textRange.startLine"), 2);
}

BOOST_AUTO_TEST_SUITE_END()
