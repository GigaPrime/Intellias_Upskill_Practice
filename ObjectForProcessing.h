#pragma once

#include <iostream>



class ObjectForProcessing
{
public:
	virtual const std::unique_ptr<ObjectForProcessing> createObjetcForProcessing() = 0;
};

class ObjectForProcessingImpl : public ObjectForProcessing
{
public:
	const std::unique_ptr<ObjectForProcessing> createObjetcForProcessing();

private:
	std::string getImage(const std::string& imagePath) const;
	std::vector<std::string>GetOperations(std::vector<std::string> operations);
};