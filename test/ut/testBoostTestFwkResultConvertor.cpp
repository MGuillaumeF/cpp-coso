#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
// boost xml import
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <exception>
#include <set>
#include <string>

#include "../../src/report/TestConvertor.hpp"

const std::string TEST_BOOST_RESOURCES_DIR = "./resources/boost/";

BOOST_AUTO_TEST_SUITE(boostTestFrameworksConvertor)

BOOST_AUTO_TEST_CASE(testValidBoostResultReport) {
  const boost::property_tree::ptree sonarReport =
      TestConvertor::boostReportsToSonarReport(
          TEST_BOOST_RESOURCES_DIR + "reports.xml",
          TEST_BOOST_RESOURCES_DIR + "reportUT.xml");

  BOOST_CHECK_EQUAL(
      sonarReport.get<std::string>("testExecutions.<xmlattr>.version"), "1");
  std::set<std::string> files{"testBoostTestFwkResultConvertor.cpp",
                              "testClangTidyIssueConvertor.cpp",
                              "testCppCheckIssueConvertor.cpp"};

  uint8_t count = 0;
  for (const auto &[testExecutionsChildKey, testExecutionsValue] :
       sonarReport.get_child("testExecutions")) {
    if (testExecutionsChildKey == "file") {
      count += 1;
      const std::string filename =
          boost::filesystem::path(
              testExecutionsValue.get<std::string>("<xmlattr>.path"))
              .make_preferred()
              .filename()
              .string();
      BOOST_CHECK(files.find(filename) != files.end());
      for (const auto &[testCaseKey, testCaseValue] : testExecutionsValue) {

        if (testCaseKey == "testCase") {
          BOOST_CHECK(testCaseValue.get<std::string>("<xmlattr>.name") != "");
          BOOST_CHECK(testCaseValue.get<uint64_t>("<xmlattr>.duration") >= 0);
        }
      }
    }
  }
  // 3 files expected
  BOOST_CHECK_EQUAL(count, 3);
  boost::property_tree::write_xml(
      "./resources/boost/boost-test-sonarqube-report-test.xml", sonarReport);
}

BOOST_AUTO_TEST_SUITE_END()
