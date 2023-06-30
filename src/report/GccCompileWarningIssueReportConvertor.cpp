#include "./GccCompileWarningIssueReportConvertor.hpp"
#include "../exception/ConversionException.hpp"

// STL stream import
#include <fstream>
#include <iostream>
#include <sstream>

// STL data container import
#include <list>
#include <map>

// STL regrex import
#include <regex>

/**
 * @brief Get the Issue Severity object
 *
 * @param reportSeverity
 * @return const ESonarCloudSeverity
 */
const ESonarCloudSeverity
GccCompileWarningIssueReportConvertor::getMappedIssueSeverity(
    const std::string &reportSeverity) {
  return ESonarCloudSeverity::MAJOR;
}

std::unique_ptr<GccCompileWarningIssueReportConvertor>
    GccCompileWarningIssueReportConvertor::s_pInstance =
        std::make_unique<GccCompileWarningIssueReportConvertor>();

/**
 * @brief Get instance of singleton GccCompileWarningIssueReportConvertor
 *
 * @return GccCompileWarningIssueReportConvertor* address of
 * GccCompileWarningIssueReportConvertor instance
 */
std::unique_ptr<GccCompileWarningIssueReportConvertor> &
GccCompileWarningIssueReportConvertor::getInstance() {
  return s_pInstance;
}