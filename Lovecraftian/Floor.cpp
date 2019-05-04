#include "Floor.h"


void Floor::render(Shader groundShader, glm::vec3 I_worldPos, Terrain* heigtmap)
{
	/*
	glm::vec3 worldPos = glm::vec3(0, 0, 0);
	// world space positions of our ground
	glm::vec3 floorPositon[] =
	{
		worldPos,
	}; */
	groundShader.use();
	glBindVertexArray(VAO_ground);

	// calculate the model matrix for each object and pass it to shader before drawing
	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	for (int i = 0; i < heigtmap->getMapHeight(); i++)
	{
		for (int j = 0; j < heigtmap->getMapWidth(); j++) {
			glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
			model = glm::translate(model, glm::vec3(i, heigtmap->getHeight(i,j), j));

			// float angle = 20.0f * 1;
			// model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f)); 
			groundShader.setMat4("model", model);
			groundShader.use();

			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	} 

}

void Floor::renderWithLineStrip(Shader i_shader)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	model = glm::translate(model, glm::vec3(0, -5, 0));

	// trenger to pos til... for square
	i_shader.use();
	i_shader.setMat4("model", model);
	i_shader.use();

	glBindVertexArray(VAO_LineStrip);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 840);		// was 32
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Floor::renderOnScreen(Shader groundShader)
{
	glBindVertexArray(VAO_ground);
	groundShader.use();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

Floor::Floor()
{


	unsigned int VBO_ground = 0;

	glGenVertexArrays(1, &VAO_ground);
	glBindVertexArray(VAO_ground);

	glGenBuffers(1, &VBO_ground);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ground);
	glBufferData(GL_ARRAY_BUFFER, sizeof(groundVerices), groundVerices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_ground);
	glBufferData(GL_ARRAY_BUFFER, sizeof(groundVerices), groundVerices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



}


void Floor::initFloor(Terrain* terrain)
{
	int counter = 12;
	/*
	for (int j = 0; j < 1; j++)
	{
		for (int t = 0; t < 1; t++)
		{
			// bottom left			// Position    1
			oneRow[t++] = -0.5f;	// x
			oneRow[t++] = 0.5f;		// y
			oneRow[t++] = -0.5f;	// z

			// bottom right                       2
			oneRow[t++] = 0.5f;
			oneRow[t++] = 0.5f;
			oneRow[t++] = -0.5f;

			// top left                           3
			oneRow[t++] = -0.5f;
			oneRow[t++] = 0.5f;
			oneRow[t++] = 0.5f;

			// top right                        4
			oneRow[t++] = 0.5f;
			oneRow[t++] = 0.5f;
			oneRow[t++] = 0.5f;
		}

		for (int i = 0; i < 15; i++) // width
		{
			// bottom right
			oneRow[counter++] = 0.5f + i + 1;		// x
			oneRow[counter++] = 0.5f;		// y
			oneRow[counter++] = -0.5f;		// z

			// top right
			oneRow[counter++] = 0.5f + i + 1;
			oneRow[counter++] = 0.5f;
			oneRow[counter++] = 0.5f;
		}
	}

	*/

	int t = 0;
	for (int j = 0; j < 14; j++)
	{
		for (int i = 0; i < 15; i++) // width
		{
			// bottom left			// Position    1       
			oneRow[t++] = -0.5f + i + 1;	// x
			oneRow[t++] = 0.5f + terrain->getHeight(j, i);		// y
			oneRow[t++] = -0.5f + j;	// z

			// bottom right                       2
			oneRow[t++] = 0.5f + i + 1;
			oneRow[t++] = 0.5f;
			oneRow[t++] = -0.5f + j;

			// top left                           3
			oneRow[t++] = -0.5f + i + 1;
			oneRow[t++] = 0.5f;
			oneRow[t++] = 0.5f + j;

			// top right                        4
			oneRow[t++] = 0.5f + i + 1;
			oneRow[t++] = 0.5f;
			oneRow[t++] = 0.5f + j;

		}
	}


	int width = terrain->getMapWidth();


	// GL LINE STRIP STUFF
	unsigned int VBO_Line = 0;

	glGenVertexArrays(1, &VAO_LineStrip);
	glBindVertexArray(VAO_LineStrip);

	glGenBuffers(1, &VBO_Line);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Line);
	glBufferData(GL_ARRAY_BUFFER, sizeof(oneRow), oneRow, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}