#pragma once
#include <string>

class configParser 
{
public:
	const virtual bool parseConfigIfValid(const std::string& param) const = 0;
	const virtual bool validateIncomingParams(const std::string& param, const std::string& paramValue) const = 0;
};

class XMLParser : public configParser
{
public: 
	const bool parseConfigIfValid(const std::string& param) const;
	const bool validateIncomingParams(const std::string& param, const std::string& paramValue) const;

private:
	const bool isConfigFilePathValid() const;
	const bool isXMLFilestructureValid() const;
};