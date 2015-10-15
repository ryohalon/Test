#pragma once
#include "../../singleton/appenv/sin_appenv.h"
#include "../../singleton/gamepad/sin_gamepad.h"



//******************************************************************
//ワールドセレクト

class WorldSelect
{
private:

	Texture world_image;

	int world_num;

	StageStatus world_status[3];

	struct World
	{
		Vec2i pos;
		int size;
	};
	World world;

	struct Cursol
	{
		Vec2i pos;
		int size;
	};
	Cursol cursol;

	void MoveCursol();

public:

	WorldSelect();

	void SetWorldClear(StageStatus);
	int GetWorldNum();

	void UpDate();
	void Draw();
	SceneName Shift();

};