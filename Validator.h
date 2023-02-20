#pragma once

#include <string>

class Validator
{
	virtual bool isValid(const std::string& param) = 0;
};