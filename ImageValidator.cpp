#include <fstream>
#include <experimental/filesystem>
#include <stdexcept>

#include "GlobalConfig.h"

#include "ImageValidator.h"

const bool ImageValidatorImpl::isImageFileValid(const std::string& imagePath) const
{
	const std::string imageFileExtension = getImageFileExtensionFromPath(imagePath);

	if (!isImageExtensionValid(imageFileExtension))
	{
		throw std::invalid_argument("Error: provided file extension is not allowed");
		return false;
	}

	if (!isImagePathValid(imagePath))
	{
		return false;
	}

	if (imageFileExtension == GlobalConstants::IMAGE_FORMATS::JPEG)
	{
		return isJPEGSignatureValid(imagePath, std::ifstream(imagePath));
	}

	if (imageFileExtension == GlobalConstants::IMAGE_FORMATS::PNG)
	{
		return isPNGSignatureValid(imagePath, std::ifstream(imagePath));
	}
}

const bool ImageValidatorImpl::isImageExtensionValid(const std::string& imageFileExtension) const
{
	return xmlParser->validateIncomingParams(GlobalConstants::XML_ELEMENTS::FILE_EXTENSIONS, imageFileExtension);
}

const std::string ImageValidatorImpl::getImageFileExtensionFromPath(const std::string& imagePath) const
{
	auto extensionPos = imagePath.rfind('.');

	if (extensionPos == std::string::npos) {
		throw std::invalid_argument("Error: no file extension found in the file path.");
	}

	return imagePath.substr(extensionPos + 1);
}

const bool ImageValidatorImpl::isImagePathValid(const std::string& imagePath) const
{
	if (!std::experimental::filesystem::exists(imagePath))
	{
		throw std::runtime_error("Error: file path is not valid.");
	}

	std::ifstream file(imagePath);

	if (!file.is_open()) {
		throw std::runtime_error("Error: Could not open config file for reading.");
	}
	return true;
}

const bool ImageValidatorImpl::isPNGSignatureValid(const std::string& imagePath, std::ifstream& file) const
{
	char pngSignature[8];
	file.read(pngSignature, 8);
	return !pngSignature[0] && !pngSignature[1] && pngSignature[2] == 0x89 && pngSignature[3] == 0x50
		&& pngSignature[4] == 0x4e && pngSignature[5] == 0x47 && pngSignature[6] == 0x0d && pngSignature[7] == 0x0a;
}

const bool ImageValidatorImpl::isJPEGSignatureValid(const std::string& imagePath, std::ifstream& file) const
{
	char jpegSignature[2];
	file.read(jpegSignature, 2);
	return jpegSignature[0] == 0xff && jpegSignature[1] == 0xd8;
}