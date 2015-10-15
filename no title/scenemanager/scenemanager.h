#pragma once
#include "../singleton/gamepad/sin_gamepad.h"
#include "../scene/title/title.h"
#include "../scene/worldselect/worldselect.h"
#include "../scene/stageselect/stageselect.h"
#include "../scene/gamemanager/gamemanager.h"

//****************************************************************
//ÉVÅ[Éìä«óù
//****************************************************************

class SceneManager
{
private:

	Title title;
	WorldSelect worldselect;
	StageSelect stageselect;
	GameMain gamemain;

	SceneName scene_num = TITLE;

public:

	void UpDate();
	void Draw();
	void Shift();

};