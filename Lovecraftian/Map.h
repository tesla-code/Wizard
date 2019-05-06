#pragma once

#include "Shader.h"
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Terrain.h"

class Map
{

public:
	int mapWidth = 15;
	int mapHeight = 14;
	GLuint VAO_map;

	// First sqaure has 12 floats
	// and 4 draw calls
						// mapWidth * 6
	 //            (16 * 6)
	//                      pos size       color size
	float firstSquare[((15 * 12) * (13)) ] =
	{
	/*	-0.5f,  0.5f, -0.5f,  // bottom left		
		 0.5f, 0.5f, -0.5f,   // bottom right
		-0.5f,  0.5f, 0.5f,   // top left
		 0.5f,  0.5f, 0.5f,   // top right */
	};

public:
	Map(Terrain* terrain);
	void renderOnScreen(Shader mapShader);
	void initMap();
};