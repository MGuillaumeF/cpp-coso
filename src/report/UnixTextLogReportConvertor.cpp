#include "./UnixTextLogReportConvertor.hpp"

/**
 * @brief Get the Issue object
 *
 * @param match The regexp match of row
 * @return const Issue
 */
const Issue
UnixTextLogReportConvertor::getMappedIssue(const std::smatch &match) {
  Issue issue;
  issue.source_file = match.str(1);
  issue.line = std::stoull(match.str(2));
  issue.column = std::stoull(match.str(3));
  issue.severity = getMappedIssueSeverity(match.str(4));
  issue.message = match.str(5);
  issue.rule_id = match.str(6);
  return issue;
}
