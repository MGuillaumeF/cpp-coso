#include "./MvscCompileWarningIssueReportConvertor.hpp"
#include "../exception/ConversionException.hpp"

// STL stream import
#include <fstream>
#include <iostream>
#include <sstream>

// STL data container import
#include <list>
#include <map>

// STL regrex import
#include <regex>

/**
 * @brief method to processing entries to change data format
 *
 * @param entries The list of entries files
 * @return The property tree result of conversion
 */
boost::property_tree::ptree MvscCompileWarningIssueReportConvertor::processing(
    const std::list<boost::filesystem::path> &entries) {
  // init empty property tree to save resilt of covert
  boost::property_tree::ptree sonarQubeReport;
  std::ifstream inFile;
  // open the input file
  inFile.open(entries.front().string());

  std::stringstream strStream;
  // read the file
  strStream << inFile.rdbuf();
  // str holds the content of the file
  const std::string reportContent = strStream.str();

  const std::regex regex("(.+\\.[chi](?:pp|xx)?)\\((\\d+),(\\d+)\\):\\s([a-z]+)"
                         "\\s(C\\d+):\\s'.+': (.+)\\s\\[.+\\]",
                         std::regex_constants::ECMAScript);

  // all issues have engineId for this conversion
  const std::string engineId = m_engineId;

  // external issues are "CODE_SMELL" by default
  const std::string type = "CODE_SMELL";

  // issue property tree array
  boost::property_tree::ptree issues;

  // for each issue text line found in raw clang tidy report
  // convert to issue property tree
  for (auto i = std::sregex_iterator(reportContent.begin(), reportContent.end(),
                                     regex);
       i != std::sregex_iterator(); ++i) {
    const std::smatch match = *i;
    std::cout << "Match size = " << match.size() << std::endl;

    // save all raw splitted data
    const std::string sourceFile = match.str(1);
    const std::string line = match.str(2);
    const std::string column = match.str(3);
    const std::string severity = match.str(4);
    const std::string ruleId = match.str(5);
    const std::string message = match.str(6);

    // print issue raw data
    std::cout << "Whole match : " << match.str(0) << std::endl
              << "SourceFile is :" << sourceFile << std::endl
              << "Line :" << line << std::endl
              << "Column :" << column << std::endl
              << "Severity :" << severity << std::endl
              << "Message :" << message << std::endl
              << "ruleId :" << ruleId << std::endl;

    std::cout << "new rule added in map : " << ruleId << std::endl;

    // create and populate issue property tree
    boost::property_tree::ptree issue;

    // common properties
    issue.put<std::string>("engineId", engineId);
    issue.put<std::string>("ruleId", ruleId);

    // add converted level of issue
    issue.put<std::string>("severity",
                           IssueReportConvertor::SonarCloudSeverityValue.at(
                               ESonarCloudSeverity::MAJOR));
    issue.put<std::string>("type", type);

    // get location Peter of issue
    const boost::property_tree::ptree location =
        buildLocationTree(message, sourceFile, line, column);
    issue.add_child("primaryLocation", location);

    // add full generated issue in issue ptree array
    issues.push_back(
        std::pair<const std::string, boost::property_tree::ptree>("", issue));
  }

  // save all issues in result property tree
  sonarQubeReport.add_child("issues", issues);
  return sonarQubeReport;
}

/**
 * @brief method to build location tree of issue
 *
 * @param message The message of issue
 * @param filePath The file path of origine issue
 * @param line The line of issue
 * @param column The column of issue
 * @return boost::property_tree::ptree The location property tree
 */
boost::property_tree::ptree
MvscCompileWarningIssueReportConvertor::buildLocationTree(
    const std::string &message, const std::string &filePath,
    const std::string &line, const std::string &column) const {
  boost::property_tree::ptree location;

  location.put<std::string>("message", message);
  location.put<std::string>("filePath", filePath);

  // add text range to get location of error
  boost::property_tree::ptree textRange;
  textRange.put<std::string>("startLine", line == "0" ? "1" : line);
  uint64_t startColumn = stoi(column);
  if (startColumn > 0) {
    startColumn -= 1;
  }
  textRange.put<uint64_t>("startColumn", startColumn);
  location.add_child("textRange", textRange);

  return location;
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