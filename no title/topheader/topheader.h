#pragma once
#include "../singleton/gamepad/sin_gamepad.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>

#define MAP_SIZE (64)

enum class SceneName
{
	TITLE,
	WORLDSELECT,
	STAGESELECT,
	GAMEMANAGER,
};

enum class StageStatus
{
	UNCLEAR,
	CLEAR,
	LOCKED,
};

enum class MapNum
{
	HEIGHTNUM = 16,
	WIDTHNUM = 32
};

enum class MapType
{
	NONE,
	FLOOR,
};

enum class CharaType
{
	NORMAL,
	FALL,
	THIN,
	SPRING,
};

enum class CollisionType
{
	TOP,
	LEFT,
	RIGHT,
	DOWN,
	NONE
};