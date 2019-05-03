#pragma once

#include <string>
#include "Texture.h" // for image type enum

class Terrain
{
private:
	unsigned int mapID;	// not 100% sure we need this

	unsigned int terrainImageWidth;
	unsigned int terrainImageHeight;

	unsigned long size; // size of the array I guess

	// z dimensions (range = max - min = relief)
	unsigned char min, max, range;

	unsigned char* data;

public:
	void loadHeightMap(std::string filePath, ImageType imageType);
	void scanHeightMap();

	// functions
	void bind() const;
	void unbind();
	int getID();

};