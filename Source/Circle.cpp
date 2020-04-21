#include "Circle.h"

void Circle::printAllAttributes() const
{
	std::cout << "Circle ";
	Shape::printAllAttributes();
}

bool Circle::translate(const int _horizontal, const int _vertical)
{
	std::string xAsString = std::to_string(_horizontal);
	std::string yAsString = std::to_string(_vertical);

	if (!(this->setAttributeValue("cx", xAsString)))
	{
		// The attribute does not exist, i.e it is defaulted to 0
		// Add it
		this->addAttribute("cx", xAsString);
	}

	if (!(this->setAttributeValue("cy", yAsString)))
	{
		this->addAttribute("cy", yAsString);
	}

	return true;
}

bool Circle::isWithinRectangle(const int _x, const int _y, const unsigned _width, const unsigned _height)
{
	int cx = std::stoi(this->getAttributeValue("cx"));
	int cy = std::stoi(this->getAttributeValue("cy"));
	int r = std::stoi(this->getAttributeValue("r"));

	if (cx >= _x + r && cx + r <= _x + _width)
	{
		if (cy >= _y + r && cy + r <= _y + _height)
		{
			return true;
		}
	}

	return false;
}

bool Circle::isWithinCircle(const int _cx, const int _cy, const unsigned _r)
{
	int cx = std::stoi(this->getAttributeValue("cx"));
	int cy = std::stoi(this->getAttributeValue("cy"));
	unsigned r = std::stoi(this->getAttributeValue("r"));
	
	double distanceBetweenRadiuses = std::sqrt((cx - _cx)*(cx - _cx) + (cy - _cy)*(cy - _cy));

	return _r >= distanceBetweenRadiuses + r;
}
