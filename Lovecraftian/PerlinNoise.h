#pragma once

#include <iostream>
#include <string>
#include <algorithm>

// this is image width tbh
class PerlinNoise
{
private:
	// 2D noise variables

	int perlin_imageWidth = 256;
	int perlin_imageHeight = 256;

	int nOutputWidth = 256;
	int nOutputHeight = 256;
	float* fNoiseSeed2D = nullptr;
	float* fPerlinNoise2D = nullptr;

	// 1D noise variables
	float* fNoiseSeed1D = nullptr;
	float* fPerlinNoise1D = nullptr;
	int nOutputSize = 256;


	int nOctaveCount = 1;
	float fScalingBias = 2.0f;
	int nMode = 1;

public:
	PerlinNoise();
	
	void perlin2D();
	void perlinNoise2D(int nWidth, int nHeight, float* fSeed, int nOctaves, float fBias, float* fOutput);

};