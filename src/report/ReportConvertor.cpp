#include "./ReportConvertor.hpp"
#include "../exception/ConversionException.hpp"
#include "../exception/ValidationException.hpp"

// boost json import
#include <boost/filesystem.hpp>
#include <boost/property_tree/json_parser.hpp>

// std imports
#include <exception>
#include <iostream>

/**
 * @brief method to run conversion with check
 *
 * @param entries The list of entries files
 * @param output The path to write result of conversion
 */
void ReportConvertor::convert(const std::list<boost::filesystem::path> &entries,
                              const boost::filesystem::path &output) {
  // fore each files in entry list test if file exist on disk
  for (const boost::filesystem::path &entry : entries) {
    if (!boost::filesystem::exists(entry)) {
      const std::string fileError =
          "The file \"" + entry.string() + "\" not exist";
      std::cerr << "[ERROR] " << fileError << std::endl;
      // if file not exist throw exception
      throw ConversionException(fileError);
    }
  }
  // run specialized conversion processing
  const boost::property_tree::ptree result = processing(entries);

  // test if report generated has valid format
  if (const bool isValid = verifyResultReport(result); !isValid) {
    const std::string validationError = "The conversion report failed";
    std::cerr << "[ERROR] " << validationError << std::endl;
    // if file generated invalide throw exception
    throw ValidationException(validationError);
  }

  // if at least one issue found write property tree json report
  if (!result.get_child("issues").empty()) {
    boost::property_tree::write_json(output.string(), result);
  } else {
    // if issues property tree array is empty write empty report
    // to have a valid report
    std::ofstream emptyJsonFile;
    emptyJsonFile.open(output.string());
    emptyJsonFile << "{\"issues\": []}";
    emptyJsonFile.close();
  }
}