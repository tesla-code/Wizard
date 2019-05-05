
#include <GL/glew.h>

#include "Terrain.h" 
#include "stb_image.h"
#include <iostream>

void Terrain::loadHeightMap(std::string filePath, ImageType imageType)
{
	int image_width = 0;
	int image_height = 0;
	int bpp;
	int nrChannels = 1; // STBI_rgb_alpha is 4
	data = stbi_load(filePath.c_str(), &image_width, &image_height, &bpp, nrChannels);

	// width and height of terrain
	this->terrainImageWidth = (unsigned int) image_width;
	this->terrainImageHeight = (unsigned int)image_height;
	this->size = (unsigned long)(unsigned int)image_width * (unsigned int)image_height;

	if (!data)
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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glActiveTexture(0);				 // activate texture unit 0
	glBindTexture(GL_TEXTURE_2D, 0); // glGenTextures will never give us a id of 0

	scanHeightMap();

}


void Terrain::scanHeightMap()
{
	unsigned char tmp_min, tmp_max;

	tmp_min = 255;
	tmp_max = 0;

	std::vector<float> tmp;
	// Loop over all rgb values inn the image
	int counter = 0;
	for (int i = 0; i < this->terrainImageHeight; i++)
	{
		tmp.clear();
		for (int j = 0; j < this->terrainImageWidth; j++)
		{
			tmp.push_back((float)data[counter++] / 255.0f); // normalize to 0, 1
		}
		heights.push_back(tmp);
	}


	// Loop over all rgb values inn the image
	for (int i = 0; i < this->size; i++)
	{
		if (this->data[i] < tmp_min)
		{
			tmp_min = this->data[i];
		}
		if (this->data[i] > tmp_max)
		{
			tmp_max = this->data[i];
		}
	}

	this->min = tmp_min;		// min 41
	this->max = tmp_max;		// max 255
	this->range = max - min;	// 204

	fprintf(stderr, "img Width: %u\n", this->terrainImageWidth);
	fprintf(stderr, "img Height: %u\n", this->terrainImageHeight);
	fprintf(stderr, "img size: %u\n", this->size);

	fprintf(stderr, "Min: %u\n", this->min);
	fprintf(stderr, "Max: %u\n", this->max);
	fprintf(stderr, "Range: %u\n", this->range);

}


void Terrain::renderMap()
{

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

float Terrain::getHeight(int x, int y)
{
	return heights[x][y];
}

int Terrain::getMapWidth()
{
	return terrainImageWidth;
}

int Terrain::getMapHeight()
{
	return terrainImageHeight;
}