#pragma once

enum class GameState : unsigned char
{
	TITLE,
	PLAY,
};

enum class PlayerState : unsigned char
{
	ON_THE_GROUND,
	CHECK_GROUND,
	JUMP,
	FALL,
	DEATH,
};

enum class Object : unsigned char
{
	MARIO,
	NORMAL_BLOCK,
	KURIBOU,
	SPACE
};