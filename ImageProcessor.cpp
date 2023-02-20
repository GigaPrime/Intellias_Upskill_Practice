#include "ImageProcessor.h"

#include "GlobalConfig.h"

ImageProcessor::~ImageProcessor()
{
}

void ImageProcessor::process() const
{
    namespace operationName = GlobalConstants::XML_CONFIG::OPERATIONS;
    namespace resizeVal = GlobalConstants::OPERATION_VALUES::RESIZE_VALUES;
    namespace cropVal = GlobalConstants::OPERATION_VALUES::CROP_VALUES;
    namespace blurVal = GlobalConstants::OPERATION_VALUES::BLUR_VALUES;
    namespace watercolorVal = GlobalConstants::OPERATION_VALUES::WATERCOLOR_VALUES;
    namespace catroonizeVal = GlobalConstants::OPERATION_VALUES::CARTOONIZE_VALUES;

    // this should be refactored to the state-machine instance with separate objects like "PerfomResize", "PerformCrop"
    // and so on to handle operations
    for (const auto& operation : operations) 
    {
        if (operation == operationName::RESIZE)
        {
            resize(resizeVal::WIDTH, resizeVal::HEIGHT);
        }
        else if (operation == operationName::CROP) 
        {
            crop(cropVal::X, cropVal::Y, cropVal::WIDTH, cropVal::HEIGHT);
        }
        else if (operation == operationName::BLUR) 
        {
            blur(blurVal::RADIUS);
        }
        else if (operation == operationName::WATERCOLOR) 
        {
            watercolor(watercolorVal::RADIUS, watercolorVal::X_SHIFT, watercolorVal::Y_SHIFT);
        }
        else if (operation == operationName::CARTOONIZE) 
        {
            cartoonize(catroonizeVal::RADIUS);
        }
    }
}