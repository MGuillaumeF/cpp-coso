#ifndef __MVSC_COMPILE_LOG_ISSUE_REPORT_CONVERTOR_HPP__
#define __MVSC_COMPILE_LOG_ISSUE_REPORT_CONVERTOR_HPP__

// extend abstract class
#include "./IssueReportConvertor.hpp"

/**
 * @brief abstract class to convert issue report
 */
class MvscCompileWarningIssueReportConvertor : public IssueReportConvertor {

public:
  /**
   * @brief Construct a new Report Convertor objec
   *
   */
  MvscCompileWarningIssueReportConvertor() = default;

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
   * @brief Get instance of singleton MvscCompileWarningIssueReportConvertor
   *
   * @return MvscCompileWarningIssueReportConvertor* address of
   * MvscCompileWarningIssueReportConvertor instance
   */
  static std::unique_ptr<MvscCompileWarningIssueReportConvertor> &getInstance();

private:
  /**
   * @brief The engine Id of convertor
   *
   */
  std::string m_engineId = "mvsc-warning";

  /**
   * @brief method to processing entries to change data format
   *
   * @param entries The list of entries files
   * @return The property tree result of conversion
   */
  boost::property_tree::ptree
  processing(const std::list<boost::filesystem::path> &entries) override;

  /**
   * @brief method to build location tree of issue
   *
   * @param message The message of issue
   * @param filePath The file path of origine issue
   * @param line The line of issue
   * @param column The column of issue
   * @return boost::property_tree::ptree The location property tree
   */
  [[nodiscard]] boost::property_tree::ptree
  buildLocationTree(const std::string &message, const std::string &filePath,
                    const std::string &line, const std::string &column) const;

  static std::unique_ptr<MvscCompileWarningIssueReportConvertor> s_pInstance;
};
#endif
