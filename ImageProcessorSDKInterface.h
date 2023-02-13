#pragma once

#include <vector>
#include <string>

#include "ObjectForProcessing.h"


class ImageProcessorSDKInterface
{
public:
	virtual void getData(const std::string& imagePath, const std::vector<std::string>& operations) = 0;
	std::string returnResult();
};

class ImageProcessingSDKInterfaceImpl : public ImageProcessorSDKInterface
{
public:
	void getData(const std::string& imagePath, const std::vector<std::string>& operations);
};