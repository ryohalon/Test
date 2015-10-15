#pragma once
#include "../../singleton/appenv/sin_appenv.h"
#include "../../singleton/gamepad/sin_gamepad.h"



//****************************************************************
//ステージセレクト

class StageSelect
{
private:

	Texture world_image;

	int world_num;
	int stage_num;
	StageStatus stage_status[3][10];

	//マップアイコン
	struct Stage
	{
		Vec2i pos;
		int size;
	};
	Stage stage;

	//カーソル
	struct Cursol
	{
		Vec2i pos;
		int size;
	};
	Cursol cursol;

	void MoveCursol();

public:

	StageSelect();

	void SetWorldNum(int);
	void StageClear(StageStatus);
	int GetStageNum();
	StageStatus IsWorldClear();

	void UpDate();
	void Draw();
	SceneName Shift();

};