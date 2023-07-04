#include "./UnixTextLogReportConvertor.hpp"

/**
 * @brief Get the Issue object
 *
 * @param match The regexp match of row
 * @return Issue
 */
Issue
UnixTextLogReportConvertor::getMappedIssue(const std::smatch &match) {
  const uint8_t SOURCE_FILE_RG_POS = 1;
  const uint8_t LINE_RG_POS = 2;
  const uint8_t COLUMN_RG_POS = 3;
  const uint8_t SEVERITY_RG_POS = 4;
  const uint8_t MESSAGE_RG_POS = 5;
  const uint8_t RULE_ID_RG_POS = 6;
  Issue issue;
  issue.source_file = match.str(SOURCE_FILE_RG_POS);
  issue.line = std::stoull(match.str(LINE_RG_POS));
  issue.column = std::stoull(match.str(COLUMN_RG_POS));
  issue.severity = getMappedIssueSeverity(match.str(SEVERITY_RG_POS));
  issue.message = match.str(MESSAGE_RG_POS);
  issue.rule_id = match.str(RULE_ID_RG_POS);
  return issue;
}
