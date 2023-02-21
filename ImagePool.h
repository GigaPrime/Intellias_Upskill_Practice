#pragma once

#include <map>
#include <string>
#include <tuple>
#include <vector>

class ImagePool {
public:
    void addValidImageToPool(const std::string& imagePath, const std::vector<std::string>& operations);
    std::pair<std::string, std::vector<std::string>> getImageFromPool(const std::string& key);

private:
    // The idea of container is to use const std::sting& imagePath as a key and 
    // std::vector<std::string>& operations as a flag if image was processed or not.
    // If the vector of operations is empty (appropriate stringshould be deleted 
    // after each operation is performed) it means the image was already processed 
    // and could be returned

    // Ready and NotReady maps are used to store incoming and already validated images
    std::map<std::string, std::vector<std::string>> readyImages;
    std::map<std::string, std::vector<std::string>> notReadyImages;
};