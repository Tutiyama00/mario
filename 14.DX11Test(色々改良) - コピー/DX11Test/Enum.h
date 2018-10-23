#pragma once

enum class GameState : unsigned char
{
	TITLE,
	PLAY,
	GAMEOVER,
	GAMECLEAR
};

enum class MoveObjState : unsigned char
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