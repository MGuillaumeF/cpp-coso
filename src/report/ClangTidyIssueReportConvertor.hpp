#ifndef __CLANG_TIDY_ISSUE_REPORT_CONVERTOR_HPP__
#define __CLANG_TIDY_ISSUE_REPORT_CONVERTOR_HPP__

// extend abstract class
#include "./UnixTextLogReportConvertor.hpp"

/**
 * @brief abstract class to convert issue report
 */
class ClangTidyIssueReportConvertor : public UnixTextLogReportConvertor {

public:
  /**
   * @brief Construct a new Report Convertor object
   *
   */
  ClangTidyIssueReportConvertor() : UnixTextLogReportConvertor("clang-tidy"){};

  /**
   * @brief Destroy the Report Convertor object
   *
   */
  ~ClangTidyIssueReportConvertor() override = default;

  /**
   */
  ClangTidyIssueReportConvertor(const ClangTidyIssueReportConvertor &) = delete;
  /**
   */
  ClangTidyIssueReportConvertor(ClangTidyIssueReportConvertor &&) = delete;
  /**
   */
  ClangTidyIssueReportConvertor &
  operator=(const ClangTidyIssueReportConvertor &) = delete;
  /**
   */
  ClangTidyIssueReportConvertor &
  operator=(ClangTidyIssueReportConvertor &&) = delete;

  /**
   * @brief Get the Issue Severity object
   *
   * @param reportSeverity
   * @return ESonarCloudSeverity
   */
  ESonarCloudSeverity
  getMappedIssueSeverity(const std::string &reportSeverity) override;

  /**
   * @brief Get instance of singleton ClangTidyIssueReportConvertor
   *
   * @return ClangTidyIssueReportConvertor* address of
   * ClangTidyIssueReportConvertor instance
   */
  static std::unique_ptr<ClangTidyIssueReportConvertor> &getInstance();

private:
  static std::unique_ptr<ClangTidyIssueReportConvertor> s_pInstance;
};
#endif
