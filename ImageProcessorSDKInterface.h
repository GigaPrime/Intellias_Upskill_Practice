#pragma once

#include <vector>
#include <string>
#include <map>

#include "ObjectForProcessing.h"


class ImageProcessorSDKInterface
{
public:
	virtual void getData(const std::string& imagePath, const std::vector<std::string>& operations) = 0;
	virtual std::string returnResult() = 0; 
};

class ImageProcessingSDKInterfaceImpl : public ImageProcessorSDKInterface
{
public:
	void getData(const std::string& imagePath, const std::vector<std::string>& operations);


private:
	std::map<std::string, std::vector<std::string>> imagesForProcessingWithOperations;
};