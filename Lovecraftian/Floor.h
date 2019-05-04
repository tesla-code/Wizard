#pragma once

#include "Shader.h"
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Terrain.h"

#include <limits.h>

// Based on height values use different colors/textures
enum BIOME
{
	WATER, GRASS, DIRT, MOUNTAIN
};

class Floor
{
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
	float firstSquare[12] =
	{	// x    y      z	 // differnece betwnne vertex 1 and two is 1 in z value
		-0.5f,  0.5f, -0.5f, // bottom left		(if you think that you are)
  		 0.5f, 0.5f, -0.5f,  // bottom right	(looking down on the x and z axis)
		-0.5f,  0.5f, 0.5f,  // top left

//		-0.5f,  0.5f, 0.5f, // Used twice (we dont need that since we use line strip  tbh)
		 0.5f,  0.5f, 0.5f, // top right 
//		 0.5f,  0.5f, -0.5f, // same as the one that was on its own
	};

	// we need 6 more floats (2 more positons / vertexs)
	
	float twoSquaresInARow[18] =
	{
		// x    y      z
		-0.5f,  0.5f, -0.5f, // bottom left	
		 0.5f,  0.5f, -0.5f,  // bottom right	
		-0.5f,  0.5f, 0.5f,  // top left
		 0.5f,  0.5f, 0.5f,  // top right

		 0.5f + 1,  0.5f, -0.5f,  // bottom right	
		 0.5f + 1,  0.5f, 0.5f,  // top right 
	};

	// Lets try and draw 15 squares witch is the widht of the map
	//       
	float oneRow[(12 * 15 * 14)];


public:
	Floor();
	void render(Shader 	groundShader, glm::vec3 i_worldPos, Terrain* terrain);
	void renderOnScreen(Shader groundShader);
	void renderWithLineStrip(Shader i_shader);

	void initFloor(Terrain* terrain);
};