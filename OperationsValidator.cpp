#include "OperationsValidator.h"

#include "GlobalConfig.h"

const bool OperationsValidator::isValid(const std::vector<std::string>& operations) const
{
	for (const auto& operation : operations)
	{
		if (!xmlParser->validateIncomingParams(GlobalConstants::XML_CONFIG::XML_ELEMENTS::OPERATIONS, operation))
		{
			throw std::invalid_argument("Error: invalid operations provided");
			return false;
		}
	}
	
	return true;
}
