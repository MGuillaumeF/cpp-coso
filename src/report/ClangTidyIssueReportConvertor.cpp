#include "./ClangTidyIssueReportConvertor.hpp"
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
 * @brief map to convert clang-tidy severity to sonacloud severity
 *
 */
const std::map<std::string, ESonarCloudSeverity, std::less<>>
    clangTidyToSonarCloudSeverity = {
        // INFOS
        {"none", ESonarCloudSeverity::INFO},
        {"debug", ESonarCloudSeverity::INFO},
        {"information", ESonarCloudSeverity::INFO},
        // MINORS
        {"note", ESonarCloudSeverity::MINOR},
        {"style", ESonarCloudSeverity::MINOR},
        // MAJORS
        {"warning", ESonarCloudSeverity::MAJOR},
        {"portability", ESonarCloudSeverity::MAJOR},
        // CRITICAL
        {"performance", ESonarCloudSeverity::CRITICAL},
        // BLOCKERS
        {"error", ESonarCloudSeverity::BLOCKER}};

/**
 * @brief Get the Issue Severity object
 *
 * @param reportSeverity
 * @return const ESonarCloudSeverity
 */
const ESonarCloudSeverity ClangTidyIssueReportConvertor::getMappedIssueSeverity(
    const std::string &reportSeverity) {
  // check issue level is known by tool and sonar
  if (!clangTidyToSonarCloudSeverity.contains(reportSeverity)) {
    std::cerr << "Map error : unknown severity '" << reportSeverity << "' "
              << std::endl;
    throw ConversionException("Map error : unknown severity");
  }
  return clangTidyToSonarCloudSeverity.at(reportSeverity);
}

std::unique_ptr<ClangTidyIssueReportConvertor>
    ClangTidyIssueReportConvertor::s_pInstance =
        std::make_unique<ClangTidyIssueReportConvertor>();

/**
 * @brief Get instance of singleton ClangTidyIssueReportConvertor
 *
 * @return ClangTidyIssueReportConvertor* address of
 * ClangTidyIssueReportConvertor instance
 */
std::unique_ptr<ClangTidyIssueReportConvertor> &
ClangTidyIssueReportConvertor::getInstance() {
  return s_pInstance;
}