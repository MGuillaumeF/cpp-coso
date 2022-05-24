#ifndef __Test_Convertor_HPP__
#define __Test_Convertor_HPP__

// std imports
#include <map>
#include <string>
// boost import
#include <boost/property_tree/ptree.hpp>

/**
 * @brief class to convert cppcheck xml report to sonarqube json report
 *
 */
class TestConvertor {

public:
  /**
   * @brief Construct a new TestConvertor object
   *
   */
  TestConvertor() = delete;

  /**
   * @brief Save the Result of test in Map object
   *
   * @param modulePtreeResult The property tree of result test suite of test
   * report
   * @param caseResult The map to update
   */
  static void provideMapResultTests(
      const boost::property_tree::ptree &modulePtreeResult,
      std::map<std::string, std::string, std::less<>> &caseResult);

  /**
   * @brief method to extract data case from log result test report to convert
   * to sonarqube report
   *
   * @param source The source property tree where search test cases data
   * @param destination The destination where save formated data case result
   */
  static void extractCaseDatas(const boost::property_tree::ptree &source,
                               boost::property_tree::ptree &destination);

  /**
   * @brief Function to convert unified boost report to sonar generic report
   *
   * @param pathToLogXML The log of boost tests result, XML format required
   * @param pathToResultXML The Result report of boost tests result, XML format
   * required
   * @return boost::property_tree::ptree The Sonar Generic Test reprt format
   * ptree
   */
  static boost::property_tree::ptree
  boostReportsToSonarReport(const std::string &pathToLogXML,
                            const std::string &pathToResultXML);
};
#endif
