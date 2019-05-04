#pragma once

#include "Shader.h"
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Based on height values use different colors/textures
enum BIOME
{
	WATER, GRASS, DIRT, MOUNTAIN
};

class Floor
{
	unsigned int VAO_ground = 0;
	
	float groundVerices[9] =
	{	// x    y      z
		-0.5f, -0.5f, -0.5f, // vertex 1
		 0.5f, -0.5f, -0.5f, // vertex 2
		 0.0f,  0.5f, -0.5f, // vertex 3
	};

public:
	Floor();
	void render(Shader 	groundShader);
};