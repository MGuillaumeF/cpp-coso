#ifndef __UNIX_TEXT_LOG_REPORT_CONVERTOR_HPP__
#define __UNIX_TEXT_LOG_REPORT_CONVERTOR_HPP__

// extend abstract class
#include "./TextLogIssueReportConvertor.hpp"

/**
 * @brief abstract class to convert issue report
 */
class UnixTextLogReportConvertor : public TextLogIssueReportConvertor {

public:
  /**
   * @brief Construct a new Report Convertor object
   * @param engineId The engine Id to identify tools
   *
   */
  explicit UnixTextLogReportConvertor(const std::string &engineId)
      : TextLogIssueReportConvertor(engineId,
                                    "(.+\\.[ch](?:pp|xx)?):(\\d+):(\\d+):\\s(["
                                    "a-z]+):\\s*(.+)\\[(.+)\\]"){};
  /**
   * @brief Destroy the Report Convertor object
   *
   */
  ~UnixTextLogReportConvertor() override = default;

  /**
   */
  UnixTextLogReportConvertor(const UnixTextLogReportConvertor &) = delete;
  /**
   */
  UnixTextLogReportConvertor(UnixTextLogReportConvertor &&) = delete;
  /**
   */
  UnixTextLogReportConvertor &
  operator=(const UnixTextLogReportConvertor &) = delete;
  /**
   */
  UnixTextLogReportConvertor &operator=(UnixTextLogReportConvertor &&) = delete;

  /**
   * @brief Get the Issue object
   *
   * @param match The regexp match of row
   * @return Issue
   */
  Issue getMappedIssue(const std::smatch &match) override;

  /**
   * @brief Get the Issue Severity object
   *
   * @param reportSeverity
   * @return ESonarCloudSeverity
   */
  ESonarCloudSeverity
  getMappedIssueSeverity(const std::string &reportSeverity) override {
    return TextLogIssueReportConvertor::getMappedIssueSeverity(reportSeverity);
  };
};
#endif
