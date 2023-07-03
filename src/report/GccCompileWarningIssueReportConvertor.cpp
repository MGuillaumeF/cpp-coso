#include "./GccCompileWarningIssueReportConvertor.hpp"

std::unique_ptr<GccCompileWarningIssueReportConvertor>
    GccCompileWarningIssueReportConvertor::s_pInstance =
        std::make_unique<GccCompileWarningIssueReportConvertor>();

/**
 * @brief Get instance of singleton GccCompileWarningIssueReportConvertor
 *
 * @return GccCompileWarningIssueReportConvertor* address of
 * GccCompileWarningIssueReportConvertor instance
 */
std::unique_ptr<GccCompileWarningIssueReportConvertor> &
GccCompileWarningIssueReportConvertor::getInstance() {
  return s_pInstance;
}