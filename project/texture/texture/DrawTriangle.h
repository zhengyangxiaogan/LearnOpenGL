#pragma once
#include <glad/glad.h>
#include <iostream>
#include "ConstructDraw.h"

class DrawTriangle :public ConstructDraw
{
public:
	DrawTriangle();
	~DrawTriangle();
	void SetContext();
	void SetDraw();
	void SetShader0();
	void SetShader1();

public:
	unsigned int VBO, VAO, EBO;

	int shaderProgram0;
	int shaderProgram1;
	Shader ourShader;
};

