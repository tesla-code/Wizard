#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

// my headers
#include "Texture.h"

// glm math library
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include "Terrain.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
int framebufferWidth = 0;
int framebufferHeight = 0;

void framebuffer_resize_callback(GLFWwindow* window, int fbw, int fbh)
{
	glViewport(0, 0, fbw, fbh);
}

bool loadShaders(GLuint& program)
{
	bool loadSuccess = true;
	char infoLog[512];
	GLint success;

	std::string temp = "";
	std::string src = "";

	std::ifstream in_file;

	// VERTEX
	in_file.open("shaders/vertex_core.glsl");

	if (in_file.is_open())
	{
		while(std::getline(in_file, temp))
		{
			src += temp + "\n";
		}
	}
	else
	{
		std::cout << "ERROR::LOADSHADER::COULD NOT OPEN  VERTEX FILE " << std::endl;
		loadSuccess = false;
	}
	
	in_file.close();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar* vertSrc = src.c_str();
	glShaderSource(vertexShader, 1, &vertSrc, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADER::COULT NOT COMPILE VERTEX SHADER" << std::endl;
		std::cout << infoLog << std::endl;
		loadSuccess = false;
	}

	temp = "";
	src = "";

	// FRAGMENT
	in_file.open("shaders/fragment_core.glsl");

	if (in_file.is_open())
	{
		while (std::getline(in_file, temp))
		{
			src += temp + "\n";
		}
	}
	else
	{
		std::cout << "ERROR::LOADSHADER:: COULT NOT OPEN FRAGMENT SHADER" << std::endl;
		loadSuccess = false;
	}

	in_file.close();

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* fragSrc = src.c_str();
	glShaderSource(fragmentShader, 1, &fragSrc, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADERS::COULD NOT COMPILE FRAGMENT SHADER" << std::endl;
		std::cout << infoLog << std::endl;
		loadSuccess = false;
	}

	// PROGRAM
	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::LOADSHADERS::COULD_NOT_LINK_PROGRAM" << std::endl;
		std::cout << infoLog << std::endl;
		loadSuccess = false;
	}

	// END
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return loadSuccess;
}

void updateInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

struct  Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texcoord;
};

Vertex vertices[] =
{
	// Position						// color						// Texcoords
	glm::vec3(-0.5f, 0.5f, 0.f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),
	glm::vec3(-0.5f, -0.5f, 0.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),
	glm::vec3(0.5f, -0.5f, 0.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),
	glm::vec3(0.5f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f)

};

unsigned int numberOfVertices = sizeof(vertices) / sizeof(Vertex);

GLuint indices[] =
{
	0, 1, 2,	//Triangle 1
	0, 2, 3		//Triangle 2
};
unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);


