#include "AlphaToCoverage.h"

AlphaToCoverage::AlphaToCoverage()
{

}

AlphaToCoverage::~AlphaToCoverage()
{
	// optional: de-allocate all resources once they've outlived their purpose:
// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void AlphaToCoverage::SetShader()
{
	Shader outShader("a2c.vs", "a2c.fs");
	outShader.use();
}

void AlphaToCoverage::SetContext()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f,  0.5f, 0.0f,  // bottom right
		 0.5f,  0.5f, 0.0f,  // bottom left

		 -0.5f,  -0.5f, 0.0f,  // top left 
		 -0.5f,  0.0f, 0.0f,
		 0.0f, -0.5f, 0.0f
	};
	unsigned int indices[] = {  // note that we start from 0!
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void AlphaToCoverage::SetDraw()
{
	// render
// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
