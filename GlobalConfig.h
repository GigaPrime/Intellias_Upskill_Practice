#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <experimental/filesystem>
#include <stdexcept>

namespace GlobalConstants
{
	const std::string XMLConfigFilename = "config.xml";
}

class Config {
public:
    void setConfig(const std::vector<std::string>& extensions, const std::vector<std::string>& operations);

private:
    void addFileExtensions(const std::vector<std::string>& extensions);
    void addOperations(const std::vector<std::string>& operations);
    void writeToFile();

    std::vector<std::string> fileExtensions;
    std::vector<std::string> fileOperations;
};

