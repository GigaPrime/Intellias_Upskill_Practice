#pragma once

#include <memory>
#include <vector>

#include "Validator.h"
#include "XMLParser.h"

class OperationsValidator : public Validator
{
public: 
	explicit OperationsValidator(std::shared_ptr<XMLParser> xmlParser) : xmlParser(xmlParser) {};

	const bool isValid(const std::vector<std::string>& operations) const;

private:
	std::shared_ptr<XMLParser> xmlParser;
};