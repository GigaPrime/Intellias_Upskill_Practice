# Intellias_Upskill_Practice
#Please take a look at the 'overall_schema.jpg' first!

TODO
1. All file operations (like getting byteSize of the file, path validation and so on) should be moved to the separate object (FileValidator). So ImageValiadator should be splited to 
FileValidator and ImageValidator itself
2. Add one more parallelized thread pool for image preparation (before the image processing thread pool). 
This pool would fill in mutable std::map<std::string, std::vector<std::string>>& imagesForProcessingWithOperations performing
all the validations (file and image)