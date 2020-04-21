#include "SVGParser.h"

SVGParser* SVGParser::instance = 0;

SVGParser & SVGParser::getInstance()
{
	if (instance == nullptr)
	{
		instance = new SVGParser();
	}

	return *instance;
}

Shape* createAppropriateShape(const std::string& _shapeName)
{
	if (_shapeName == "rect")
	{
		return new Rectangle();
	}
	else if (_shapeName == "circle")
	{
		return new Circle();
	}
	else if (_shapeName == "line")
	{
		return new Line();
	}

	// Not all paths return a value. However, this function is for internal use only and it is always
	// used with correct arguments since only supported shapes are parsed
}

bool SVGParser::open(const std::string _fileName)
{
	std::ifstream fileToRead(_fileName + ".svg");

	if (fileToRead.is_open())
	{
		this->currentFile = _fileName;
		std::cout << "Successfully opened " << _fileName << std::endl;
		//std::vector<Shape*> shapes; // A vector with all known shapes found in the input
		std::smatch shapeName; // The current shape name

		const std::regex attributePattern("(\\w+|\\w+-\\w+)=\"(\\w+)\""); // A regex for the svg shape attributes
		const std::regex shapeNamePattern("^\\s*<(rect|circle|line)"); // A regex for the shape name

		std::string inputLine; // A string to store the current line of the document

		std::vector<int> captureGroups = { 1, 2 }; // The capture groups to iterate over

		while (std::getline(fileToRead, inputLine))
		{
			if (inputLine != "")
			{
				// Find the line containing a SVG tag
				if (inputLine.find("<svg") != std::string::npos && this->svgLine.empty())
				{
					this->svgLine = inputLine;
				}

				// Check if there is a tag that marks a shape
				bool match = std::regex_search(inputLine, shapeName, shapeNamePattern);

				if (match)
				{
					const std::sregex_token_iterator end; // Default constructed end-of-sequence iterator
					Shape* currentShape = createAppropriateShape(shapeName[1]);

					std::sregex_token_iterator
						i(inputLine.begin(), inputLine.end(), attributePattern, captureGroups);

					while (i != end)
					{
						std::string attributeName = *i; i++;
						std::string attributeValue = *i; i++;
						currentShape->addAttribute(attributeName, attributeValue);
					}

					this->shapes.push_back(currentShape);
				}
			}
			inputLine += "\n";
			this->fileContent.push_back(inputLine);
		}
		fileToRead.close();
		lastFile = currentFile;
		currentFile = "";

		return 1; // Success
	}
	else
	{
		std::cout << "Error parsing" << std::endl;
		std::quick_exit(EXIT_FAILURE);
		return 0;
	}
}

bool SVGParser::printAllShapes() const
{
	for (auto i = this->shapes.begin(); i < this->shapes.end(); i++)
	{
		std::cout << (*i)->getName() << " ";
		(*i)->printAllAttributes();
	}

	return true;
}

bool SVGParser::close()
{
	if (!this->lastFile.empty())
	{
		this->fileContent.clear();
		this->shapes.clear();
		this->currentFile.erase();
		this->lastFile.erase();
		this->svgLine.erase();

		std::cout << "Successfully closed " << this->lastFile << std::endl;
		return true;
	}

	std::cout << "Error closing the file!" << std::endl;
	return false;
}

bool SVGParser::saveAs(const std::string _newFileName)
{
	std::ofstream fileToWriteTo(_newFileName + ".svg");

	if (fileToWriteTo.is_open())
	{
		std::vector<std::string>::const_iterator i = this->fileContent.begin();

		fileToWriteTo << this->svgLine << '\n';

		// Iterate over the shapes
		for (auto j = this->shapes.begin(); j < this->shapes.end(); j++)
		{
			fileToWriteTo << "<" << (*j)->getName() << " ";
			for (auto k = (*j)->attributes.begin(); k != (*j)->attributes.end(); k++)
			{
				fileToWriteTo << k->first << "=" << "\"" << k->second << "\"" << " ";
			}

			fileToWriteTo << "/> \n";
		}

		fileToWriteTo << "</svg>";

		fileToWriteTo.close();
		std::cout << "Successfully saved as " << _newFileName << std::endl;
		return true;
	}
	else
	{
		std::cout << "Error opening the file to save as to!" << std::endl;
		return false;
	}
}

