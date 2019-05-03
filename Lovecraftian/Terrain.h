#pragma once

#include <string>
#include <vector>

#include "Texture.h" // for image type enum

class Terrain
{
private:
	unsigned int mapID;	// not 100% sure we need this

	unsigned int terrainImageWidth;
	unsigned int terrainImageHeight;

	unsigned long size; // size of the array I guess

	// z dimensions (range = max - min = relief)
	unsigned char min;
	unsigned char max;
	unsigned char range;

	unsigned char* data;

	std::vector<std::vector<float>> heights;  // elevation[][]

public:
	void loadHeightMap(std::string filePath, ImageType imageType);
	void scanHeightMap();
	void renderMap();

	// functions
	void bind() const;
	void unbind();
	int getID();
};