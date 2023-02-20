#pragma once

#include <memory>

#include "Validator.h"
#include "XMLParser.h"

class OperationsValidator : public Validator
{
public: 
	explicit OperationsValidator(std::shared_ptr<XMLParser> xmlParser) : xmlParser(xmlParser) {};

	const bool isValid(const std::string& param) const;

private:
	std::shared_ptr<XMLParser> xmlParser;
};