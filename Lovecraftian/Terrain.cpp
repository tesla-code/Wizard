
#include <GL/glew.h>

#include "Terrain.h" 
#include "stb_image.h"
#include <iostream>

void Terrain::loadHeightMap(std::string filePath, ImageType imageType)
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

	mapID; // basicly texture id
	glGenTextures(1, &mapID);
	glBindTexture(GL_TEXTURE_2D, mapID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// x
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	// y
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glActiveTexture(0);				 // activate texture unit 0
	glBindTexture(GL_TEXTURE_2D, 0); // glGenTextures will never give us a id of 0

}


void Terrain::bind() const
{
	glBindTexture(GL_TEXTURE_2D, mapID);
}

// unbindes the texture
void Terrain::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


int Terrain::getID()
{
	return mapID;
}