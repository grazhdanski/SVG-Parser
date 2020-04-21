#include "Line.h"

void Line::printAllAttributes() const
{
	std::cout << "Line ";
	Shape::printAllAttributes();
}

bool Line::translate(const int _horizontal, const int _vertical)
{
	const unsigned ARR_SIZE = 4;
	std::string coordinates[ARR_SIZE] = { "x1", "x2", "y1", "y2" };

	std::string xAsString = std::to_string(_horizontal);
	std::string yAsString = std::to_string(_vertical);

	// CONSIDER REFACTORING
	for (unsigned i = 0; i < ARR_SIZE; i++)
	{
		if (i < ARR_SIZE / 2)
		{
			if (!(this->setAttributeValue(coordinates[i], xAsString)))
			{
				// Attribute has a default value 0, i.e it is not in the attributes
				// Add it
				this->addAttribute(coordinates[i], xAsString);
			}
		}
		else
		{
			if (!(this->setAttributeValue(coordinates[i], yAsString)))
			{
				// Attribute has a default value 0, i.e it is not in the attributes
				// Add it
				this->addAttribute(coordinates[i], yAsString);
			}
		}
	}

	return true;
}

bool Line::isWithinRectangle(const int _x, const int _y, const unsigned _width, const unsigned _height)
{
	int x1 = std::stoi(this->getAttributeValue("x1"));
	int x2 = std::stoi(this->getAttributeValue("x2"));
	int y1 = std::stoi(this->getAttributeValue("y1"));
	int y2 = std::stoi(this->getAttributeValue("y2"));

	if (x1 + _x <= _width && x2 + _x <= _width && y1 + _y <= _height && y2 + _y <= _height)
	{
		return true;
	}

	return false;
}

bool Line::isWithinCircle(const int _cx, const int _cy, const unsigned _r)
{
	int x1 = std::stoi(this->getAttributeValue("x1"));
	int x2 = std::stoi(this->getAttributeValue("x2"));
	int y1 = std::stoi(this->getAttributeValue("y1"));
	int y2 = std::stoi(this->getAttributeValue("y2"));

	return (_r*_r >= (x1-_cx)*(x1-_cx) + (y1 - _cy) * (y1 - _cy)) && 
		(_r*_r >= (x2 - _cx)*(x2 - _cx) + (y2 - _cy) * (y2 - _cy));
}
