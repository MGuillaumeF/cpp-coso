#include "./IssueReportConvertor.hpp"
#include <iostream>
#include <set>
#include <string>
/**
 * @brief method to check if the result of conversion is valid
 *
 * @param report The report to check
 * @return true The result report is valid
 * @return false The result report is not valid
 */
bool IssueReportConvertor::verifyResultReport(
    const boost::property_tree::ptree &report) {
  // at the start of validation the property tree is a valide issue list
  bool isValid = true;
  // test if issues exists
  if (const boost::property_tree::ptree issues = report.get_child("issues");
      issues.size() > 0) {
    const std::set<std::string, std::less<>> severityValues = {
        "INFO", "MINOR", "MAJOR", "CRITICAL", "BLOCKER"};
    const std::set<std::string, std::less<>> typeValues = {
        "BUG", "VULNERABILITY", "CODE_SMELL"};
    // for each issue check keys/values of objects
    for (const auto &[key, value] : issues) {
      bool hasValid = true;
      // check all mandatories key a present in issue object
      // free string field
      hasValid &= value.get<std::string>("engineId") != "";
      // free string field
      hasValid &= value.get<std::string>("ruleId") != "";
      // values accepted in list of severityValues
      hasValid &= value.get<std::string>("severity") != "" &&
                  severityValues.contains(value.get<std::string>("severity"));
      // values accepted in list of typeValues
      hasValid &= value.get<std::string>("type") != "" &&
                  typeValues.contains(value.get<std::string>("type"));

      if (!hasValid) {
        // at least one issue in property tree list is an invalid issue so print
        // error and raise exception
        std::cerr << "[ERROR] not issues generated";
        isValid = false;
      }
    }
  } else {
    // an empty issue list is a valid list
    std::cout << "[INFO] not issues generated";
  }
  return isValid;
}

/**
 * @brief map to convert cppcheck severity to sonacloud severity
 *
 */
const std::map<ESonarCloudSeverity, std::string, std::less<>>
    IssueReportConvertor::SonarCloudSeverityValue = {
        {ESonarCloudSeverity::INFO, "INFO"},
        {ESonarCloudSeverity::MINOR, "MINOR"},
        {ESonarCloudSeverity::MAJOR, "MAJOR"},
        {ESonarCloudSeverity::CRITICAL, "CRITICAL"},
        {ESonarCloudSeverity::BLOCKER, "BLOCKER"}};
