#include "Map.h"

Map::Map(Terrain* terrain)
{


	mapWidth = terrain->getMapWidth();
	mapHeight = terrain->getMapHeight();

	std::cout << "Terrain width: " << mapWidth << std::endl;
	std::cout << "Terrain Height: " << mapHeight << std::endl;


	int numDrawCalls = 0;
	int size = 0;
	int counter = 0;
	/*
	// width = 15,     15 * 2 draw calls   +  15 * 6 size?
	bool up = true;
	int move = 0;
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < mapWidth; i++)
		{
			if (up)
			{
				// Top right + 1
				firstSquare[counter++] = 0.5f + i;  // x
				firstSquare[counter++] = 0.5f + terrain->getHeight(j, i);  // y
				firstSquare[counter++] = -0.5f + j;  // z

				// bottom right + 1
				firstSquare[counter++] = 0.5f + i;  // x
				firstSquare[counter++] = 0.5f + terrain->getHeight(j + 1, i); // y
				firstSquare[counter++] = 0.5f + j;  // z

				move++;
			}
			else
			{
				// bottom right + 1
				firstSquare[counter++] = 0.5f + move - 1;  // x
				firstSquare[counter++] = 0.5f + terrain->getHeight(j + 1, i); // y
				firstSquare[counter++] = 0.5f + j;  // z

				// Top right + 1
				firstSquare[counter++] = 0.5f + move - 1;  // x
				firstSquare[counter++] = 0.5f + terrain->getHeight(j, i);  // y
				firstSquare[counter++] = -0.5f + j;  // z

				move--;
			}
	
			numDrawCalls += 2;
			size += 6;
		}

		up = !up;
	} */

	/*
	// bottom right + 1 Z (down)   14
	firstSquare[counter++] = 0.5f + 14;  // x
	firstSquare[counter++] = 0.5f + terrain->getHeight(2, 14); // y
	firstSquare[counter++] = 0.5f + 1;  // z
	size += 3;
	numDrawCalls += 1;
	*/

	counter = 0;
	numDrawCalls = 0;
	size = 0;
	int move = 0;
	int scale = 5.0f;
	for (int j = 0; j < mapHeight - 1; j++)
	{
		for (int i = 0; i < mapWidth; i++ )
		{
			// top left
			firstSquare[counter++] = -0.5f + i;  // x
			firstSquare[counter++] = 0.5f + terrain->getHeight(j + 0, i) * scale;  // y
			firstSquare[counter++] = -0.5f + j;  // z


			// bottom left
			firstSquare[counter++] = -0.5f + i;  // x
			firstSquare[counter++] = 0.5f + terrain->getHeight(j + 1, i) * scale;  // y
			firstSquare[counter++] = 0.5f +j;  // z


			// Top right
			firstSquare[counter++] = 0.5f + i;  // x
			firstSquare[counter++] = 0.5f + terrain->getHeight(j + 0, i) * scale;  // y
			firstSquare[counter++] = -0.5f + j;  // z


			// bottom right
			firstSquare[counter++] = 0.5f + i;  // x
			firstSquare[counter++] = 0.5f + terrain->getHeight(j + 1, i) * scale;  // y
			firstSquare[counter++] = 0.5f + j;  // z



			numDrawCalls += 4;
			size += 12;
			move++;
		}

	}
	/*
	int j = 1;
	// Top right + 1
	firstSquare[counter++] = 0.5f + (move - 1);  // x
	firstSquare[counter++] = 0.5f + terrain->getHeight(0 + j, move - 1);  // y
	firstSquare[counter++] = -0.5f + 0;  // z */

	/*
	// bottom right
	firstSquare[counter++] = 0.5f + (move - 1);  // x
	firstSquare[counter++] = 0.5f + terrain->getHeight(1 + j, move - 1); // y
	firstSquare[counter++] = 0.5f + j;  // z */



	unsigned int VBO_map = 0;

	glGenVertexArrays(1, &VAO_map);
	glBindVertexArray(VAO_map);

	glGenBuffers(1, &VBO_map);

	glBindBuffer(GL_ARRAY_BUFFER, VAO_map);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstSquare), firstSquare, GL_STATIC_DRAW);
	std::cout << "size of f sq" << sizeof(firstSquare) << std::endl;

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

void Map::initMap()
{

}


void Map::renderOnScreen(Shader mapShader)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	model = glm::translate(model, glm::vec3(0, -10, 0));

	mapShader.use();
	mapShader.setMat4("model", model);

	glBindVertexArray(VAO_map);

	// GL_TRIANGLE_STIP
	glDrawArrays(GL_TRIANGLE_STRIP, 0, (4*14) * 13 );
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}
