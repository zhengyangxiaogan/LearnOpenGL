#pragma once
#include "ConstructDraw.h"

class TextureTest1 :
	public ConstructDraw
{
public:
	TextureTest1();
	~TextureTest1();
	void SetContext();
	void SetDraw();
	void SetShader();

public:
	unsigned int VBO, VAO, EBO;

	int shaderProgram;
	unsigned int texture;
};

