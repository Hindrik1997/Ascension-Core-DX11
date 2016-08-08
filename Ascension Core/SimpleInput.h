#pragma once

class SimpleInput
{
public:
	SimpleInput();
	~SimpleInput();

	void Initialize();

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);

	bool IsKeyDown(unsigned int);

private:
	bool m_keys[256];
};

