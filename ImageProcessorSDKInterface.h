#pragma once

#include <vector>
#include <string>

class ImageProcessorSDKInterface
{
public:
	void getData(const std::string& imagePath, const std::vector<std::string>& operations);
	std::string returnResult(); 
};
