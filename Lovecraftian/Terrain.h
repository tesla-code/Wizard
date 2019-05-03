#pragma once

#include <string>
#include "Texture.h" // for image type enum

class Terrain
{
private:
	unsigned int mapID;

public:
	void loadHeightMap(std::string filePath, ImageType imageType);

	// functions
	void bind() const;
	void unbind();
	int getID();

};