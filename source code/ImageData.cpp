#include "ImageData.h"
ImageData::ImageData()
{
	fileSize = 0;
	totalBytesRead = 0;
	data.clear();
}
void ImageData::downloadImage()
{
	std::string filePath = "../../SpaceImages";

	std::ifstream file(filePath, std::ios::binary);

	if (!file.is_open()) {
		std::cerr << "FAILED TO OPEN FILE" << std::endl;
		return;
	}

	file.seekg(0, std::ios::end);
	std::streampos fileSize = file.tellg();
	if (fileSize > 0) {
		std::cout << std::endl << fileSize << std::endl;
	}

	char* imageBuffer = new char[fileSize];

	file.seekg(0, std::ios::beg);
	file.read(imageBuffer, fileSize);

	delete[] imageBuffer;

}

std::vector<unsigned char> ImageData::getImage()
{
	return data;
}

std::pair<std::vector<unsigned char>, Telem> ImageData::getCombinedData()
{
	return { data, t };
}