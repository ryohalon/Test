#pragma once
#include "../../map/map.h"



//****************************************************************
//ƒQ[ƒ€ƒƒCƒ“

class GameMain
{
private:

	int world_num;
	int stage_num;



public:

	GameMain();

	void SetWorldNum(int);
	void SetStageNum(int);
	StageStatus GetStageStatus();

	void UpDate();
	void Draw();
	SceneName Shift();

};