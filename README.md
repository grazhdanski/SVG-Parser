# SVG Parser
Individual course project for the OOP course during the second semester in Sofia University, FMI

This is a simple SVG parser and editor console application that supports only a limited set of shapes: rectangles, circles and lines.

__Functionality:__
* Parse a valid SVG file
* List all supported shapes found in a parsed file including their attributes
* Create any of the supported shapes by specifying their attributes
* Translate a shape or all shapes by a given pair of values (X, Y)
* For each shape, check if it is located within a specified rectangular or circular area
* Save all changes to the file being edited
* Save the modified file as a new file

__Basic Usage:__
* SVGParser& parserInstance = SVGParser::getInstance(); --- Get a reference to the SVGParser object
* parserInstance.open("fileToOpen"); --- Open and parse fileToOpen.svg
* parserInstance.printAllShapes(); --- Print a list of all supported shapes found in the parsed file in the console
* parserInstance.createRectangle(10, 10, 250, 200, "pink"); --- Create a pink rectange by given (X, Y) coordinates, width, height and color
* parserInstance.createCircle(10, "red", "2", 20, 20); --- Create a circle with radius of 10, (X, Y) coordinates (20, 20), red stroke color and stroke width of 2
* parserInstance.Translate(25, 25, 1); --- Translate only the first shape in the list of shapes by (25, 25)
* parserInstance.Translate(20, 20); --- Translate all shapes
* parserInstance.save(); --- Save all changes made to the parsed file and close it
* parserInstance.saveAs("fileToOpenModified"); --- Save all changes made in a new file and close the parsed file
* parserInstance.close(); --- Close the parsed file
