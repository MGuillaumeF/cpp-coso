#include "./MvscCompileWarningIssueReportConvertor.hpp"

/**
 * @brief Get the Issue object
 *
 * @param match The regexp match of row
 * @return const Issue
 */
const Issue MvscCompileWarningIssueReportConvertor::getMappedIssue(
    const std::smatch &match) {
  Issue issue;
  issue.source_file = match.str(1);
  issue.line = std::stoull(match.str(2));
  issue.column = std::stoull(match.str(3));
  issue.severity = getMappedIssueSeverity(match.str(4));
  issue.rule_id = match.str(5);
  issue.message = match.str(6);
  return issue;
}

std::unique_ptr<MvscCompileWarningIssueReportConvertor>
    MvscCompileWarningIssueReportConvertor::s_pInstance =
        std::make_unique<MvscCompileWarningIssueReportConvertor>();

/**
 * @brief Get instance of singleton MvscCompileWarningIssueReportConvertor
 *
 * @return MvscCompileWarningIssueReportConvertor* address of
 * MvscCompileWarningIssueReportConvertor instance
 */
std::unique_ptr<MvscCompileWarningIssueReportConvertor> &
MvscCompileWarningIssueReportConvertor::getInstance() {
  return s_pInstance;
}