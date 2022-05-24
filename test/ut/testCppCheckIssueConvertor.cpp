#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "../../src/Application.hpp"
#include "../../src/report/CppCheckIssueReportConvertor.hpp"

BOOST_AUTO_TEST_SUITE(testsCppCheckConvertor)

BOOST_AUTO_TEST_CASE(testConvertCppCheckToSonarQube) {

  BOOST_CHECK((Application::run({"cppcheck", "./resources/cppcheck_report.xml",
                                 "./resources/cppcheck_report_result.json"}) ==
               EXIT_SUCCESS));
}

BOOST_AUTO_TEST_SUITE_END()
