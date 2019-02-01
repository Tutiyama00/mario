#pragma once

enum class InputFlagCode :unsigned char
{
	INPUT_ERRER = 1,
	INPUT_SPACE = 2,
	INPUT_LEFT  = 4,
	INPUT_RIGHT = 8,
	INPUT_SHIFT = 16
};

class InputFlag
{
public:
	InputFlag();
	~InputFlag();

	bool Check(InputFlagCode);
	void Set(InputFlagCode);
	void ReSet(InputFlagCode);
	void AllReSet();

private:
	unsigned char mFlags;
};