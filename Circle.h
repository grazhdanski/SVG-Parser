#pragma once
#include "Shape.h"

class Circle : public Shape
{
public:
	Circle() : Shape("circle") {}
	void printAllAttributes() const;
	bool translate(const int _horizontal, const int _vertical) override;
	bool isWithinRectangle(const int _x, const int _y,
		const unsigned _width, const unsigned _height) override;
	bool isWithinCircle(const int _cx, const int _cy, const unsigned _r) override;
};