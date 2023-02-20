#include "OperationsValidator.h"

#include "GlobalConfig.h"

const bool OperationsValidator::isValid(const std::string& param) const
{
	if (!xmlParser->validateIncomingParams(GlobalConstants::XML_ELEMENTS::OPERATIONS, param))
	{
		throw std::invalid_argument("Error: invalid operations provided");
		return false;
	}
	return true;
}
