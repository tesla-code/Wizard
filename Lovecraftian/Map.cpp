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


			if (terrain->getHeight(j + 0, i) < 0.35f)
			{
				// Colors (Blue)
				firstSquare[counter++] = 0.0f;
				firstSquare[counter++] = 0.0f;
				firstSquare[counter++] = 1.0f;
			}
			else if (terrain->getHeight(j + 0, i) < 0.50f)
			{
				// Colors (dark green)     // 0.5 1.0 0.5 light green
				firstSquare[counter++] = 0.0f;
				firstSquare[counter++] = 0.5f;
				firstSquare[counter++] = 0.0f;
			}
			else // white
			{
				firstSquare[counter++] = 1.0f;
				firstSquare[counter++] = 1.0f;
				firstSquare[counter++] = 1.0f;
			}
	


			// bottom left
			firstSquare[counter++] = -0.5f + i;  // x
			firstSquare[counter++] = 0.5f + terrain->getHeight(j + 1, i) * scale;  // y
			firstSquare[counter++] = 0.5f +j;  // z

			if (terrain->getHeight(j + 0, i) < 0.35f)
			{
				// Colors (Blue)
				firstSquare[counter++] = 0.0f;
				firstSquare[counter++] = 0.0f;
				firstSquare[counter++] = 1.0f;
			}
			else if (terrain->getHeight(j + 0, i) < 0.50f)
			{
				// Colors (dark green)     // 0.5 1.0 0.5 light green
				firstSquare[counter++] = 0.0f;
				firstSquare[counter++] = 0.5f;
				firstSquare[counter++] = 0.0f;
			}
			else // white
			{
				firstSquare[counter++] = 1.0f;
				firstSquare[counter++] = 1.0f;
				firstSquare[counter++] = 1.0f;
			}

			// Top right
			firstSquare[counter++] = 0.5f + i;  // x
			firstSquare[counter++] = 0.5f + terrain->getHeight(j + 0, i) * scale;  // y
			firstSquare[counter++] = -0.5f + j;  // z

			if (terrain->getHeight(j + 0, i) < 0.35f)
			{
				// Colors (Blue)
				firstSquare[counter++] = 0.0f;
				firstSquare[counter++] = 0.0f;
				firstSquare[counter++] = 1.0f;
			}
			else if (terrain->getHeight(j + 0, i) < 0.50f)
			{
				// Colors (dark green)     // 0.5 1.0 0.5 light green
				firstSquare[counter++] = 0.0f;
				firstSquare[counter++] = 0.5f;
				firstSquare[counter++] = 0.0f;
			}
			else // white
			{
				firstSquare[counter++] = 1.0f;
				firstSquare[counter++] = 1.0f;
				firstSquare[counter++] = 1.0f;
			}

			// bottom right
			firstSquare[counter++] = 0.5f + i;  // x
			firstSquare[counter++] = 0.5f + terrain->getHeight(j + 1, i) * scale;  // y
			firstSquare[counter++] = 0.5f + j;  // z

			if (terrain->getHeight(j + 0, i) < 0.35f)
			{
				// Colors (Blue)
				firstSquare[counter++] = 0.0f;
				firstSquare[counter++] = 0.0f;
				firstSquare[counter++] = 1.0f;
			}
			else if (terrain->getHeight(j + 0, i) < 0.50f)
			{
				// Colors (dark green)     // 0.5 1.0 0.5 light green
				firstSquare[counter++] = 0.0f;
				firstSquare[counter++] = 0.5f;
				firstSquare[counter++] = 0.0f;
			}
			else // white
			{
				firstSquare[counter++] = 1.0f;
				firstSquare[counter++] = 1.0f;
				firstSquare[counter++] = 1.0f;
			}
			numDrawCalls += 4;
			size += 12;
			move++;
		}

	}


	unsigned int VBO_map = 0;

	glGenVertexArrays(1, &VAO_map);
	glBindVertexArray(VAO_map);

	glGenBuffers(1, &VBO_map);

	glBindBuffer(GL_ARRAY_BUFFER, VAO_map);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstSquare), firstSquare, GL_STATIC_DRAW);
	std::cout << "size of f sq" << sizeof(firstSquare) << std::endl;

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

}

void Map::initMap()
{

}


void Map::renderOnScreen(Shader mapShader)
{

	glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
	model = glm::translate(model, glm::vec3(0, -10, 0));

	mapShader.use();
	mapShader.setMat4("model", model);

	glBindVertexArray(VAO_map);

	// GL_TRIANGLE_STIP
	glDrawArrays(GL_TRIANGLE_STRIP_ADJACENCY, 0, (4*14) * 13 );
	

}
