#pragma once
#include <vector>
#include "Telem.h"
#include <fstream>
#include <iostream>
#include <string>
/**
 * @brief Class to handle image data operations.
 *
 * This class is responsible for managing image data, including reading from files
 * and providing access to the image data. It uses a vector to store the image data
 * in bytes and manages file operations for reading images.
 */

class ImageData
{
private:
	std::vector<unsigned char> data; ///< Buffer to store image data in bytes.
	Telem t; ///< Telemetry object (if used for additional metadata or operations).
	int fileSize; ///< Size of the image file in bytes.
	int totalBytesRead; ///< Total number of bytes read from the file.

public:
	/**
	 * @brief Construct a new ImageData object.
	 *
	 * Initializes fileSize and totalBytesRead to zero and clears any existing data.
	 */
	ImageData()
	{
		fileSize = 0;
		totalBytesRead = 0;
		data.clear();
	}
	/**
	 * @brief Reads an image from a file and stores it in the buffer.
	 *
	 * The function opens a file from a predefined path, reads its contents,
	 * and stores it in an internal buffer. It handles file operations and errors.
	 *
	 * @exception std::runtime_error Thrown if the file cannot be opened.
	 */
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
	/**
	 * @brief Get the Image data as a vector of bytes.
	 *
	 * This function provides access to the image data that has been read and stored.
	 * The data is returned as a vector of unsigned char (bytes).
	 *
	 * @return std::vector<unsigned char> The image data.
	 */
	std::vector<unsigned char> getImage()
	{
		return data;
	}
};