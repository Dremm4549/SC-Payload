#pragma once
#include <vector>
#include "Telem.h"
#include <fstream>
#include <iostream>
#include <string>
/// <summary>
/// This class is expected to handle all image data functions
/// </summary>
class ImageData
{
private:
	std::vector<unsigned char> data;
	Telem t;
	int fileSize;
	int totalBytesRead;

public:
	/// <summary>
	/// Default constructor for ImageData
	/// </summary>
	ImageData()
	{
		fileSize = 0;
		totalBytesRead = 0;
		data.clear();
	}
	/// <summary>
	/// Reading the image from a text file and saving it to the image buffer
	/// </summary>
	void downloadImage()
	{
		std::string filePath = "../../SpaceImages";

		std::ifstream file(filePath, std::ios::binary);

		if(!file.is_open()){
			std::cerr << "FAILED TO OPEN FILE" << std::endl;
			return;
		}

		file.seekg(0,std::ios::end);
		std::streampos fileSize = file.tellg();
		if(fileSize > 0){
			std::cout << std::endl << fileSize << std::endl;
		}

		char* imageBuffer = new char[fileSize];

		file.seekg(0,std::ios::beg);
		file.read(imageBuffer, fileSize);

		delete[] imageBuffer;

	}
	/// <summary>
	/// Return image buffer the buffer will be a byte[] that holds the binary data max size 2GB storage
	/// </summary>
	/// <returns>The image data as a vector</returns>
	std::vector<unsigned char> getImage()
	{
		return data;
	}
};