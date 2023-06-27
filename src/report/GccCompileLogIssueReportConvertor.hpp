#ifndef __GCC_COMPILE_LOG_ISSUE_REPORT_CONVERTOR_HPP__
#define __GCC_COMPILE_LOG_ISSUE_REPORT_CONVERTOR_HPP__

// extend abstract class
#include "./IssueReportConvertor.hpp"

/**
 * @brief abstract class to convert issue report
 */
class GccCompileLogIssueReportConvertor : public IssueReportConvertor {

public:
  /**
   * @brief Construct a new Report Convertor object
   * @param engineId Th engine Id to identify tools
   *
   */
  GccCompileLogIssueReportConvertor(const std::string &engineId)
      : m_engineId(engineId){};
  /**
   * @brief Destroy the Report Convertor object
   *
   */
  ~GccCompileLogIssueReportConvertor() override = default;

  /**
   */
  GccCompileLogIssueReportConvertor(const GccCompileLogIssueReportConvertor &) =
      delete;
  /**
   */
  GccCompileLogIssueReportConvertor(GccCompileLogIssueReportConvertor &&) =
      delete;
  /**
   */
  GccCompileLogIssueReportConvertor &
  operator=(const GccCompileLogIssueReportConvertor &) = delete;
  /**
   */
  GccCompileLogIssueReportConvertor &
  operator=(GccCompileLogIssueReportConvertor &&) = delete;

  /**
   * @brief Get the Issue Severity object
   *
   * @param reportSeverity
   * @return const ESonarCloudSeverity
   */
  virtual const ESonarCloudSeverity
  getMappedIssueSeverity(const std::string &reportSeverity) = 0;

private:
  /**
   * @brief The engine Id of convertor
   *
   */
  std::string m_engineId;

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
