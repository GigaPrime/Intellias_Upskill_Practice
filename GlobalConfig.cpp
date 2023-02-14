#include "GlobalConfig.h"

void Config::setConfig(const std::vector<std::string>& extensions, const std::vector<std::string>& operations)
{
    addFileExtensions(extensions);
    addOperations(operations);
    writeToFile();
}

void Config::addFileExtensions(const std::vector<std::string>& operations)
{
    fileOperations.insert(std::end(fileOperations), std::begin(operations), std::end(operations));
}

void Config::addOperations(const std::vector<std::string>& operations)
{
    fileExtensions.insert(std::end(fileExtensions), std::begin(operations), std::end(operations));
}

void Config::writeToFile() 
{
    std::ofstream file(GlobalConstants::XML_ELEMENTS::CONFIG_FILENAME);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file for writing.");
    }

    file << "<config>\n";
    for (const auto& extension : fileExtensions) {
        file << "  <file_extension>" << extension << "</file_extension>\n";
    }
    for (const auto& operation : fileOperations) {
        file << "  <file_extension>" << operation << "</file_extension>\n";
    }
    file << "</config>\n";
    file.close();
}