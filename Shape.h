#pragma once
#include <map>
#include <iostream>
#include <string>

class Shape
{
	std::string name;
	std::map<std::string, std::string> attributes;
protected:
	Shape(const std::string _name) : name(_name) {}
	bool setAttributeValue(const std::string _attribute, const std::string _value);

public:
	bool addAttribute(const std::string _attribute, const std::string _value);
	std::string getAttributeValue(const std::string _attribute);
	virtual bool translate(const int _horizontal, const int _vertical) = 0;
	void printAllAttributes()  const;
	std::string getName() const { return this->name; }

	virtual bool isWithinRectangle(const int _x, const int _y,
		const unsigned _width, const unsigned _height) = 0;
	
	virtual bool isWithinCircle(const int _cx, const int _cy, const unsigned _r) = 0;

	friend class SVGParser;
};