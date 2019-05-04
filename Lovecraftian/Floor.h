#pragma once

#include "Shader.h"
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Terrain.h"

// Based on height values use different colors/textures
enum BIOME
{
	WATER, GRASS, DIRT, MOUNTAIN
};

class Floor
{
	unsigned int VAO_ground = 0;
	unsigned int VAO_LineStrip = 0;

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
		-0.5f,  0.5f, -0.5f, // 
		 0.5f, 0.5f, -0.5f,  // triangle on its own z axis 
		-0.5f,  0.5f, 0.5f,  // 

//		-0.5f,  0.5f, 0.5f, // Used twice (we dont need that since we use line strip  tbh)
		 0.5f,  0.5f, 0.5f, // new vertices has + 1 more z than the one that was on its own in trangle
//		 0.5f,  0.5f, -0.5f, // same as the one that was on its own
	};


	float twoSquaresInARow[18 * 2] =
	{
		-0.5f,  0.5f, -0.5f, // vertex 1
		 0.5f, 0.5f, -0.5f, // vertex 2
		-0.5f,  0.5f, 0.5f, // vertex 3

	  //  x       y    z
		-0.5f,  0.5f, 0.5f, // vertex 1
		 0.5f,  0.5f, 0.5f, // vertex 2
		 0.5f,  0.5f, -0.5f, // vertex 3


	};




public:
	Floor();
	void render(Shader 	groundShader, glm::vec3 i_worldPos, Terrain* terrain);
	void renderOnScreen(Shader groundShader);
	void renderWithLineStrip(Shader i_shader);
};