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
