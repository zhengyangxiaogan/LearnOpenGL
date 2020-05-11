#pragma once
#include "ConstructDraw.h"
class AlphaToCoverage :
	public ConstructDraw
{
public:
	AlphaToCoverage();
	~AlphaToCoverage();
	void SetContext();
	void SetDraw();
	void SetShader();

public:
	unsigned int VBO, VAO, EBO;

	int shaderProgram;
	Shader outShader;
};

