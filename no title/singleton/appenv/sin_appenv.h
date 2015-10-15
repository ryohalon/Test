#pragma once
#include "../../lib/framework.hpp"

#define WIN_WIDTH (2048)
#define WIN_HEIGHT (1024)

class App
{
private:

public:

	static AppEnv& Get()
	{
		static AppEnv env(WIN_WIDTH, WIN_HEIGHT, false, true);

		return env;
	}
};



enum SceneName
{
	TITLE,
	WORLDSELECT,
	STAGESELECT,
	GAMEMANAGER,
};

enum StageStatus
{
	UNCLEAR,
	CLEAR,
};

enum MapNum
{
	HEIGHTNUM = 32,
	WIDTHNUM = 64
};

#define MAP_SIZE (64)