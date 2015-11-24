#pragma once
#include "../../topheader/topheader.h"
#include "../../object/object.h"

#define WORLD_START_POSITION Vec2i(-200, -280)
#define WORLD_SIZE (400)

class WorldSelect
{
private:

	Texture world_image;

	int world_num;

	StageStatus world_status[3];

	//ワールドアイコン
	Object world = Object(WORLD_START_POSITION, WORLD_SIZE);
	//カーソル
	Object cursol = Object(WORLD_START_POSITION, WORLD_SIZE);

	void MoveCursol();

public:

	WorldSelect();

	void IsWorldClear(StageStatus);
	void UnlockedNextWorld();
	int GetWorldNum();

	void UpDate();
	void Draw();
	SceneName Shift();

};