#include "ImagePreparationThreadPoolHandler.h"

#include <memory>

#include "ImagePool.h"
#include "ImageValidator.h"
#include "OperationsValidator.h"
#include "XMLParser.h"

void ImagePreparationThreadPoolHandler::prepareImage(const std::string& imagePath, const std::vector<std::string>& operations)
{
	std::shared_ptr<ImagePool> imagePool = std::make_shared<ImagePool>();
	std::shared_ptr<configParser> XMLParser = std::make_shared<XMLParser>();

	threads.emplace_back(std::make_pair<std::make_unique<ImageValidator>(XMLParser)->isValid(imagePath), std::make_unique<OperationsValidator>(XMLParser)->isValid(operations)));
	
}
