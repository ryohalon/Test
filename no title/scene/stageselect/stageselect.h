#pragma once
#include "../../topheader/topheader.h"
#include "../../object/object.h"

#define STAGE_START_POSITION Vec2i(-600, -50)
#define STAGE_SIZE (200)

class StageSelect
{
private:

	Texture world_image;

	int world_num;
	int stage_num;
	StageStatus stage_status[3][10];

	//マップアイコン
	Object stage_icon = Object(STAGE_START_POSITION, STAGE_SIZE);
	//カーソル
	Object cursol = Object(STAGE_START_POSITION, STAGE_SIZE);

	void MoveCursol();

public:

	StageSelect();

	void SetWorldNum(int);
	void IsStageClear(StageStatus);
	void UnlockedNextStage();
	int GetStageNum();
	StageStatus* GetStageStatus();
	StageStatus IsWorldClear();

	void UpDate();
	void Draw();
	SceneName Shift();

};