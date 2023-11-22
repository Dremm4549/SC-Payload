#include "ImageData.h"
ImageData::ImageData()
{
	imageFile.open("../../SpaceImages/Image4.jpg",std::ios::binary | std::ios::in | std::ios::ate);
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

std::string ImageData::ConvertBinaryToHex(const std::string& s, bool upper_case) 
{
	std::ostringstream ret;

	for (std::string::size_type i = 0; i < s.length(); i++) 
	{
		ret << std::hex << std::setfill('0') << std::setw(2) << (upper_case ? std::uppercase : std::nouppercase) << (int)s[i];
	}

	return ret.str();
}

void ImageData::SetImageFileSize()
{

	if (!imageFile.is_open()) 
	{
		std::cerr << "FAILED TO OPEN FILE" << std::endl;
		return;
	}

	std::streampos imgFileSize = imageFile.tellg();
	if (imgFileSize > 0) 
	{
		std::cout << std::endl << imgFileSize << std::endl;
		fileSize = imgFileSize;
	}
}

int ImageData::GetImageFileSize(){
	return fileSize;
}
std::vector<char> ImageData::AllocateImageBuffer(int size)
{
	std::vector<char> buffer(size);
	imageBuffer = new char[size];
	return buffer;
}
void ImageData::StoreImageInMemmory()
{
	if (!imageFile.is_open()) 
	{
		std::cerr << "FAILED TO OPEN FILE" << std::endl;
		return;
	}
	
	imageFile.seekg(0, std::ios::beg);
	imageFile.read(imageBuffer, fileSize);
	
	imageFile.close();

	imageHex = ConvertBinaryToHex(std::string(imageBuffer, imageBuffer + fileSize), true);

}

std::string ImageData::GetImageHex()
{
	return imageHex;
}



