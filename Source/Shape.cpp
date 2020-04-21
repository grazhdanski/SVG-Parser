#include "Shape.h"
// A function to modify a given attribute
bool Shape::setAttributeValue(const std::string _attribute, const std::string _value)
{
	std::map<std::string, std::string>::iterator i = this->attributes.find(_attribute);
	if (i != this->attributes.end()) 
	{
		// Attribute exists
		i->second = std::to_string( std::stoi(_value) + std::stoi(i->second));
		return true;
	}

	return false;
}

bool Shape::addAttribute(const std::string _attribute, const std::string _value)
{
	if (this->attributes.find(_attribute) == this->attributes.end())
	{
		// Attribute does not already exist
		attributes.insert(std::make_pair(_attribute, _value));
		return true;
	}
	
	return false;
}

std::string Shape::getAttributeValue(const std::string _attribute)
{
	std::map<std::string, std::string>::iterator i;
	i = attributes.find(_attribute);
	if (i != attributes.end())
	{
		return i->second;
	}
	else
	{
		return "0";
	}
}

//bool Shape::translate(const int _horizontal, const int _vertical)
//{
//	return true;
//}

void Shape::printAllAttributes() const
{
	for (auto i = attributes.cbegin(); i != attributes.cend(); i++)
	{
		std::cout <<i->first <<	":" << i->second << " "; 
	}
	std::cout << std::endl;
}
