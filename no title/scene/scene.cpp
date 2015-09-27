#include "scene.h"

//タイトル
void Title::UpDate()
{

}

void Title::Draw()
{
	drawFillBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, Color::white);
}

SceneName Title::Shift()
{
	return SceneName::WORLDSELECT;
}


//ワールドセレクト
void WorldSelect::UpDate()
{

}

int WorldSelect::GetterWorld()
{
	return world_num;
}

void WorldSelect::Draw()
{
	drawFillBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, Color::green);
}

SceneName WorldSelect::Shift()
{
	if (env.isPushKey(GLFW_KEY_SPACE))
		return TITLE;
	if (env.isPushKey(GLFW_KEY_ENTER))
		return STAGESELECT;

	return WORLDSELECT;
}


//ステージセレクト

//コンストラクタ
StageSelect::StageSelect()
{
	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 5; k++)
		{
			stagestatus[i][k] = StageStatus::UNCLEAR;
		}
	}

	stage.pos = Vec2f(-600, -50);
	stage.size = 200;
}

void StageSelect::UpDate()
{

}

int StageSelect::GetterStage()
{
	return stage_num;
}

void StageSelect::Draw()
{
	drawFillBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, Color::blue);

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 5; k++)
		{
			switch (stagestatus[i][k])
			{
			case StageStatus:: UNCLEAR:
				drawFillBox(stage.pos.x() + 250 * k, stage.pos.y() - 250 * i, stage.size, stage.size, Color::yellow);
	
				break;

			case StageStatus::CLEAR:
				drawFillBox(stage.pos.x() + 250 * k, stage.pos.y() - 250 * i, stage.size, stage.size, Color::cyan);
				break;
			}
		}
	}
}

SceneName StageSelect::Shift()
{
	if (env.isPushKey(GLFW_KEY_SPACE))
		return WORLDSELECT;
	if (env.isPushKey(GLFW_KEY_ENTER))
		return GAMEMAIN;

	return WORLDSELECT;
}


//ゲームメイン
void GameMain::UpDate()
{

}

void GameMain::Draw()
{
	drawFillBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, Color::red);
}

SceneName GameMain::Shift()
{
	return SceneName::STAGESELECT;
}
