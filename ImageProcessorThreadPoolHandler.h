#include <string>
#include <vector>
#include <map>
#include <future>
#include <thread>
#include <mutex>
#include <queue>
#include <iostream>

class ImageProcessorThreadPoolHandler 
{
public:
    ImageProcessorThreadPoolHandler(mutable std::map<std::string, std::vector<std::string>>& imagesForProcessingWithOperations);
    ~ImageProcessorThreadPoolHandler();

private:
    void fillImageQueue(std::map<std::string, std::vector<std::string>>& imagesForProcessingWithOperations);
    long getImageFileSize(const std::string& imagePath) const;
    void processImage(const std::pair<std::string, std::vector<std::string>> imageWithOperations); // pass-by-value is not occasional

    std::mutex queueMutex;
    std::queue<std::pair<std::string, std::vector<std::string>>> imageQueue;
    std::vector<std::thread> threads;
    std::atomic<bool> stop{ false };
};
