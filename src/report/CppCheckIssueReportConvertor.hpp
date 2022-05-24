#ifndef __CPP_CHECK_ISSUE_REPORT_CONVERTOR_HPP__
#define __CPP_CHECK_ISSUE_REPORT_CONVERTOR_HPP__

// extend abstract class
#include "./IssueReportConvertor.hpp"

/**
 * @brief abstract class to convert issue report
 */
class CppCheckIssueReportConvertor : public IssueReportConvertor {
public:
  /**
   * @brief Construct a new Report Convertor object
   *
   */
  CppCheckIssueReportConvertor() = default;
  /**
   * @brief Destroy the Report Convertor object
   *
   */
  ~CppCheckIssueReportConvertor() override = default;

  /**
   */
  CppCheckIssueReportConvertor(const CppCheckIssueReportConvertor &) = delete;
  /**
   */
  CppCheckIssueReportConvertor(CppCheckIssueReportConvertor &&) = delete;
  /**
   */
  CppCheckIssueReportConvertor &
  operator=(const CppCheckIssueReportConvertor &) = delete;
  /**
   */
  CppCheckIssueReportConvertor &
  operator=(CppCheckIssueReportConvertor &&) = delete;
  /**
   * @brief Get instance of singleton CppCheckIssueReportConvertor
   *
   * @return CppCheckIssueReportConvertor* address of
   * CppCheckIssueReportConvertor instance
   */
  static std::unique_ptr<CppCheckIssueReportConvertor> &getInstance();

private:
  static std::unique_ptr<CppCheckIssueReportConvertor> s_pInstance;
  /**
   * @brief method to processing entries to change data format
   *
   * @param entries The list of entries files
   * @return The property tree result of conversion
   */
  boost::property_tree::ptree
  processing(const std::list<boost::filesystem::path> &entries) override;
};
#endif
