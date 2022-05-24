#include "TestConvertor.hpp"

// boost xml import
#include <boost/property_tree/xml_parser.hpp>

#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <map>
#include <regex>

/**
 * @brief map to convert boost test node name to sonar test result leveling
 *
 * @return const std::map<std::string, std::string, std::less<>>
 */
const std::map<std::string, std::string, std::less<>>
    boostSonarState({{"passed with warnings", "error"},
                     {"failed", "failure"},
                     {"skipped", "skipped"},
                     {"aborted", "skipped"}});

/**
 * @brief Save the Result of test in Map object
 *
 * @param modulePtreeResult The property tree of result test suite of test
 * report
 * @param caseResult The map to update
 */
void TestConvertor::provideMapResultTests(
    const boost::property_tree::ptree &modulePtreeResult,
    std::map<std::string, std::string, std::less<>> &caseResult) {
  for (const auto &[modulePtreeResultKey, modulePtreeResultValue] :
       modulePtreeResult) {
    if ("TestSuite" == modulePtreeResultKey) {
      const std::string testSuiteName =
          modulePtreeResultValue.get<std::string>("<xmlattr>.name");
      std::cout << "test suite found with name : " << testSuiteName
                << " and state : "
                << modulePtreeResultValue.get<std::string>("<xmlattr>.result")
                << std::endl;

      for (const auto &[key, value] : modulePtreeResultValue) {
        if ("TestCase" == key) {
          const std::string testCaseName =
              value.get<std::string>("<xmlattr>.name");
          const std::string testCaseResult =
              value.get<std::string>("<xmlattr>.result");
          std::cout << "test case found with name : " << testCaseName
                    << " and state : " << testCaseResult << std::endl;
          if (testCaseResult != "passed") {
            const std::string sonarState =
                boostSonarState.contains(testCaseResult)
                    ? boostSonarState.at(testCaseResult)
                    : "error";
            caseResult.try_emplace(testSuiteName + "." + testCaseName,
                                   testCaseResult);
          }
        } else if ("<xmlattr>" != key) {
          std::cout << "test case not found at key : " << key << std::endl;
        }
      }
    } else if ("<xmlattr>" != modulePtreeResultKey) {
      std::cout << "test suite not found at key : " << modulePtreeResultKey
                << std::endl;
    }
  }
}

/**
 * @brief method to extract data case from log result test report to convert to
 * sonarqube report
 *
 * @param source The source property tree where search test cases data
 * @param destination The destination where save formated data case result
 */
void TestConvertor::extractCaseDatas(const boost::property_tree::ptree &source,
                                     boost::property_tree::ptree &destination) {
  for (const auto &[caseDataKey, caseDataValue] : source) {
    if (caseDataKey == "Error") {

      boost::property_tree::ptree errorPtree(
          caseDataValue.get_value<std::string>());
      errorPtree.put("<xmlattr>.message",
                     "Error at line " +
                         caseDataValue.get<std::string>("<xmlattr>.line"));

      destination.push_back(
          boost::property_tree::ptree::value_type("error", errorPtree));
    } else if (caseDataKey == "Exception") {

      boost::property_tree::ptree errorPtree(
          caseDataValue.get_value<std::string>());
      errorPtree.put("<xmlattr>.message",
                     "Exception at line " +
                         caseDataValue.get<std::string>("<xmlattr>.line"));
      destination.push_back(
          boost::property_tree::ptree::value_type("skipped", errorPtree));
    }
  }
}

/**
 * @brief Function to convert unified boost report to sonar generic report
 *
 * @param pathToLogXML The log of boost tests result, XML format required
 * @param pathToResultXML The Result report of boost tests result, XML format
 * required
 * @return boost::property_tree::ptree The Sonar Generic Test reprt format ptree
 */
