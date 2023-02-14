#pragma once
#include <string>

#include "GlobalConfig.h"

class configParser 
{
public:
	const virtual bool parseXMLConfigIfValid(const std::string& param) = 0;
	const virtual bool validateIncomingParams(const std::string& param, const std::string& paramValue) = 0;
};

class XMLParser : public configParser
{
public: 
	const bool parseXMLConfigIfValid(const std::string& param) const;
	const bool validateIncomingParams(const std::string& param, const std::string& paramValue) const;

private:
	const bool isConfigFilePathValid() const;
	const bool isXMLFilestructureValid() const;
};