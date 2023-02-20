#include "ImageProcessorThreadPoolHandler.h"

#include <memory>
#include <fstream>

#include "ImageProcessor.h"
#include "GlobalConfig.h"

ImageProcessorThreadPoolHandler::ImageProcessorThreadPoolHandler(mutable std::map<std::string, std::vector<std::string>>& imagesForProcessingWithOperations)
{
    namespace hardwareLimits = GlobalConstants::HARWARE_LIMITS;
    const size_t maxThreads = std::min(std::thread::hardware_concurrency(), static_cast<unsigned int>(hardwareLimits::MAX_CORES));
    const size_t maxMemoryGB = static_cast<unsigned int>(hardwareLimits::MAX_RAM_GB);
    const size_t maxDiskSpaceGB = static_cast<unsigned int>(hardwareLimits::MAX_DISK_GB);

    // @TODO here separate asynchronous manager should be present to detect if there are enough resources for creating thread(s)
    // @TODO long getImageFileSize(const std::string& imagePath) const should be used in this manager
    const double bytesPerImage = 0.1 * hardwareLimits::BYTES_PER_GB;  // Assume each image takes up to 100MB
    const size_t maxImages = std::min((maxMemoryGB * hardwareLimits::BYTES_PER_GB) / bytesPerImage, (maxDiskSpaceGB * hardwareLimits::BYTES_PER_GB) / bytesPerImage);

    std::cout << "Max threads: " << maxThreads << std::endl;
    std::cout << "Max images: " << maxImages << std::endl;

    fillImageQueue(imagesForProcessingWithOperations);

    const size_t numThreads = std::min(imageQueue.size(), maxThreads);
    for (size_t i = 0; i < numThreads; ++i) 
    {
        threads.emplace_back([this]() 
        {
            while (!stop) 
            {
                std::lock_guard<std::mutex> lock(queueMutex);
                if (!imageQueue.empty()) 
                {
                     processImage(imageQueue.front());
                     imageQueue.pop();
                }
                else 
                {
                     continue;
                }                
            }
        });
    }
}

ImageProcessorThreadPoolHandler::~ImageProcessorThreadPoolHandler() {
    stop = true;

    for (auto& thread : threads) 
    {
        thread.join();
    }
}

void ImageProcessorThreadPoolHandler::fillImageQueue(std::map<std::string, std::vector<std::string>>& imagesForProcessingWithOperations)
{
    for (const auto& image : imagesForProcessingWithOperations)
    {
        imageQueue.push(image);
    }
}

// @TODO this method should be moved to the FileValidator object
long ImageProcessorThreadPoolHandler::getImageFileSize(const std::string& imagePath) const
{
    std::ifstream file(imagePath, std::ios::binary | std::ios::ate);
    return file.tellg();
}

void ImageProcessorThreadPoolHandler::processImage(const std::pair<std::string, std::vector<std::string>> imageWithOperations)
{
    std::unique_ptr<Processor> imageProcessor = std::make_unique<ImageProcessor>(imageWithOperations.first, imageWithOperations.second);
    imageProcessor->process();
}