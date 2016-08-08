#pragma once
class ShaderBase
{
public:
	ShaderBase();
	virtual ~ShaderBase() = 0;

	virtual void Set() = 0;
};

