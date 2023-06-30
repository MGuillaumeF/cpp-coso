#ifndef __GCC_COMPILE_WARNING_ISSUE_REPORT_CONVERTOR_HPP__
#define __GCC_COMPILE_WARNING_ISSUE_REPORT_CONVERTOR_HPP__

// extend abstract class
#include "./GccCompileLogIssueReportConvertor.hpp"

/**
 * @brief abstract class to convert issue report
 */
class GccCompileWarningIssueReportConvertor
    : public GccCompileLogIssueReportConvertor {

public:
  /**
   * @brief Construct a new Report Convertor object
   *
   */
  GccCompileWarningIssueReportConvertor()
      : GccCompileLogIssueReportConvertor("gcc-warning"){};
  /**
   * @brief Destroy the Report Convertor object
   *
   */
  ~GccCompileWarningIssueReportConvertor() override = default;

  /**
   */
  GccCompileWarningIssueReportConvertor(
      const GccCompileWarningIssueReportConvertor &) = delete;
  /**
   */
  GccCompileWarningIssueReportConvertor(
      GccCompileWarningIssueReportConvertor &&) = delete;
  /**
   */
  GccCompileWarningIssueReportConvertor &
  operator=(const GccCompileWarningIssueReportConvertor &) = delete;
  /**
   */
  GccCompileWarningIssueReportConvertor &
  operator=(GccCompileWarningIssueReportConvertor &&) = delete;

  /**
   * @brief Get the Issue Severity object
   *
   * @param reportSeverity
   * @return const ESonarCloudSeverity
   */
  const ESonarCloudSeverity
  getMappedIssueSeverity(const std::string &reportSeverity) override;

  /**
   * @brief Get instance of singleton GccCompileWarningIssueReportConvertor
   *
   * @return GccCompileWarningIssueReportConvertor* address of
   * GccCompileWarningIssueReportConvertor instance
   */
  static std::unique_ptr<GccCompileWarningIssueReportConvertor> &getInstance();

private:
  static std::unique_ptr<GccCompileWarningIssueReportConvertor> s_pInstance;
};
#endif
