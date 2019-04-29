#pragma once

#include <glad/glad.h>
#include <iostream>

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

