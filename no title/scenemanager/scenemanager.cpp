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

	case SceneName::GAMEMAIN:
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

	case SceneName::GAMEMAIN:
		gamemain.Draw();
		break;
	}
}

void SceneManager::Shift()
{
	switch (scene_num)
	{
	case SceneName::TITLE:
		if (env.isPushKey(GLFW_KEY_ENTER))
			scene_num = title.Shift();
		break;

	case WORLDSELECT:
		if (env.isPushKey(GLFW_KEY_ENTER) || env.isPushKey(GLFW_KEY_SPACE))
		{
			scene_num = worldselect.Shift();

			stageselect.SetWorldNum(worldselect.GetWorldNum());
		}
			
		break;

	case SceneName::STAGESELECT:
		if (env.isPushKey(GLFW_KEY_ENTER) || env.isPushKey(GLFW_KEY_SPACE))
		{
			scene_num = stageselect.Shift();

			gamemain.SetWorldNum(worldselect.GetWorldNum());
			gamemain.SetStageNum(stageselect.GetStageNum());

			worldselect.SetWorldClear(stageselect.IsWorldClear());
		}
		break;

	case SceneName::GAMEMAIN:
		if (env.isPushKey(GLFW_KEY_ENTER))
		{
			scene_num = gamemain.Shift();

			stageselect.StageClear(gamemain.GetStageStatus());
		}
		break;
	}
}