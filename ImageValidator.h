#pragma once

#include <memory>

#include "Validator.h"
#include "XMLParser.h"

class ImageValidator : public Validator
{
public:
    explicit ImageValidator(std::shared_ptr<XMLParser> xmlParser) : xmlParser(xmlParser) {};

    const bool isValid(const std::string& imagePath) const;

private:
    const bool isImageExtensionValid(const std::string& imageFileExtension) const;
    const std::string getImageFileExtensionFromPath(const std::string& imagePath) const;
    const bool isImagePathValid(const std::string& imagePath) const;
    const bool isPNGSignatureValid(const std::string& imagePath, std::ifstream& file) const;
    const bool isJPEGSignatureValid(const std::string& imagePath, std::ifstream& file) const;

    std::shared_ptr<XMLParser> xmlParser;
};