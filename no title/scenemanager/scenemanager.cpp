#include "scenemanager.h"

void SceneManager::UpDate()
{
	switch (scene_num)
	{
	case SceneName::TITLE:
		title.UpDate();
		break;

	case WORLDSELECT:
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

	case WORLDSELECT:
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

	case WORLDSELECT:
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

			worldselect.SetWorldClear(stageselect.IsWorldClear());
		}
		break;

	case SceneName::GAMEMANAGER:
		if (Pad::Get().isPushButton(2))
		{
			scene_num = gamemain.Shift();

			stageselect.StageClear(gamemain.GetStageStatus());
		}
		break;
	}
}