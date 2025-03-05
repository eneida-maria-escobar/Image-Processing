#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Image
{
public:
	string fileDirectory;
public:
	struct Header
	{
	public:
		/*The following variables are all given in the PDF*/
		char idLength;
		char colorMapType;
		char dataTypeCode;

		short colorMapOrigin;
		short colorMapLength;

		char colorMapDepth;

		short xOrigin;
		short yOrigin;
		short width;
		short height;

		char bitsPerPixel;
		char imageDescriptor;
		//I don't think we need constructors because the values are
	};
	struct Pixel
	{
	public:
		unsigned char Red, Green, Blue;
		Pixel();
		Pixel(unsigned char r, unsigned char g, unsigned char b);
	};
	//These variables have to be defined under the class definition
public:
	Header headerData;
	vector<Pixel> pixelData;
	
	Image(string directory);
	void createImage(string _directory, ifstream& file);
	void createHeader(string __directory, ifstream& file);
	void writeImage(string oldDirectory, string newDirectory, vector<Image::Pixel>& data);
};
