#include "Rectangle.h"

void Rectangle::printAllAttributes() const
{
	std::cout << "Rectangle ";
	Shape::printAllAttributes();
}

bool Rectangle::translate(const int _horizontal, const int _vertical)
{
	std::string xAsString = std::to_string(_horizontal);
	std::string yAsString = std::to_string(_vertical);

	if (!(this->setAttributeValue("x", xAsString)))
	{
		// The attribute does not exist, i.e it is defaulted to 0
		// Add it
		this->addAttribute("x", xAsString);
	}

	if (!(this->setAttributeValue("y", yAsString)))
	{
		this->addAttribute("y", yAsString);
	}

	return true;
}

bool Rectangle::isWithinRectangle(const int _x, const int _y, const unsigned _width, const unsigned _height)
{
	int x = std::stoi(this->getAttributeValue("x"));
	int y = std::stoi(this->getAttributeValue("y"));
	int width = std::stoi(this->getAttributeValue("width"));
	int height = std::stoi(this->getAttributeValue("height"));

	if (x >= _x && y >= _y)
	{
		if (x + width <= _width && y + height <= _height)
		{
			return true;
		}
	}

	return false;
}

bool Rectangle::isWithinCircle(const int _cx, const int _cy, const unsigned _r)
{
	int x = std::stoi(this->getAttributeValue("x"));
	int y = std::stoi(this->getAttributeValue("y"));
	unsigned width = std::stoi(this->getAttributeValue("width"));
	unsigned height = std::stoi(this->getAttributeValue("height"));

	double dx = std::fmax(_cx - x, x + width - _cx);
	double dy = std::fmax(_cy - y, y + height - _cy);

	return (double)_r * _r >= dx * dx + dy * dy;
}
