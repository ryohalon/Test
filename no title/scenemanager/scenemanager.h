#pragma once
#include "../scene/scene.h"

//****************************************************************
//�V�[���Ǘ�
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