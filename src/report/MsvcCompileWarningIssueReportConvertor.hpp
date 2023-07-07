#ifndef __MSVC_COMPILE_LOG_ISSUE_REPORT_CONVERTOR_HPP__
#define __MSVC_COMPILE_LOG_ISSUE_REPORT_CONVERTOR_HPP__

// extend abstract class
#include "./TextLogIssueReportConvertor.hpp"

/**
 * @brief abstract class to convert issue report
 */
class MsvcCompileWarningIssueReportConvertor
    : public TextLogIssueReportConvertor {

public:
  /**
   * @brief Construct a new Report Convertor objec
   *
   */
  MsvcCompileWarningIssueReportConvertor()
      : TextLogIssueReportConvertor(
            "msvc-warning",
            "(.+\\.[chi](?:pp|xx)?)\\((\\d+),(\\d+)\\):\\s([a-z]+)"
            "\\s(C\\d+):\\s'.+': (.+)\\s\\[.+\\]"){};

  /**
   * @brief Destroy the Report Convertor object
   *
   */
  ~MsvcCompileWarningIssueReportConvertor() override = default;

  /**
   */
  MsvcCompileWarningIssueReportConvertor(
      const MsvcCompileWarningIssueReportConvertor &) = delete;
  /**
   */
  MsvcCompileWarningIssueReportConvertor(
      MsvcCompileWarningIssueReportConvertor &&) = delete;
  /**
   */
  MsvcCompileWarningIssueReportConvertor &
  operator=(const MsvcCompileWarningIssueReportConvertor &) = delete;
  /**
   */
  MsvcCompileWarningIssueReportConvertor &
  operator=(MsvcCompileWarningIssueReportConvertor &&) = delete;

  /**
   * @brief Get the Issue object
   *
   * @param match The regexp match of row
   * @return Issue
   */
  Issue getMappedIssue(const std::smatch &match) override;

  /**
   * @brief Get instance of singleton MsvcCompileWarningIssueReportConvertor
   *
   * @return MsvcCompileWarningIssueReportConvertor* address of
   * MsvcCompileWarningIssueReportConvertor instance
   */
  static std::unique_ptr<MsvcCompileWarningIssueReportConvertor> &getInstance();

private:
  static std::unique_ptr<MsvcCompileWarningIssueReportConvertor> s_pInstance;
};
#endif
