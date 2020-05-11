#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
//#include "ConstructDraw.h"

#include "DrawTriangle.h"
#include "TextureTest1.h"
#include "AlphaToCoverage.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	DrawTriangle mTest1;

	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);	
		mTest1.SetShader0();
		mTest1.SetShader1();
		mTest1.SetContext();
		mTest1.SetDraw();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void ConstructUniform(GLuint shader)
{
	GLuint blockId, bufferId;
	GLint blockSize;
	GLuint bindingPoint = 1;
	GLfloat lightData[] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	blockId = glGetUniformBlockIndex(shader, "outColor");
	glUniformBlockBinding(shader, blockId, bindingPoint);
	glGetActiveUniformBlockiv(shader, blockId, GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize);

	glGenBuffers(1, &bufferId);
	glBindBuffer(GL_UNIFORM_BUFFER, bufferId);
	glBufferData(GL_UNIFORM_BUFFER, blockSize, lightData, GL_DYNAMIC_DRAW);

	//glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, buffer);
}
