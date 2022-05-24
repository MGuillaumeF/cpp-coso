#ifndef __CLANG_TIDY_ISSUE_REPORT_CONVERTOR_HPP__
#define __CLANG_TIDY_ISSUE_REPORT_CONVERTOR_HPP__

// extend abstract class
#include "./IssueReportConvertor.hpp"

/**
 * @brief abstract class to convert issue report
 */
class ClangTidyIssueReportConvertor : public IssueReportConvertor {

public:
  /**
   * @brief Construct a new Report Convertor object
   *
   */
  ClangTidyIssueReportConvertor() = default;
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
   * @brief Get instance of singleton ClangTidyIssueReportConvertor
   *
   * @return ClangTidyIssueReportConvertor* address of
   * ClangTidyIssueReportConvertor instance
   */
  static std::unique_ptr<ClangTidyIssueReportConvertor> &getInstance();

private:
  static std::unique_ptr<ClangTidyIssueReportConvertor> s_pInstance;
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
};
#endif
