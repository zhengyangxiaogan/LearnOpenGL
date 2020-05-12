#include "DrawTriangle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

DrawTriangle::DrawTriangle()
{

}

DrawTriangle::~DrawTriangle()
{
	// optional: de-allocate all resources once they've outlived their purpose:
// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void DrawTriangle::SetShader0()
{
	const char *vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec4 aColor;\n"
		"out vec4 ourColor;\n"
		"uniform mat4 trans;\n"
		"void main()\n"
		"{\n"
		"   gl_Position =  trans * vec4(aPos, 1.0);\n"
		"   ourColor = aColor;\n"
		"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = ourColor;\n"
		"}\n\0";

// ------------------------------------
// vertex shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// fragment shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// link shaders
	shaderProgram0 = glCreateProgram();
	glAttachShader(shaderProgram0, vertexShader);
	glAttachShader(shaderProgram0, fragmentShader);
	glLinkProgram(shaderProgram0);
	// check for linking errors
	glGetProgramiv(shaderProgram0, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram0, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void DrawTriangle::SetShader1()
{
	//ourShader.SetShader("triangle.vs", "triangle.fs");
}


void DrawTriangle::SetContext()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
	float vertices[] = {
		 0.0f,  0.5f, 0.5f,  1.0f, 0.0f, 0.0f,1.0f,//Red
		-0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,1.0f,
		0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,1.0f,
					  
		-0.5f,  0.5f, 0.5f,  0.0f, 1.0f, 0.0f,1.0f,//Green
		 0.5f,  0.5f, 0.5f,	 0.0f, 1.0f, 0.0f,1.0f,
		 0.0f, -0.5f, 0.5f,	 0.0f, 1.0f, 0.0f,1.0f,
	};
	unsigned short indices[] = {  // note that we start from 0!
		0, 1, 2,  // first Triangle
		3, 4, 5   // second Triangle
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	const float radius = 10.0f;
	float camX = sin(glfwGetTime()) * radius;
	float camZ = cos(glfwGetTime()) * radius;
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	view = { 0.0, 0.0, 0.0, 1.0,  0.0, 0.0, 0.0, 2.0,  0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };
	//ourShader.setMat4("viewMatrix", view);
}

void DrawTriangle::SetDraw()
{
	glm::mat4 trans = glm::mat4(1.0f);
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	trans = glm::scale(trans, glm::vec3(2.0, 2.0, 0.0));
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
	ourShader.setMat4("transMatrix", trans);
	ourShader.SetShader("triangle.vs", "triangle.fs");

	unsigned int transformLoc = glGetUniformLocation(shaderProgram0, "trans");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	//unsigned int transformLoc = glGetUniformLocation(ourShader.getID(), "trans");
	//unsigned int transformLoc = glGetUniformLocation(shaderProgram0, "trans");
	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	glClearColor(0.0, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgram0);

	//glDepthRange(0.0, 1.0f);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LEQUAL);
	glBindVertexArray(VAO);
	//glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//glDepthRange(0.0f, 1.0f);
	//ourShader.use();
	//glDrawArrays(GL_TRIANGLES, 3, 3);
}