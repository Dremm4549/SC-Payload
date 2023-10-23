#pragma once
#include <vector>
#include "Telem.h"
/// <summary>
/// This class is expected to handle all image data functions
/// </summary>
class ImageData
{
private:
	std::vector<unsigned char> data;
	Telem t;

public:
	/// <summary>
	/// Default constructor for ImageData
	/// </summary>
	ImageData()
	{
		data.clear();
	}
	/// <summary>
	/// Reading the image from a text file and saving it to the image buffer
	/// </summary>
	void downloadImage()
	{

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