#pragma once

enum class GameState : unsigned char
{
	TITLE,
	PLAY,
	GAMEOVER,
	RESULT
};

enum class MoveObjState : unsigned char
{
	ON_THE_GROUND,
	CHECK_GROUND,
	JUMP,
	FALL
};

enum class Object : unsigned char
{
	MARIO,
	NORMAL_BLOCK,
	GROUND_BLOCK,
	GROUND_BLOCK_DUMMY,
	KURIBOU,
	NOKONOKO,
	SPACE,
	GOAL
};