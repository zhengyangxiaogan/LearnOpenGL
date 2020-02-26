#include "DrawTriangle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos, 1.0);\n"
		"   ourColor = aColor;\n"
		"}\0";
	const char *fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = ourColor;\n"
		"}\n\0";

	// build and compile our shader program
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
	shaderProgram1 = Shader("triangle.vs", "triangle.fs").ID;
}



void DrawTriangle::SetContext()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
	float vertices[] = {
		 0.0f,  0.5f, 1.0f,  1.0f, 0.0f, 0.0f,1.0f,//Red
		-0.5f, -0.5f, 1.0f,  1.0f, 0.0f, 0.0f,1.0f,
		0.5f,  -0.5f, 1.0f,  1.0f, 0.0f, 0.0f,1.0f,
											  
		-0.5f,  0.5f, 1.0f,  0.0f, 1.0f, 0.0f,1.0f,//Green
		 0.5f,  0.5f, 1.0f,	 0.0f, 1.0f, 0.0f,1.0f,
		 0.0f, -0.5f, 1.0f,	 0.0f, 1.0f, 0.0f,1.0f,
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
}

void DrawTriangle::SetDraw()
{
	// render
// ------
	glClearColor(0.0, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shaderProgram0);
	glDepthRange(0.6, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDepthRange(1.0f, 0.0f);
	glUseProgram(shaderProgram1);
	//glEnable(GL_POLYGON_OFFSET_FILL);
	//glPolygonOffset(0, 1);
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_EQUAL);
	//glDepthFunc(GL_LESS);
	glDrawArrays(GL_TRIANGLES, 3, 3);
}