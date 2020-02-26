#pragma once
#include "ConstructDraw.h"
class Lighting :
	public ConstructDraw
{
public:
	Lighting();
	~Lighting();
	void SetContext();
	void SetDraw();
	void SetShader();

private:
	unsigned int VBO, VAO, EBO;

	int shaderProgram;
};

