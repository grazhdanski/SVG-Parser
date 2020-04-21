#pragma once
#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include "Rectangle.h"
#include "Circle.h"
#include "Line.h"

class SVGParser
{
private:
	SVGParser() {};
	static SVGParser* instance;
	std::vector<std::string> fileContent;
	std::vector<Shape*> shapes; // A vector with all known shapes found in the current file
	std::string currentFile = "";
	std::string lastFile = "";
	std::string svgLine = "";
	
public:
	SVGParser(const SVGParser& _right) = delete;
	SVGParser& operator=(const SVGParser& _right) = delete;
	static SVGParser& getInstance();
	bool open(const std::string _fileName);
	bool printAllShapes() const;
	bool close();
	bool save();
	bool saveAs(const std::string _newFileName);
	bool Translate(const int _horizontal, const int _vertical, const int _shapeNumber = -1);

	bool createRectangle(const int _x, const int _y, const unsigned _width, 
	const unsigned _height, const std::string _color);
	bool createCircle(const unsigned _r, const std::string _strokeColor, const std::string _strokeWidth = "1", const int _cx = 0, const int _cy = 0);
	bool createLine(const int _x1, const int _y1, const int _x2, const int _y2,
		const std::string _strokeColor, const std::string _strokeWidth = "1");

	void withinRectangle(const int _x, const int _y, const unsigned _width, const unsigned _height) const;
	void withinCircle(const int _cx, const int _cy, const unsigned _r) const;

	~SVGParser();
};
