#ifndef __REPORT_CONVERTOR_HPP__
#define __REPORT_CONVERTOR_HPP__

// STL imports
#include <functional>
#include <list>
#include <memory>

// boost imports
#include <boost/filesystem/path.hpp>
#include <boost/property_tree/ptree.hpp>

/**
 * @brief abstract class to convert report
 */
class ReportConvertor {
  /**
   * @brief method to processing entries to change data format
   *
   * @param entries The list of entries files
   * @return The property tree result of conversion
   */
  virtual boost::property_tree::ptree
  processing(const std::list<boost::filesystem::path> &entries) = 0;
  /**
   * @brief method to check if the result of conversion is valid
   *
   * @param report The report to check
   * @return true The result report is valid
   * @return false The result report is not valid
   */
  virtual bool
  verifyResultReport(const boost::property_tree::ptree &report) = 0;

public:
  /**
   * @brief Construct a new Report Convertor object
   *
   */
  ReportConvertor() = default;
  /**
   * @brief Destroy the Report Convertor object
   *
   */
  virtual ~ReportConvertor() = default;

  /**
   */
  ReportConvertor(const ReportConvertor &) = delete;
  /**
   */
  ReportConvertor(ReportConvertor &&) = delete;
  /**
   */
  ReportConvertor &operator=(const ReportConvertor &) = delete;
  /**
   */
  ReportConvertor &operator=(ReportConvertor &&) = delete;

  /**
   * @brief method to run conversion with check
   *
   * @param entries The list of entries files
   * @param output The path to write result of conversion
   */
  void convert(const std::list<boost::filesystem::path> &entries,
               const boost::filesystem::path &output);
};

#endif
