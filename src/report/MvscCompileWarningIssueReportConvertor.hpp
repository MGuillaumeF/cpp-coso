#ifndef __MVSC_COMPILE_LOG_ISSUE_REPORT_CONVERTOR_HPP__
#define __MVSC_COMPILE_LOG_ISSUE_REPORT_CONVERTOR_HPP__

// extend abstract class
#include "./TextLogIssueReportConvertor.hpp"

/**
 * @brief abstract class to convert issue report
 */
class MvscCompileWarningIssueReportConvertor
    : public TextLogIssueReportConvertor {

public:
  /**
   * @brief Construct a new Report Convertor objec
   *
   */
  MvscCompileWarningIssueReportConvertor()
      : TextLogIssueReportConvertor(
            "mvsc-warning",
            "(.+\\.[chi](?:pp|xx)?)\\((\\d+),(\\d+)\\):\\s([a-z]+)"
            "\\s(C\\d+):\\s'.+': (.+)\\s\\[.+\\]"){};

  /**
   * @brief Destroy the Report Convertor object
   *
   */
  ~MvscCompileWarningIssueReportConvertor() override = default;

  /**
   */
  MvscCompileWarningIssueReportConvertor(
      const MvscCompileWarningIssueReportConvertor &) = delete;
  /**
   */
  MvscCompileWarningIssueReportConvertor(
      MvscCompileWarningIssueReportConvertor &&) = delete;
  /**
   */
  MvscCompileWarningIssueReportConvertor &
  operator=(const MvscCompileWarningIssueReportConvertor &) = delete;
  /**
   */
  MvscCompileWarningIssueReportConvertor &
  operator=(MvscCompileWarningIssueReportConvertor &&) = delete;

  /**
   * @brief Get the Issue object
   *
   * @param match The regexp match of row
   * @return Issue
   */
   Issue getMappedIssue(const std::smatch &match) override;

  /**
   * @brief Get instance of singleton MvscCompileWarningIssueReportConvertor
   *
   * @return MvscCompileWarningIssueReportConvertor* address of
   * MvscCompileWarningIssueReportConvertor instance
   */
  static std::unique_ptr<MvscCompileWarningIssueReportConvertor> &getInstance();

private:
  static std::unique_ptr<MvscCompileWarningIssueReportConvertor> s_pInstance;
};
#endif
