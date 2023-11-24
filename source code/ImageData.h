#pragma once
#include <vector>
#include "Telem.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
/**
 * @brief Class to handle image data operations.
 *
 * This class is responsible for managing image data, including reading from files
 * and providing access to the image data. It uses a vector to store the image data
 * in bytes and manages file operations for reading images.
 */

#define MAXBUFFERSIZE 65536 ///< Buffer size as defined by project

class ImageData
{
private:
	std::vector<unsigned char> data; ///< Buffer to store image data in bytes.
	Telem t; ///< Telemetry object (if used for additional metadata or operations).
	int fileSize; ///< Size of the image file in bytes.
	int totalBytesRead; ///< Total number of bytes read from the file.
	std::ifstream imageFile; /// To be changed static file
	char* imageBuffer; ///< Buffer to store image data in bytes.
	std::string imageHex; ///< Hex representation of image data.

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
	std::vector<unsigned char> getImage();
	/**
	 * @brief Converts image binary to HEX
	 *
	 * This function takes the stored image file from memory and 
	 * converts it to hexidecimal
	 *
	 * @return std::string The hexidecimal binary data.
	 */
	std::string ConvertBinaryToHex(const std::string& s, bool upper_case);
	/**
	 * @brief allowcates space for image buffer
	 *
	 * This function takes the stored image file from memory and 
	 * converts it to hexidecimal
	 *
	 * @return std::string The hexidecimal binary data.
	 */
	void SetImageFileSize();
	/**
	 * @brief allowcates space for image buffer
	 *
	 * This function takes the stored image file from memory and 
	 * converts it to hexidecimal
	 *
	 * @return std::string The hexidecimal binary data.
	 */
	int GetImageFileSize();
	/**
	 * @brief allowcates image buffer array
	 *
	 * This function takes the stored image file from memory and 
	 * converts it to hexidecimal
	 *
	 * @return std::string The hexidecimal binary data.
	 */
	 std::vector<char> AllocateImageBuffer(int size);
	/**
	 * @brief allowcates image buffer array
	 *
	 * This function takes the stored image file from memory and 
	 * converts it to hexidecimal
	 *
	 * @return std::string The hexidecimal binary data.
	 */
	void StoreImageInMemmory();
	/**
	 * @brief allowcates image buffer array
	 *
	 * This function takes the stored image file from memory and 
	 * converts it to hexidecimal
	 *
	 * @return std::string The hexidecimal binary data.
	 */
	std::string GetImageHex();
	/**
	 * @brief allowcates image buffer array
	 *
	 * This function takes the stored image file from memory and 
	 * converts it to hexidecimal
	 *
	 * @return std::string The hexidecimal binary data.
	 */
	void OpenImage(std::string imageToBeOpened);
	/**
	 * @brief Closes open image file
	 * 
	 * This function closes the image file that was opened
	 * It makes sure that file handling is released properly 
	 * 
	*/
	void CloseImage();
};