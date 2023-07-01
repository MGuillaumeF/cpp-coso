#ifndef __ISSUE_REPORT_CONVERTOR_HPP__
#define __ISSUE_REPORT_CONVERTOR_HPP__

// extend abstract class
#include "./ReportConvertor.hpp"
#include <map>

/**
 * @brief SonarCloud severity levels of issues
 *
 */
enum class ESonarCloudSeverity { INFO, MINOR, MAJOR, CRITICAL, BLOCKER };

/**
 * @brief The issue structure to complete for each item parsed
 *
 */
struct Issue {
  /**
   * @brief The path of source file where the issue is found
   *
   */
  std::string source_file;
  /**
   * @brief The row where issue is raised in source file (start at index 1)
   *
   */
  uint64_t line;
  /**
   * @brief The column where issue is raised in source file (start at index 0)
   *
   */
  uint64_t column;
  /**
   * @brief The severity of issue
   *
   */
  ESonarCloudSeverity severity;
  /**
   * @brief The message to explain the issue
   *
   */
  std::string message;
  /**
   * @brief The rule id to display in sonarqube menu
   *
   */
  std::string rule_id;
};

/**
 * @brief abstract class to convert issue report
 */
class IssueReportConvertor : public ReportConvertor {
public:
  /**
   * @brief Construct a new Report Convertor object
   *
   */
  IssueReportConvertor() = default;
  /**
   * @brief Destroy the Report Convertor object
   *
   */
  ~IssueReportConvertor() override = default;
  /**
   * @brief map to convert cppcheck severity to sonacloud severity
   *
   */
  static const std::map<ESonarCloudSeverity, std::string, std::less<>>
      SonarCloudSeverityValue;
  /**
   */
  IssueReportConvertor(const IssueReportConvertor &) = delete;
  /**
   */
  IssueReportConvertor(IssueReportConvertor &&) = delete;
  /**
   */
  IssueReportConvertor &operator=(const IssueReportConvertor &) = delete;
  /**
   */
  IssueReportConvertor &operator=(IssueReportConvertor &&) = delete;

private:
  /**
   * @brief method to check if the result of conversion is valid
   *
   * @param report The report to check
   * @return true The result report is valid
   * @return false The result report is not valid
   */
  bool verifyResultReport(const boost::property_tree::ptree &report) override;
};
#endif
