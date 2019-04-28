#pragma once
#include <glad/glad.h>
#include <iostream>
class DrawTexture 
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

