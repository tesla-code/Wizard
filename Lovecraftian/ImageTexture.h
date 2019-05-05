#pragma once
#include<string>

enum ImageType { png = 0, jpg = 1 };

class ImageTexture
{
private:
	GLuint textureID; // for rendering

public:
	// constructor
	ImageTexture(std::string filePath, ImageType imageType);

	// functions
	void bind() const;
	void unbind();
	int getID();
};