#include "scenemanager.h"

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
	
}

void SceneManager::MainLoop()
{
	while (App::Get().isOpen())
	{
		UpDate();

		Shift();

		App::Get().begin();

		Draw();

		App::Get().end();

	}
}

void SceneManager::UpDate()
{
	switch (scene_num)
	{
	case SceneName::TITLE:
		title.UpDate();
		break;

	case SceneName::WORLDSELECT:
		worldselect.UpDate();
		break;

	case SceneName::STAGESELECT:
		stageselect.UpDate();
		break;

	case SceneName::GAMEMANAGER:
		gamemain.UpDate();
		break;
	}
}

void SceneManager::Draw()
{
	switch (scene_num)
	{
	case SceneName::TITLE:
		title.Draw();
		break;

	case SceneName::WORLDSELECT:
		worldselect.Draw();
		break;

	case SceneName::STAGESELECT:
		stageselect.Draw();
		break;

	case SceneName::GAMEMANAGER:
		gamemain.Draw();
		break;
	}
}

void SceneManager::Shift()
{
	switch (scene_num)
	{
	case SceneName::TITLE:
		if (Pad::Get().isPushButton(2))
			scene_num = title.Shift();

		if (Pad::Get().isPushButton(9))
			exit(0);
		break;

	case SceneName::WORLDSELECT:
		if (Pad::Get().isPushButton(2) || Pad::Get().isPushButton(1))
		{
			scene_num = worldselect.Shift();

			stageselect.SetWorldNum(worldselect.GetWorldNum());
		}
			
		break;

	case SceneName::STAGESELECT:
		if (Pad::Get().isPushButton(2) || Pad::Get().isPushButton(1))
		{
			scene_num = stageselect.Shift();

			gamemain.SetWorldNum(worldselect.GetWorldNum());
			gamemain.SetStageNum(stageselect.GetStageNum());

			worldselect.IsWorldClear(stageselect.IsWorldClear());
		}
		break;

	case SceneName::GAMEMANAGER:
		if (Pad::Get().isPushButton(2)) /*|| Pad::Get().isPushButton(1))*/
		{
			scene_num = gamemain.Shift();

			stageselect.IsStageClear(gamemain.GetStageStatus());

			savedata.SaveStageData(worldselect.GetWorldNum(), stageselect.GetStageStatus());
		}
		break;
	}
}