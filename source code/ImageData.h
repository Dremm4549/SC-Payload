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
	ImageData();
	/**
	 * @brief Reads an image from a file and stores it in the buffer.
	 *
	 * The function opens a file from a predefined path, reads its contents,
	 * and stores it in an internal buffer. It handles file operations and errors.
	 *
	 * @exception std::runtime_error Thrown if the file cannot be opened.
	 */
	void downloadImage();
	/**
	 * @brief Get the Image data as a vector of bytes.
	 *
	 * This function provides access to the image data that has been read and stored.
	 * The data is returned as a vector of unsigned char (bytes).
	 *
	 * @return std::vector<unsigned char> The image data.
	 */
	void setTelemetryData(const Telem& telemetry);

	std::vector<unsigned char> getImage();

	std::pair<std::vector<unsigned char>, Telem> getCombinedData();
};