#include "SVGParser.h"

int main()
{
	//// Basic Usage

	SVGParser& parserInstance = SVGParser::getInstance();


	parserInstance.open("simple");
	parserInstance.printAllShapes();

	parserInstance.createCircle(10, "red", "2", 20, 20);
	parserInstance.createLine(10, 10, 20, 20, "blue", "2");

	parserInstance.printAllShapes();

	//// For each shape, check if it is within a circle with given (X, Y) coordinates and radius
	//parserInstance.withinCircle(20, 30, 250);

	//parserInstance.printAllShapes();

	//// Translate only the first shape in the list of shapes by (25, 25)
	//parserInstance.Translate(25, 25, 1);

	//// Translate all shapes
	//parserInstance.Translate(20, 20);
	//parserInstance.printAllShapes(); 

	//// Create a pink rectange by given (X, Y) coordinates, width, height and color
	//parserInstance.createRectangle(10, 10, 250, 200, "pink");
	//parserInstance.printAllShapes();

	//parserInstance.saveAs("simpleModified");

	//parserInstance.save();

	//return 0;
}