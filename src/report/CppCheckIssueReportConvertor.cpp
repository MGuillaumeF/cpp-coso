#include "./CppCheckIssueReportConvertor.hpp"

// boost xml import
#include <boost/property_tree/xml_parser.hpp>

#include <map>

/**
 * @brief map to convert cppcheck severity to sonacloud severity
 *
 */
const std::map<std::string, ESonarCloudSeverity, std::less<>>
    cppcheckToSonarCloudSeverity = {
        // INFO
        {"none", ESonarCloudSeverity::INFO},
        {"debug", ESonarCloudSeverity::INFO},
        {"information", ESonarCloudSeverity::INFO},
        // MINOR
        {"style", ESonarCloudSeverity::MINOR},
        // MAJOR
        {"warning", ESonarCloudSeverity::MAJOR},
        {"portability", ESonarCloudSeverity::MAJOR},
        // CRITICAL
        {"performance", ESonarCloudSeverity::CRITICAL},
        // BLOCKER
        {"error", ESonarCloudSeverity::BLOCKER}};

/**
 * @brief method to processing entries to change data format
 *
 * @param entries The list of entries files
 * @return The property tree result of conversion
 */
boost::property_tree::ptree CppCheckIssueReportConvertor::processing(
    const std::list<boost::filesystem::path> &entries) {

  // read XML cpp check report file
  boost::property_tree::ptree cppCheckReport;
  boost::property_tree::read_xml((entries.front()).string(), cppCheckReport);

  // init empty property tree to save convert result
  boost::property_tree::ptree sonarQubeReport;

  // get cppcheck version to generate engineId of issues
  const std::string cppckecVerison =
      cppCheckReport.get<std::string>("results.cppcheck.<xmlattr>.version");

  const boost::property_tree::ptree errors =
      cppCheckReport.get_child("results.errors");

  boost::property_tree::ptree issues;

  // for each error
  for (const auto &[errorTagName, error] : errors) {
    boost::property_tree::ptree issue;
    // generate engineId with cppcheck version
    issue.put<std::string>("engineId", "cppcheck-" + cppckecVerison);
    const std::string ruleId = error.get<std::string>("<xmlattr>.id");
    const std::string severity = error.get<std::string>("<xmlattr>.severity");

    // the ruleId is the error Id
    issue.put<std::string>("ruleId", ruleId);

    // The severity is calculated and translated
    issue.put<std::string>("severity",
                           IssueReportConvertor::SonarCloudSeverityValue.at(
                               cppcheckToSonarCloudSeverity.at(severity)));

    // all issues have type CODE_SMELL
    issue.put<std::string>("type", "CODE_SMELL");
    const std::string message = error.get<std::string>("<xmlattr>.msg");

    // the boolean "first" is to detect if issue is the first occurency
    bool first = true;
    boost::property_tree::ptree secondaryLocations;
    for (const auto &[errorChildNodeKey, errorChildNodeContent] : error) {
      if (errorChildNodeKey == "location") {
        const std::string filePath =
            errorChildNodeContent.get<std::string>("<xmlattr>.file");

        boost::property_tree::ptree location;
        location.put<std::string>("message", message);
        location.put<std::string>("filePath", filePath);

        // add text range to get location of error
        boost::property_tree::ptree textRange;
        const std::string line =
            errorChildNodeContent.get<std::string>("<xmlattr>.line");
        // the line 0 not exist if error is at line 0 (all file for example),
        // move issue at the first line of file
        textRange.put<std::string>("startLine", line == "0" ? "1" : line);
        textRange.put<std::string>(
            "startColumn",
            errorChildNodeContent.get<std::string>("<xmlattr>.column"));
        location.add_child("textRange", textRange);

        // if it's first occurency of error add in primary place
        if (first) {
          issue.add_child("primaryLocation", location);
          first = false;
        } else {
          // else add in secondary place
          secondaryLocations.push_back(
              std::pair<const std::string, boost::property_tree::ptree>(
                  "", location));
        }
      }
    }

    // add secondary locations if ptree is not empty
    // optional field
    if (secondaryLocations.size() > 0) {
      issue.add_child("secondaryLocations", secondaryLocations);
    }

    // if the issue haven't primaryLocation we don't push the issue because it's
    // a mandatory field
    if (!first) {
      issues.push_back(
          std::pair<const std::string, boost::property_tree::ptree>("", issue));
    }
  }

  sonarQubeReport.add_child("issues", issues);

  return sonarQubeReport;
}

std::unique_ptr<CppCheckIssueReportConvertor>
    CppCheckIssueReportConvertor::s_pInstance =
        std::make_unique<CppCheckIssueReportConvertor>();

/**
 * @brief Get instance of singleton CppCheckIssueReportConvertor
 *
 * @return CppCheckIssueReportConvertor* address of CppCheckIssueReportConvertor
 * instance
 */
std::unique_ptr<CppCheckIssueReportConvertor> &
CppCheckIssueReportConvertor::getInstance() {
  return s_pInstance;
}