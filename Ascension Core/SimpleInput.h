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

	float ChangeHorizontal = 0.0f;
	float ChangeVertical = 0.0f;

private:
	bool m_keys[256];
};

