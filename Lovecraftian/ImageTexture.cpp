#include "stb_image.h"
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "ImageTexture.h"

ImageTexture::ImageTexture(std::string filePath, ImageType imageType)
{
	int image_width = 0;
	int image_height = 0;
	int bpp;
	int nrChannels = 4; // STBI_rgb_alpha is 4
	unsigned char* imageData = stbi_load(filePath.c_str(), &image_width, &image_height, &bpp, nrChannels);

	if (!imageData)
	{
		std::cout << "ERROR::TEXTURE_LOADING_FAILED " << std::endl;
	}

	textureID; // basicly texture id
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// x
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	// y
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glActiveTexture(0);				 // activate texture unit 0
	glBindTexture(GL_TEXTURE_2D, 0); // glGenTextures will never give us a id of 0

	stbi_image_free(imageData);
}

void ImageTexture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

// unbindes the texture
void ImageTexture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


int ImageTexture::getID()
{
	return textureID;
}