#include "ImageData.h"
ImageData::ImageData()
{
	//imageFile.open("../../SpaceImages/Image4.jpg",std::ios::binary | std::ios::in | std::ios::ate);
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
		//std::cout << std::endl << fileSize << std::endl;
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

std::string ImageData::ConvertBinaryToHex(const char* buffer, size_t size, bool upper_case) {
    std::ostringstream ret;
    for (size_t i = 0; i < size; ++i) {
        ret << std::hex << std::setfill('0') << std::setw(2)
            << (upper_case ? std::uppercase : std::nouppercase)
            << static_cast<int>(static_cast<unsigned char>(buffer[i]));
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
	
	imageFile.seekg(0, std::ios::end);
	fileSize = imageFile.tellg();
	imageFile.seekg(0, std::ios::beg);

	char* tmpimageBuffer = new char[fileSize];

	imageFile.read(tmpimageBuffer, fileSize);
	
	imageFile.close();

	imageHex = ConvertBinaryToHex(tmpimageBuffer, fileSize, true);

	std::cout << "size: " << imageHex.size() << std::endl;
	// if(ConvertHexToBinaryAndWriteToFile(imageHex, "./output.jpg"))
	// {
	// 	std::cout << "word";
	// }

}

bool ImageData::ConvertHexToBinaryAndWriteToFile(const std::string& hexStr, const std::string& outputPath)
{
	std::ofstream outputFile(outputPath, std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
        return false;
    }

    for (size_t i = 0; i < hexStr.length(); i += 2) {
        std::string byteString = hexStr.substr(i, 2);
        char byte = static_cast<char>(std::stoi(byteString, nullptr, 16));
        outputFile.write(&byte, sizeof(char));
    }

    outputFile.close();
    return true;
}

std::string ImageData::GetImageHex()
{
	return imageHex;
}

void ImageData::OpenImage(std::string imageToBeOpened)
{
	imageFile.open(imageToBeOpened,std::ios::binary | std::ios::in | std::ios::ate);
}

void ImageData::CloseImage()
{
	imageFile.close();
}



