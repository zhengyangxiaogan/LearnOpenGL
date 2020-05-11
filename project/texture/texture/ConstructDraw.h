#pragma once

#include <glad/glad.h>
#include <iostream>
#include "shader.h"
#include <glm/glm.hpp>

class ConstructDraw
{
public:
	ConstructDraw() = default;
	
	~ConstructDraw() = default;
	
	virtual void SetContext()
	{
	};

	virtual void SetDraw()
	{
	};
	
	virtual void SetShader()
	{
	};
};