int main()
{
	// INIT GLFW
	glfwInit();

	// CREATE WINDOW
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Lovecraftian", NULL, NULL);

	// glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
	// glViewport(0, 0, framebufferWidth, framebufferHeight);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback); // when window is resized this will be called

	glfwMakeContextCurrent(window);

	// INIT GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR::MAIN.CPP::GLEW_INIT_FAILED" << std::endl;
		glfwTerminate();
	}

	// OPENGL OPTIONS
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// SHADER INIT
	GLuint core_program;
	if (!loadShaders(core_program))
	{
		glfwTerminate();
	}
	
	// MODEL

	// VAO, VBO, EBO  we need buffers to hold our data, openGL has a lot of different buffer types
	// GEN VAO AND BIND
	GLuint vao;
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);	// any thing we do now with any other buffers will bind to this vao

	// GEN VBO AND BIND AND SEND DATA
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // send data to gpu

	// GEN EBO AND BIND AND SEND DATA
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// SET VERTEXATTRIBPOINTERS AND ENABLE
	// Position attribute
	glVertexAttribPointer(
		0, // attrib 0 
		3, // 3 positions
		GL_FLOAT, // type  float
		GL_FALSE, // normalize? 
		sizeof(Vertex), // stride 
		(GLvoid*)offsetof(Vertex, position) // memory to next attrib
	); // Position
	glEnableVertexAttribArray(0); // effects our currently bound vao

	// Color attribute
	glVertexAttribPointer(
		1, // attrib 1 
		3, // 3 positions
		GL_FLOAT, // type  float
		GL_FALSE, // normalize? 
		sizeof(Vertex), // stride 
		(GLvoid*)offsetof(Vertex, color) // memory to next attrib
	); // Position
	glEnableVertexAttribArray(1); // effects our currently bound vao

	// Texcoord
	glVertexAttribPointer(
		2,				// attrib 2
		2,				// 3 positions
		GL_FLOAT,		// type  float
		GL_FALSE,		// normalize? 
		sizeof(Vertex), // stride 
		(GLvoid*)offsetof(Vertex, texcoord) // memory to next attrib
	); // Position
	glEnableVertexAttribArray(2); // effects our currently bound vao

	// BIND VAO 0
	glBindVertexArray(0);


	Texture texture0("res/images/cat.png", png);
	Texture texture1("res/images/box.png", png);

	
	// Matrix Movement, Rotation, Scaling
	glm::mat4 Modelmatrix(1.f);
	Modelmatrix = glm::translate(Modelmatrix, glm::vec3(0.f, 0.f, 0.f));								
	Modelmatrix = glm::rotate(Modelmatrix,    glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f)); // x axis to rotate
	Modelmatrix = glm::rotate(Modelmatrix,	  glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f)); // y axis to rotate
	Modelmatrix = glm::rotate(Modelmatrix,	  glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f)); // z axis to rotate
	Modelmatrix = glm::scale(Modelmatrix,	  glm::vec3(1.f)); 

	glUseProgram(core_program); // we wanna send this in every time

	// Update uniforms
	glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE,
		glm::value_ptr(Modelmatrix));

	glUseProgram(0);

	// Load Height Map
	Terrain heightMap;
	heightMap.loadHeightMap("res/map/map1.png", png);
	// heightMap.loadHeightMap("res/map/model2-low.png", png);
	heightMap.renderMap();

	// MAIN LOOP
	while (!glfwWindowShouldClose(window))
	{
		// UPDATE INPUT
		glfwPollEvents();

		updateInput(window);

		// UPDATE

		// DRAW
		// Clear
		glClearColor(0.5f, 0.5f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		
		// use program
		glUseProgram(core_program);

		// update uniforms
		glUniform1i(glGetUniformLocation(core_program, "texture0"), 0);
		glUniform1i(glGetUniformLocation(core_program, "texture1"), 1);

		// Move, Rotate and Scale
		Modelmatrix = glm::translate(Modelmatrix, glm::vec3(0.f, 0.f, 0.f));
		Modelmatrix = glm::rotate(Modelmatrix, glm::radians(0.f), glm::vec3(1.f, 0.f, 0.f)); // x axis to rotate
		Modelmatrix = glm::rotate(Modelmatrix, glm::radians(0.f), glm::vec3(0.f, 1.f, 0.f)); // y axis to rotate
		Modelmatrix = glm::rotate(Modelmatrix, glm::radians(0.f), glm::vec3(0.f, 0.f, 1.f)); // z axis to rotate
		Modelmatrix = glm::scale(Modelmatrix, glm::vec3(1.f));

		glUniformMatrix4fv(glGetUniformLocation(core_program, "ModelMatrix"), 1, GL_FALSE, glm::value_ptr(Modelmatrix));

		// Activate Texture
		glActiveTexture(GL_TEXTURE0);
		texture0.bind(); // instead of  glBindTexture(GL_TEXTURE_2D, texture0);
		
		//heightMap.bind();

		glActiveTexture(GL_TEXTURE1);
		texture1.bind();


		// bind vertex array object
		glBindVertexArray(vao);

		// Draw
		//glDrawArrays(GL_TRIANGLES, 0, numberOfVertices);
		glDrawElements(GL_TRIANGLES, nrOfIndices, GL_UNSIGNED_INT, 0);

		// end draw
		glfwSwapBuffers(window);

		glBindVertexArray(0);
		glUseProgram(0);
		glActiveTexture(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// END OF PROGRAM
	glfwDestroyWindow(window);
	glfwTerminate();

	// DELETE PROGRAM
	glDeleteProgram(core_program);

	// DELETE VAO and BUFFERS (VBO's ETC)

	return 0;
}