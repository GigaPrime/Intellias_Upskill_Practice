#include "ObjectForProcessing.h"

#include "ImageValidator.h"

std::string ObjectForProcessingImpl::getImage(const std::string& imagePath) const
{
	std::unique_ptr<ImageValidator> imageValidator = std::make_unique<ImageValidatorImpl>();
	if (imageValidator->isImageValid(imagePath))
	{
		return imagePath;
	}
	throw std::runtime_error("Error: provided image file pr path is invalid.");
}

const std::unique_ptr<ObjectForProcessing> ObjectForProcessingImpl::createObjetcForProcessing()
{

}

