#pragma once
#include <glad/glad.h>
#include <iostream>
#include "ConstructDraw.h"

class DrawTexture :public ConstructDraw
{
public:
	DrawTexture();
	~DrawTexture();
	void SetContext();
	void SetDraw();
	void SetShader();

public:
	unsigned int VBO, VAO, EBO;

	int shaderProgram;
};