boost::property_tree::ptree
TestConvertor::boostReportsToSonarReport(const std::string &pathToLogXML,
                                         const std::string &pathToResultXML) {

  boost::property_tree::ptree logReport;
  boost::property_tree::ptree resultReport;

  boost::property_tree::ptree sonarReport;

  boost::property_tree::read_xml(pathToLogXML, logReport);
  boost::property_tree::read_xml(pathToResultXML, resultReport);

  const boost::property_tree::ptree modulePtreeResult =
      resultReport.get_child("TestResult.TestSuite");
  std::map<std::string, std::string, std::less<>> caseResult;

  provideMapResultTests(modulePtreeResult, caseResult);

  std::map<std::string, boost::property_tree::ptree, std::less<>> mapFilesPtree;

  for (const auto &[modulePtreeLogKey, modulePtreeLogValue] :
       logReport.get_child("TestLog.TestSuite")) {
    if ("TestSuite" == modulePtreeLogKey) {
      const std::string testSuiteName =
          modulePtreeLogValue.get<std::string>("<xmlattr>.name");
      std::cout << "test suite found with name : " << testSuiteName
                << std::endl;

      for (const auto &[key, value] : modulePtreeLogValue) {
        if ("TestCase" == key) {
          const std::string testCaseName =
              value.get<std::string>("<xmlattr>.name");
          const std::string testCaseFile =
              value.get<std::string>("<xmlattr>.file");
          const std::string testCaseDuration =
              value.get<std::string>("TestingTime");
          const std::string testCaseResult =
              caseResult.contains(testSuiteName + "." + testCaseName)
                  ? caseResult.at(testSuiteName + "." + testCaseName)
                  : "passed";

          std::cout << "test case found with name : " << testCaseName
                    << " with state " << testCaseResult
                    << " in : " << testCaseFile << " with duration "
                    << testCaseDuration << std::endl;
          if (!mapFilesPtree.contains(testCaseFile)) {
            boost::property_tree::ptree filePtree;
            boost::property_tree::ptree casePtree;

            boost::property_tree::ptree testCaseContent;
            if (testCaseResult != "passed") {
              boost::property_tree::ptree defaultErrorPtree("no data");
              defaultErrorPtree.put("<xmlattr>.message", "unknown");

              extractCaseDatas(value, testCaseContent);
            }
            casePtree.push_back(boost::property_tree::ptree::value_type(
                "testCase", testCaseContent));
            casePtree.put("testCase.<xmlattr>.name", testCaseName);
            casePtree.put("testCase.<xmlattr>.duration", testCaseDuration);

            filePtree.push_back(
                boost::property_tree::ptree::value_type("file", casePtree));
            filePtree.put("file.<xmlattr>.path", testCaseFile);
            mapFilesPtree.try_emplace(testCaseFile, filePtree);
          } else {
            boost::property_tree::ptree &filePtree =
                mapFilesPtree.at(testCaseFile);
            boost::property_tree::ptree &casePtree = filePtree.add_child(
                "file.testCase", boost::property_tree::ptree());

            if (testCaseResult != "passed") {
              extractCaseDatas(value, casePtree);
            }

            casePtree.put("<xmlattr>.name", testCaseName);
            casePtree.put("<xmlattr>.duration", testCaseDuration);
          }

        } else if ("<xmlattr>" != key) {
          std::cout << "test case not found at key : " << key << std::endl;
        }
      }
    } else if ("<xmlattr>" != modulePtreeLogKey) {
      std::cout << "test suite not found at key : " << modulePtreeLogKey
                << std::endl;
    }
  }
  boost::property_tree::ptree temp;
  for (const auto &[filename, fileTree] : mapFilesPtree) {
    std::string convertedPath = filename;
    // replace windows paths to linux format
    std::replace(convertedPath.begin(), convertedPath.end(), '\\', '/');
    // remove ":" of disk windows path if exist
    const std::regex re("([a-zA-Z]):/(.*)");

    // change abosolute path win to Linux
    std::string result;
    std::regex_replace(std::back_inserter(result), convertedPath.begin(),
                       convertedPath.end(), re, "/$1/$2");

    temp.add_child("file", fileTree.get_child("file"))
        .put("<xmlattr>.path", result);
  }
  sonarReport.add_child("testExecutions", temp).put("<xmlattr>.version", "1");

  return sonarReport;
}