bool SVGParser::Translate(const int _horizontal, const int _vertical, const int _shapeNumber)
{
	if (this->lastFile.empty()) // There is no parsed file
	{
		std::cout << "Nothing to translate!" << std::endl;
		return false;
	}

	if (_shapeNumber == -1) // No specific figure was chosen, translate all figures
	{
		std::vector<Shape*>::iterator i;
		for (i = this->shapes.begin(); i < this->shapes.end(); i++)
		{
			(*i)->translate(_horizontal, _vertical);
		}
		std::cout << "Translated all figures" << std::endl;
	}
	else
	{
		// There is a specific figure chosen, validate the _shapeNumber
		if (_shapeNumber > 0 && _shapeNumber < this->shapes.size() + 1)
		{
			this->shapes.at(_shapeNumber - 1)->translate(_horizontal, _vertical);
			std::cout << "Translated " << _shapeNumber << std::endl;
		}
		else
		{
			std::cout << "There is no figure number " << _shapeNumber << std::endl;
			return false;
		}
	}

	return true;
}

bool SVGParser::createRectangle(const int _x, const int _y, const unsigned _width,
	const unsigned _height, const std::string _color)
{
	Rectangle* temp = new Rectangle();
	temp->addAttribute("x", std::to_string(_x));
	temp->addAttribute("y", std::to_string(_y));
	temp->addAttribute("width", std::to_string(_width));
	temp->addAttribute("height", std::to_string(_height));
	temp->addAttribute("fill", _color);

	this->shapes.push_back(temp);
	std::cout << "Successfully created a rectangle" << std::endl;

	return true;
}

bool SVGParser::createCircle(const unsigned _r, const std::string _strokeColor, const std::string _strokeWidth, const int _cx, const int _cy)
{
	Circle* temp = new Circle();
	temp->addAttribute("r", std::to_string(_r));
	temp->addAttribute("stroke-color", _strokeColor);
	temp->addAttribute("stroke-width", _strokeWidth);
	temp->addAttribute("cx", std::to_string(_cx));
	temp->addAttribute("cy", std::to_string(_cy));

	this->shapes.push_back(temp);
	std::cout << "Successfully created a circle" << std::endl;

	return true;
}

bool SVGParser::createLine(const int _x1, const int _y1, const int _x2, const int _y2,
	const std::string _strokeColor, const std::string _strokeWidth)
{
	Line* temp = new Line();
	temp->addAttribute("x1", std::to_string(_x1));
	temp->addAttribute("y1", std::to_string(_y1));
	temp->addAttribute("x2", std::to_string(_x2));
	temp->addAttribute("y2", std::to_string(_y2));
	temp->addAttribute("stroke-width", _strokeWidth);
	temp->addAttribute("stroke-color", _strokeColor);

	this->shapes.push_back(temp);
	std::cout << "Successfully created a line" << std::endl;
	return true;
}

void SVGParser::withinRectangle(const int _x, const int _y, const unsigned _width, const unsigned _height) const
{
	
	for (auto i = this->shapes.begin() ; i < this->shapes.end(); i++)
	{
		std::cout << (*i)->isWithinRectangle(_x, _y, _width, _height) << std::endl;
	}
}

void SVGParser::withinCircle(const int _cx, const int _cy, const unsigned _r) const
{
	for (auto i = this->shapes.begin(); i < this->shapes.end(); i++)
	{
		std::cout << (*i)->isWithinCircle(_cx, _cy, _r) << std::endl;
	}
}

bool SVGParser::save()
{
	if (!this->lastFile.empty())
	{
		currentFile = lastFile;
		std::ofstream fileToWriteTo(currentFile + ".svg");
		if (fileToWriteTo.is_open())
		{
			std::vector<std::string>::const_iterator i = this->fileContent.begin();

			fileToWriteTo << this->svgLine << '\n';

			// Iterate over the shapes 
			for (auto j = this->shapes.begin(); j < this->shapes.end(); j++)
			{
				fileToWriteTo << "<" << (*j)->getName() << " ";
				for (auto k = (*j)->attributes.begin(); k != (*j)->attributes.end(); k++)
				{
					fileToWriteTo << k->first << "=" << "\"" << k->second << "\"" << " ";
				}

				fileToWriteTo << "/> \n";
			}

			fileToWriteTo << "</svg>";

			fileToWriteTo.close();
			std::cout << "Successfully saved " << currentFile << std::endl;
			return true;
		}
		else
		{
			std::cout << "Error opening the file to save!" << std::endl;
		}

		// The 'save as' function can be reused, but the information messages must be corrected
		/*if (this->saveAs(this->currentFile + "_" + ".svg"))
		{
			std::remove(this->currentFile.c_str());
			std::rename((this->currentFile + "_" + ".svg").c_str(), (this->currentFile + ".svg").c_str());
			return true;
		}*/
	}
	std::cout << "Error saving the file!" << std::endl;
	return false;
}


SVGParser::~SVGParser()
{
	for (auto i = this->shapes.begin(); i < this->shapes.end(); i++)
	{
		delete *i;
		this->shapes.erase(i);
	}
}
