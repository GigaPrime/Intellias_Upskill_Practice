#pragma once

#include <string>
#include <thread>
#include <vector>

class ImagePreparationThreadPoolHandler
{
public:
	void prepareImage(const std::string& imagePath, const std::vector<std::string>& operations);

private:
	std::vector<std::thread> threads;
};