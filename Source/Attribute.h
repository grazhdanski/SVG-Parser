#pragma once
#include <string>

class Attribute
{
	std::string name;
	std::string value;
public:
	Attribute(const std::string _name, const std::string _value) 
		: name(_name), value(_value) {}
};
