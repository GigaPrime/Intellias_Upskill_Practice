#include <fstream>
#include <string>
#include <memory>
#include <experimental/filesystem>
#include <stdexcept>
#include <vector>

class ImageValidator {
public:
    virtual bool isImageValid(const std::string& imagePath) = 0;
};

class ImageValidatorImpl : public ImageValidator
{
public:
    const bool isImageValid(const std::string& imagePath) const;

private:
    const bool isFileExtensionValid(const std::string& imagePath) const;
    const std::vector<std::string> parseXMLConfigFile() const;
    const std::string parseXMLConfigFileLine(const std::string& line) const;
    const bool isPNGSignatureValid(const std::string& imagePath, std::ifstream& file) const;
    const bool isJPEGSignatureValid(const std::string& imagePath, std::ifstream& file) const;
};