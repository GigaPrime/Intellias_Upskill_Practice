#include <string>
#include <memory>

#include "XMLParser.h"

class ImageValidator {
public:
    virtual bool isImageValid(const std::string& imagePath) = 0;
};

class ImageValidatorImpl : public ImageValidator
{
public:
    explicit ImageValidatorImpl(std::shared_ptr<XMLParser> xmlParser) : xmlParser(xmlParser) {};
    const bool isImageFileValid(const std::string& imagePath) const;

private:
    const bool isImageExtensionValid(const std::string& imagePath) const;
    const std::string getImageFileExtensionFromPath(const std::string& imagePath) const;
    const bool isImagePathValid(const std::string& imagePath) const;
    const bool isPNGSignatureValid(const std::string& imagePath, std::ifstream& file) const;
    const bool isJPEGSignatureValid(const std::string& imagePath, std::ifstream& file) const;

    std::shared_ptr<XMLParser> xmlParser; 
};