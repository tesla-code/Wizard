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
	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	model = glm::translate(model, glm::vec3(0, -5, 0));

	// trenger to pos til... for square
	i_shader.use();
	i_shader.setMat4("model", model);
	i_shader.use();


	glBindVertexArray(VAO_LineStrip);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

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





	// GL LINE STRIP STUFF
	unsigned int VBO_Line = 0;

	glGenVertexArrays(1, &VAO_LineStrip);
	glBindVertexArray(VAO_LineStrip);

	glGenBuffers(1, &VBO_Line);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_Line);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstSquare), firstSquare, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_Line);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstSquare), firstSquare, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}