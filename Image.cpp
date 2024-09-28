
#include "Image.h"

Image::Pixel::Pixel()
{
	Red = 0;
	Green = 0;
	Blue = 0;
}

Image::Pixel::Pixel(unsigned char r, unsigned char g, unsigned char b)
{
	Red = r;
	Green = g;
	Blue = b;
}

Image::Image(string directory)
{
	ifstream TGA(directory, ios_base::binary);
	createHeader(directory, TGA);
	createImage(directory, TGA);
}

void Image::createImage(string _directory, ifstream& file)
{
	unsigned int pixelVectorLength = headerData.height;
	pixelVectorLength *= headerData.width;

	for (unsigned int i = 0; i < pixelVectorLength; i++)
	{
		unsigned char throwawayRed = 0;
		unsigned char throwawayGreen = 0;
		unsigned char throwawayBlue = 0;

		file.read((char*)&throwawayBlue, sizeof(throwawayBlue));
		file.read((char*)&throwawayGreen, sizeof(throwawayGreen));
		file.read((char*)&throwawayRed, sizeof(throwawayRed));
		Pixel pixel(throwawayRed, throwawayGreen, throwawayBlue);
		pixelData.push_back(pixel);

	}
}

void Image::createHeader(string __directory, ifstream& file)
{
	char _idLength;
	file.read(&_idLength, sizeof(headerData.idLength));
	headerData.idLength = _idLength;

	char _colorMapType;
	file.read(&_colorMapType, sizeof(headerData.colorMapType));
	headerData.colorMapType = _colorMapType;

	char _dataTypeCode;
	file.read(&_dataTypeCode, sizeof(headerData.dataTypeCode));
	headerData.dataTypeCode = _dataTypeCode;

	short _colorMapOrigin;
	file.read((char*)&_colorMapOrigin, sizeof(headerData.colorMapOrigin));
	headerData.colorMapOrigin = _colorMapOrigin;

	short _colorMapLength;
	file.read((char*)&_colorMapLength, sizeof(headerData.colorMapLength));
	headerData.colorMapLength = _colorMapLength;

	char _colorMapDepth;
	file.read(&_colorMapDepth, sizeof(headerData.colorMapDepth));
	headerData.colorMapDepth = _colorMapDepth;

	short _xOrigin; //this is always 0
	file.read((char*)&_xOrigin, sizeof(headerData.xOrigin));
	headerData.xOrigin = _xOrigin;

	short _yOrigin;
	file.read((char*)&_yOrigin, sizeof(headerData.yOrigin));
	headerData.yOrigin = _yOrigin;

	short _width;
	file.read((char*)&_width, sizeof(headerData.width));
	headerData.width = _width;

	short _height;
	file.read((char*)&_height, sizeof(headerData.height));
	headerData.height = _height;

	char _bitsPerPixel;
	file.read(&_bitsPerPixel, sizeof(headerData.bitsPerPixel));
	headerData.bitsPerPixel = _bitsPerPixel;

	char _imageDescriptor;
	file.read(&_imageDescriptor, sizeof(headerData.imageDescriptor));
	headerData.imageDescriptor = _imageDescriptor;
}

void Image::writeImage(string oldDirectory, string newDirectory, vector<Image::Pixel>& data)
{
	ofstream outputStream(newDirectory, ios_base::binary);
	outputStream.write((char*)&headerData.idLength, sizeof(headerData.idLength));
	outputStream.write((char*)&headerData.colorMapType, sizeof(headerData.colorMapType));
	outputStream.write((char*)&headerData.dataTypeCode, sizeof(headerData.dataTypeCode));
	outputStream.write((char*)&headerData.colorMapOrigin, sizeof(headerData.colorMapOrigin));
	outputStream.write((char*)&headerData.colorMapLength, sizeof(headerData.colorMapLength));
	outputStream.write((char*)&headerData.colorMapDepth, sizeof(headerData.colorMapDepth));
	outputStream.write((char*)&headerData.xOrigin, sizeof(headerData.xOrigin));
	outputStream.write((char*)&headerData.yOrigin, sizeof(headerData.yOrigin));
	outputStream.write((char*)&headerData.width, sizeof(headerData.width));
	outputStream.write((char*)&headerData.height, sizeof(headerData.height));
	outputStream.write((char*)&headerData.bitsPerPixel, sizeof(headerData.bitsPerPixel));
	outputStream.write((char*)&headerData.imageDescriptor, sizeof(headerData.imageDescriptor));
	int testt = 0;
	for (unsigned int i = 0; i < pixelData.size(); i++)
	{
		int test = 0;
		outputStream.write((char*)&pixelData.at(i).Blue, sizeof(pixelData.at(i).Blue));
		outputStream.write((char*)&pixelData.at(i).Green, sizeof(pixelData.at(i).Green));
		outputStream.write((char*)&pixelData.at(i).Red, sizeof(pixelData.at(i).Red));
		testt+= test;

	}
}
