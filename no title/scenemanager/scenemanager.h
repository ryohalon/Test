#pragma once
#include "../topheader/topheader.h"
#include "../savedata/savedata.h"
#include "../scene/title/title.h"
#include "../scene/worldselect/worldselect.h"
#include "../scene/stageselect/stageselect.h"
#include "../scene/gamemanager/gamemanager.h"



class SceneManager
{
private:

	Title title;
	WorldSelect worldselect;
	StageSelect stageselect;
	GameMain gamemain;
	SaveData savedata;

	SceneName scene_num = SceneName::TITLE;

public:

	SceneManager();
	~SceneManager();

	void MainLoop();

	void UpDate();
	void Draw();
	void Shift();

};