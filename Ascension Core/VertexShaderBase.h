#pragma once
#include "ShaderBase.h"

class VertexShaderBase : public ShaderBase
{
public:
	VertexShaderBase();
	virtual ~VertexShaderBase() = 0;
	virtual void Set() = 0;
};

