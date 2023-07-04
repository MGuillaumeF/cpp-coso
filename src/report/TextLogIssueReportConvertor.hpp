#ifndef __TEXT_LOG_ISSUE_REPORT_CONVERTOR_HPP__
#define __TEXT_LOG_ISSUE_REPORT_CONVERTOR_HPP__

// extend abstract class
#include "./IssueReportConvertor.hpp"
// STL regrex import
#include <regex>

/**
 * @brief abstract class to convert issue report
 */
class TextLogIssueReportConvertor : public IssueReportConvertor {

public:
  /**
   * @brief Construct a new Report Convertor object
   * @param engineId The engine Id to identify tools
   * @param pattern The regexp pattern to extract data from log text row
   *
   */
  explicit TextLogIssueReportConvertor(const std::string &engineId,
                                       const std::string &pattern)
      : m_engineId(engineId), m_pattern(pattern){};
  /**
   * @brief Destroy the Report Convertor object
   *
   */
  ~TextLogIssueReportConvertor() override = default;

  /**
   */
  TextLogIssueReportConvertor(const TextLogIssueReportConvertor &) = delete;
  /**
   */
  TextLogIssueReportConvertor(TextLogIssueReportConvertor &&) = delete;
  /**
   */
  TextLogIssueReportConvertor &
  operator=(const TextLogIssueReportConvertor &) = delete;
  /**
   */
  TextLogIssueReportConvertor &
  operator=(TextLogIssueReportConvertor &&) = delete;

  /**
   * @brief Get the Issue Severity object
   *
   * @param reportSeverity
   * @return const ESonarCloudSeverity
   */
  virtual ESonarCloudSeverity
  getMappedIssueSeverity(const std::string &reportSeverity);

  /**
   * @brief Get the Issue object
   *
   * @param match The regexp match of row
   * @return Issue
   */
  virtual Issue getMappedIssue(const std::smatch &match) = 0;

private:
  /**
   * @brief The engine Id of convertor
   *
   */
  std::string m_engineId;
  /**
   * @brief The regexp pattern to extract data from log text row
   *
   */
  std::string m_pattern;

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
