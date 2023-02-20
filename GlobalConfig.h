#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <experimental/filesystem>
#include <stdexcept>

namespace GlobalConstants
{
    namespace XML_CONFIG
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
            const std::string CARTOONIZE = "cartoonize";
        }
    }

    namespace OPERATION_VALUES 
    {
        namespace RESIZE_VALUES
        {
            const uint16_t WIDTH = 1200;
            const uint16_t HEIGHT = 600;
        }
        namespace CROP_VALUES
        {
            const uint16_t X = 10;
            const uint16_t Y = 300;
            const uint16_t WIDTH = 800;
            const uint16_t HEIGHT = 800;
        }
        namespace BLUR_VALUES
        {
            const size_t RADIUS = 123;
        }
        namespace WATERCOLOR_VALUES
        {
            const double RADIUS = 0.5;
            const double X_SHIFT = 0.7;
            const double Y_SHIFT = 0.3;
        }
        namespace CARTOONIZE_VALUES
        {
            const double RADIUS = 0.44;
        }
    }

    namespace HARWARE_LIMITS
    {
        const uint8_t MAX_CORES = 64;
        const uint8_t MAX_RAM_GB = 64;
        const uint16_t MAX_DISK_GB = 1500;
        const long long BYTES_PER_GB = 1024 * 1024 * 1024;
    }

    namespace
    {
        static bool isConfigValid = false;
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

