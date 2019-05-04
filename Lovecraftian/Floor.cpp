#include "Floor.h"


void Floor::render(Shader groundShader)
{

	// world space positions of our cubes
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f)
	};

	glBindVertexArray(VAO_ground);

	// calculate the model matrix for each object and pass it to shader before drawing
	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	model = glm::translate(model, cubePositions[0]);
	float angle = 20.0f * 1;
	model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
	groundShader.setMat4("model", model);
	groundShader.use();


	glDrawArrays(GL_TRIANGLES, 0, 3);
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