#include "Floor.h"

void Floor::render(Shader groundShader, glm::vec3 I_worldPos, Terrain* heigtmap)
{
	
	groundShader.use();
	glBindVertexArray(VAO_ground);

	// calculate the model matrix for each object and pass it to shader before drawing
	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	for (int i = 0; i < heigtmap->getMapHeight(); i++)
	{
		for (int j = 0; j < heigtmap->getMapWidth(); j++) {
			glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			model = glm::translate(model, glm::vec3(i, heigtmap->getHeight(i, j), j));

			// float angle = 20.0f * 1;
			// model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f)); 
			groundShader.setMat4("model", model);
			groundShader.use();

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}

}

void Floor::renderWithLineStrip(Shader i_shader, unsigned int textureID)
{
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	model = glm::translate(model, glm::vec3(0, -5, 0));

	// trenger to pos til... for square
	i_shader.use();
	i_shader.setMat4("model", model);
	i_shader.use();

	glActiveTexture(textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glBindVertexArray(VAO_LineStrip);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 452);
}

void Floor::renderOnScreen(Shader groundShader)
{
	glBindVertexArray(VAO_ground);
	groundShader.use();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

Floor::Floor()
{
	/*  NO reason to work here  unless ur working on clouds
		or something.											*/
	unsigned int VBO_ground = 0;

	glGenVertexArrays(1, &VAO_ground);
	glBindVertexArray(VAO_ground);

	glGenBuffers(1, &VBO_ground);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_ground);
	glBufferData(GL_ARRAY_BUFFER, sizeof(groundVerices), groundVerices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

// calculate all vertices here
void Floor::initFloor(Terrain* terrain)
{

	int numDrawCalls = 0;

	// BOTTOM LEFT (in an x and z sense)
	// Postions
	int counter = 0;

	
	oneRow[counter++] = -0.5f;	// x pos
	oneRow[counter++] = 0.5f;	// y pos
	oneRow[counter++] = -0.5f;	// z pos

	// colors
	oneRow[counter++] = 1.0f,
		oneRow[counter++] = 0.0f;
	oneRow[counter++] = 0.0f;

	// Tex Coords
	oneRow[counter++] = 1.0f;
	oneRow[counter++] = 1.0f;

	// BOTTOM RIGHT
	// Postions
	oneRow[counter++] = 0.5f;	// x pos
	oneRow[counter++] = 0.5f;	// y pos
	oneRow[counter++] = -0.5f;	// z pos

	// colors
	oneRow[counter++] = 0.0f,
		oneRow[counter++] = 1.0f;
	oneRow[counter++] = 0.0f;

	// Tex Coords
	oneRow[counter++] = 1.0f;
	oneRow[counter++] = 0.0f;

	// TOP LEFT
	// Postions
	oneRow[counter++] = -0.5f;	// x pos
	oneRow[counter++] = 0.5f;	// y pos
	oneRow[counter++] = 0.5f;	// z pos

	// colors
	oneRow[counter++] = 0.0f,
		oneRow[counter++] = 0.0f;
	oneRow[counter++] = 1.0f;

	// Tex Coords
	oneRow[counter++] = 0.0f;
	oneRow[counter++] = 0.0f;

	// TOP RIGHT
	// Postions
	oneRow[counter++] = 0.5f;	// x pos
	oneRow[counter++] = 0.5f;	// y pos
	oneRow[counter++] = 0.5f;	// z pos

	// colors
	oneRow[counter++] = 1.0f,
		oneRow[counter++] = 1.0f;
	oneRow[counter++] = 0.0f;

	// Tex Coords
	oneRow[counter++] = 0.0f;
	oneRow[counter++] = 1.0f;


	std::cout << " Counter is : " << counter << std::endl;

	numDrawCalls = 4;

	int move = 0;
	bool up = true;

	int i_WeNeed = 0;

	for (int j = 0; j < MAP_HEIGHT; j++)
	{
		up = true;
		// draw new square
		if (j % 2 == 1)  // this if is 4 draw calls
		{
			up = false;

			numDrawCalls += 4;
			// BOTTOM LEFT (in an x and z sense)
			// Postions
			int counter = 0;
			oneRow[counter++] = -0.5f;	// x pos
			oneRow[counter++] = 0.5f;		// y pos
			oneRow[counter++] = -0.5f + 1;		// z pos

			// colors
			oneRow[counter++] = 1.0f,
				oneRow[counter++] = 0.0f;
			oneRow[counter++] = 0.0f;

			// Tex Coords
			oneRow[counter++] = 1.0f;
			oneRow[counter++] = 1.0f;

			// BOTTOM RIGHT 2
			// Postions
			oneRow[counter++] = 0.5f;	// x pos
			oneRow[counter++] = 0.5f;	// y pos
			oneRow[counter++] = -0.5f + 1;	// z pos

			// colors
			oneRow[counter++] = 0.0f,
				oneRow[counter++] = 1.0f;
			oneRow[counter++] = 0.0f;

			// Tex Coords
			oneRow[counter++] = 1.0f;
			oneRow[counter++] = 0.0f;

			// TOP LEFT
			// Postions
			oneRow[counter++] = -0.5f;	// x pos
			oneRow[counter++] = 0.5f;	// y pos
			oneRow[counter++] = 0.5f + 1;	// z pos

			// colors
			oneRow[counter++] = 0.0f,
				oneRow[counter++] = 0.0f;
			oneRow[counter++] = 1.0f;

			// Tex Coords
			oneRow[counter++] = 0.0f;
			oneRow[counter++] = 0.0f;

			// TOP RIGHT
			// Postions
			oneRow[counter++] = 0.5f;	// x pos
			oneRow[counter++] = 0.5f;	// y pos
			oneRow[counter++] = 0.5f + 1;	// z pos

			// colors
			oneRow[counter++] = 1.0f,
				oneRow[counter++] = 1.0f;
			oneRow[counter++] = 0.0f;

			// Tex Coords
			oneRow[counter++] = 0.0f;
			oneRow[counter++] = 1.0f;
		}

		// 4 draw calls + 30 from loop = 34
		numDrawCalls += 30;
		for (int i = 0; i < MAP_WIDTH * 1; i++) // width
		{

			if (up)
			{
				move++;
			}
			else
			{
				move--;
			}

			// BOTTOM RIGHT
			// Postions
			oneRow[counter++] = 0.5f + move + 1;	// x pos
			oneRow[counter++] = 0.5f + terrain->getHeight(j, i);	// y pos
			oneRow[counter++] = -0.5f + j;	// z pos

			// colors
			oneRow[counter++] = 0.0f,
				oneRow[counter++] = 1.0f;
			oneRow[counter++] = 0.0f;

			// Tex Coords
			oneRow[counter++] = 1.0f;
			oneRow[counter++] = 0.0f;

			// TOP RIGHT
			// Postions
			oneRow[counter++] = 0.5f + move + 1;// x pos
			oneRow[counter++] = 0.5f + terrain->getHeight(j, i);	// y pos
			oneRow[counter++] = 0.5f + j;	// z pos

			// colors
			oneRow[counter++] = 1.0f,
				oneRow[counter++] = 1.0f;
			oneRow[counter++] = 0.0f;

			// Tex Coords
			oneRow[counter++] = 0.0f;
			oneRow[counter++] = 1.0f;
		}
	}


	/*

		for (int j = 0; j < 14; j++)
		{
			for (int i = 0; i < 15; i++) // width
			{
				oneRow[counter++] = -0.5f + i + 1;	// x pos
				oneRow[counter++] = 0.5f + terrain->getHeight(j, i);	// y pos
				oneRow[counter++] = -0.5f + j;	// z pos

				// colors
				oneRow[counter++] = 1.0f,
				oneRow[counter++] = 0.0f;
				oneRow[counter++] = 0.0f;

				// Tex Coords
				oneRow[counter++] = 1.0f;
				oneRow[counter++] = 1.0f;

				// BOTTOM RIGHT
				// Postions
				oneRow[counter++] = 0.5f + i + 1;	// x pos
				oneRow[counter++] = 0.5f;	// y pos
				oneRow[counter++] = -0.5f + j;	// z pos

				// colors
				oneRow[counter++] = 0.0f,
				oneRow[counter++] = 1.0f;
				oneRow[counter++] = 0.0f;

				// Tex Coords
				oneRow[counter++] = 1.0f;
				oneRow[counter++] = 0.0f;


				// TOP LEFT
				// Postions
				oneRow[counter++] = -0.5f + i + 1;	// x pos
				oneRow[counter++] = 0.5f;	// y pos
				oneRow[counter++] = 0.5f + j;	// z pos

				// colors
				oneRow[counter++] = 0.0f,
				oneRow[counter++] = 0.0f;
				oneRow[counter++] = 1.0f;

				// Tex Coords
				oneRow[counter++] = 0.0f;
				oneRow[counter++] = 0.0f;

				// TOP RIGHT
				// Postions
				oneRow[counter++] = 0.5f + i + 1;	// x pos
				oneRow[counter++] = 0.5f;	// y pos
				oneRow[counter++] = 0.5f + j;	// z pos

				// colors
				oneRow[counter++] = 1.0f,
				oneRow[counter++] = 1.0f;
				oneRow[counter++] = 0.0f;

				// Tex Coords
				oneRow[counter++] = 0.0f;
				oneRow[counter++] = 1.0f;



			}
		}



		*/



	std::cout << "Num draw calls: " << numDrawCalls << std::endl;
	std::cout << "Counter is: " << counter << std::endl;
	int width = terrain->getMapWidth();


	// GL LINE STRIP STUFF
	unsigned int VBO_Line = 0;

	glGenVertexArrays(1, &VAO_LineStrip);
	glBindVertexArray(VAO_LineStrip);

	glGenBuffers(1, &VBO_Line);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Line);

	glBufferData(GL_ARRAY_BUFFER, sizeof(oneRow), oneRow, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);



}