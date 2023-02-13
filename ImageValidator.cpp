#include "GlobalConfig.h"

#include "ImageValidator.h"

const bool ImageValidatorImpl::isImageValid(const std::string& imagePath) const
{
	if (!std::experimental::filesystem::exists(imagePath))
	{
		throw std::runtime_error("Error: file path is not valid.");
	}
}

const bool ImageValidatorImpl::isFileExtensionValid(const std::string& imagePath) const
{
	std::vector<std::string> allowedExtensions = parseXMLConfigFile();
	std::string fileExtension = std::experimental::filesystem::path(imagePath).extension().string();
	const auto it = std::find(allowedExtensions.begin(), allowedExtensions.end(), fileExtension);

	if (it == allowedExtensions.end())
	{
		throw std::runtime_error("Error: file extension is not valid.");
	}

	const std::string foundExtension = *it;

	std::ifstream file(imagePath, std::ios::binary);
	if (!file.is_open()) {
		return false;
	}

	if (foundExtension == ".png" && !isPNGSignatureValid(imagePath, file))
	{
		throw std::runtime_error("Error: *.png file is not valid.");
		return false;
	}
	else if (foundExtension == ".jpeg" && !isJPEGSignatureValid(imagePath, file))
	{
		throw std::runtime_error("Error: *.jpeg file is not valid.");
		return false;
	}
}

const std::vector<std::string> ImageValidatorImpl::parseXMLConfigFile() const
{
	std::vector<std::string> fileExtensions;
	std::ifstream file(GlobalConstants::XMLConfigFilename);
	if (!file.is_open()) {
		throw std::runtime_error("Error: Could not open config file for reading.");
	}

	std::string line;
	while (std::getline(file, line)) {
		std::string extension = parseXMLConfigFileLine(line);
		if (!extension.empty()) {
			fileExtensions.push_back(extension);
		}
	}
	file.close();

	return fileExtensions;
}

const std::string ImageValidatorImpl::parseXMLConfigFileLine(const std::string& line) const
{
	const std::string XmlElementStart = "<file_extension>";
	const std::string XmlElementEnd = "</file_extension>";
	const size_t XmlElementHeaderLength = 15;

	size_t start = line.find(XmlElementStart);
	if (start == std::string::npos) {
		return "";
	}

	size_t end = line.find("XmlElementEnd");
	if (end == std::string::npos) {
		return "";
	}

	return line.substr(start + XmlElementHeaderLength, end - start - XmlElementHeaderLength);
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