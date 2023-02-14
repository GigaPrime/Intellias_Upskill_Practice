#include <fstream>
#include <regex>

#include "XMLParser.h"

namespace XMLElements = GlobalConstants::XML_ELEMENTS;
namespace imageFormats = GlobalConstants::IMAGE_FORMATS;
namespace operations = GlobalConstants::OPERATIONS;

const bool XMLParser::parseXMLConfigIfValid(const std::string& param) const
{
	if (!isConfigFilePathValid)
	{
		throw std::runtime_error("Error: config file path error or file does not exist.");
	}

	if (!isXMLFilestructureValid())
	{
		throw std::runtime_error("Error: config file structure corrupted.");
	}

	return true;
}

const bool XMLParser::validateIncomingParams(const std::string& param, const std::string& paramValue) const
{
	std::ifstream file(GlobalConstants::XML_ELEMENTS::CONFIG_FILENAME);

	std::string fileContents((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());

	// Check if the <param> element with the specified attribute and value
	const std::string paramRegex = "<param\\s+" + param + "=\"" + paramValue + "\">\\s*</param>";
	std::regex paramPattern(paramRegex);

	return std::regex_search(fileContents, paramPattern);
}

const bool XMLParser::isConfigFilePathValid() const
{
	std::ifstream file(XMLElements::CONFIG_FILENAME);
	if (!file.is_open()) {
		throw std::runtime_error("Error: Could not open config file for reading.");
	}
	return true;
}


const bool XMLParser::isXMLFilestructureValid() const
{
	std::ifstream file(GlobalConstants::XML_ELEMENTS::CONFIG_FILENAME);

	std::string fileContents((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());

	// Check for valid XML declaration
	std::regex xmlDeclarationPattern("<\\?xml [^\\?]+\\?>\n?");
	if (!std::regex_match(fileContents, xmlDeclarationPattern)) 
	{
		throw std::invalid_argument("Error: invalid XML file declaration");
		return false;
	}

	// Check for valid <file_extension> tag and <jpeg> or <png> element
	std::regex fileExtensionPattern("<" + XMLElements::FILE_EXTENSIONS + ">(\n?.*(" + imageFormats::JPEG + "|" + imageFormats::PNG + ").*)*</" + XMLElements::FILE_EXTENSIONS + ">\n?");
	if (!std::regex_search(fileContents, fileExtensionPattern)) 
	{
		throw std::invalid_argument("Error: no file_extensions element found or no valid image formats found");
		return false;
	}

	// Check for valid <operations> tag with <resize>, <crop>, <blur>, <watercolor>, or <cartoonize> element
	std::regex operationsPattern("<" + XMLElements::OPERATIONS + ">(\n?.*(" + operations::RESIZE + "|" + operations::CROP + "|" + operations::BLUR + "|" + operations::WATERCOLOR + "|" + operations::CARTOONIZE + ").*)*</" + XMLElements::OPERATIONS + ">\n?");
	if (!std::regex_search(fileContents, operationsPattern)) 
	{
		throw std::invalid_argument("Provided XML file parsed. Error: no operations element found or no valid operation names found");
		return false;
	}

	return true;
}
