#pragma once

#include "Shader.h"
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Terrain.h"

#include <limits.h>

#include "ImageTexture.h"

// Based on height values use different colors/textures
enum BIOME
{
	WATER, GRASS, DIRT, MOUNTAIN
};


const int MAP_WIDTH = 15;
const int MAP_HEIGHT = 14;

class Floor
{
public:
	unsigned int VAO_ground = 0;
	unsigned int VAO_LineStrip = 0;
	int mapWidth = 0;
	int mapHegiht = 0;
	int numberOfVertices = 12;


	float groundVerices[18] =
	{	// x    y      z	
		-0.5f,  0.5f, -0.5f, // 
		 0.5f, 0.5f, -0.5f,  // triangle on its own z axis 
		-0.5f,  0.5f, 0.5f,  // 

		-0.5f,  0.5f, 0.5f, // vertex 1
		 0.5f,  0.5f, 0.5f, // vertex 2
		 0.5f,  0.5f, -0.5f, // vertex 3
	};

	// Find all the indices we need for GL_TRIANGLE_STRIP
	float firstSquare[32] =	
	{	// x    y      z		// colors  				Texcoords	
		-0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	 // bottom left		
  		 0.5f, 0.5f, -0.5f,	   0.0f, 1.0f, 0.0f,	1.0f, 0.0f,		   // bottom right
		-0.5f,  0.5f, 0.5f,	   0.0f, 0.0f, 1.0f,	0.0f, 0.0f,		   // top left
		 0.5f,  0.5f, 0.5f,    1.0f, 1.0f, 0.0f,	0.0f, 1.0f			// top right 
	};

	// we need 6 more floats (2 more positons / vertexs)
	
	float twoSquaresInARow[48] =
	{
		// x    y      z
		-0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,	1.0f, 1.0f,	 // bottom left		
		 0.5f, 0.5f, -0.5f,	   0.0f, 1.0f, 0.0f,	1.0f, 0.0f,	 // bottom right
		-0.5f,  0.5f, 0.5f,	   0.0f, 0.0f, 1.0f,	0.0f, 0.0f,	 // top left
		 0.5f,  0.5f, 0.5f,    1.0f, 1.0f, 0.0f,	0.0f, 1.0f,	 // top right 

		 1.5f, 0.5f, -0.5f,	   0.0f, 1.0f, 0.0f,	1.0f, 0.0f,		   // bottom right
		 1.5f,  0.5f, 0.5f,    1.0f, 1.0f, 0.0f,	0.0f, 1.0f			// top right 
	};

	// Lets try and draw 15 squares witch is the widht of the map
	// (15 * 6) + 6 
	float oneRow[3392]; // 3392



public:
	Floor();
	void render(Shader 	groundShader, glm::vec3 i_worldPos, Terrain* terrain);
	void renderOnScreen(Shader groundShader);
	void renderWithLineStrip(Shader i_shader, unsigned int textureID);

	void initFloor(Terrain* terrain);
};