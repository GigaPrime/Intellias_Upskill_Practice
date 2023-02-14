#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <experimental/filesystem>
#include <stdexcept>

namespace GlobalConstants
{
    namespace XML_ELEMENTS
    {
        const std::string CONFIG_FILENAME = "config.xml";
        const std::string FILE_EXTENSIONS = "file_extension";
        const std::string OPERATIONS = "operations";
    }
    namespace IMAGE_FORMATS 
    {
        const std::string JPEG = "jpeg";
        const std::string PNG = "png";
    }
    namespace OPERATIONS
    {
        const std::string RESIZE = "resize";
        const std::string CROP = "crop";
        const std::string BLUR = "blur";
        const std::string WATERCOLOR = "watercolor";
        const std::string CARTOONIZE = "cartoonaize";
    }
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

