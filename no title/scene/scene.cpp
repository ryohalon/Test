#include "scene.h"

//***************************************************************
//�^�C�g��

//private

//�����x�̕ύX
float Title::ChangeAlpha()
{
	alpha_count += 25.0f;

	return ((std::sin(alpha_count) + 1.0f) * 0.9f);
}

//public

//�R���X�g���N�^
Title::Title()
{
	title = Texture("res/image/title.png");
	press_start = Texture("res/image/press_start.png");

	alpha = 1.0f;
	alpha_count = 0.0f;
}

void Title::UpDate()
{
	alpha = ChangeAlpha();
}

void Title::Draw()
{
	//�w�i
	drawFillBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, Color::white);

	//�^�C�g��
	drawTextureBox(-500, 200, 1000, 250, 0, 0, 512, 128, title);

	//Press Start
	drawTextureBox(-256, -200, 512, 128, 0, 0, 256, 64, press_start, Color(0, 0, 0, alpha));
}

SceneName Title::Shift()
{
	return SceneName::WORLDSELECT;
}


//***************************************************************
//���[���h�Z���N�g

//private
void WorldSelect::MoveCursol()
{
	if (world_num > -1 && world_num < 2)
	{
		if (env.isPushKey(GLFW_KEY_RIGHT))
		{
			world.pos.x() -= 550;

			world_num++;
		}
	}

	if (world_num > 0 && world_num < 3)
	{
		if (env.isPushKey(GLFW_KEY_LEFT))
		{
			world.pos.x() += 550;

			world_num--;
		}
	}

}


//public

//�R���X�g���N�^
WorldSelect::WorldSelect()
{
	world_image = Texture("res/image/world.png");

	world_num = 0;

	for (int i = 0; i < 3; i++)
	{
		world_status[i] = StageStatus::UNCLEAR;
	}

	world.pos = Vec2i(-200, -250);
	world.size = 400;

	cursol.pos = Vec2i(-200, -250);
	cursol.size = 400;
}

void WorldSelect::SetWorldClear(StageStatus status)
{
	world_status[world_num] = status;
}

int WorldSelect::GetWorldNum()
{
	return world_num;
}

void WorldSelect::UpDate()
{
	MoveCursol();
}

void WorldSelect::Draw()
{
	//�w�i
	drawFillBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, Color::green);

	//���[���h�@���S
	drawTextureBox(-250, 300, 500, 150, 0, 0, 256, 64, world_image);

	//���[���h�A�C�R��
	for (int i = 0; i < 3; i++)
	{
		switch (world_status[i])
		{
		case StageStatus::UNCLEAR:
			drawFillBox(world.pos.x() + 550 * i, world.pos.y(), world.size, world.size, Color::yellow);

			break;

		case StageStatus::CLEAR:
			drawFillBox(world.pos.x() + 550 * i, world.pos.y(), world.size, world.size, Color::cyan);
			break;
		}
	}

	//�J�[�\��
	drawBox(cursol.pos.x(), cursol.pos.y(), cursol.size, cursol.size, 10, Color::magenta);
}

SceneName WorldSelect::Shift()
{
	if (env.isPushKey(GLFW_KEY_SPACE))
		return TITLE;
	if (env.isPushKey(GLFW_KEY_ENTER))
	{
		GetWorldNum();

		return STAGESELECT;
	}

	return WORLDSELECT;
}


//***************************************************************
//�X�e�[�W�Z���N�g

//private
void StageSelect::MoveCursol()
{
	//���ړ�
	if (stage_num > -1 && stage_num < 9)
	{
		if (env.isPushKey(GLFW_KEY_RIGHT))
		{
			if (stage_num != 4)
			{
				cursol.pos.x() += 250;

				stage_num++;
			}
			else
			{
				cursol.pos = Vec2i(-600, -300);

				stage_num++;
			}
		}
	}

	//�E�ړ�
	if (stage_num > 0 && stage_num < 10)
	{
		if (env.isPushKey(GLFW_KEY_LEFT))
		{
			if (stage_num != 5)
			{
				cursol.pos.x() -= 250;

				stage_num--;
			}
			else
			{
				cursol.pos = Vec2i(400, -50);

				stage_num--;
			}
		}
	}

	//���ړ�
	if (stage_num > -1 && stage_num < 5)
	{
		if (env.isPushKey(GLFW_KEY_DOWN))
		{
			cursol.pos.y() -= 250;

			stage_num += 5;
		}
	}

	//��ړ�
	if (stage_num > 4 && stage_num < 10)
	{
		if (env.isPushKey(GLFW_KEY_UP))
		{
			cursol.pos.y() += 250;

			stage_num -= 5;
		}
	}
}


//public

//�R���X�g���N�^
StageSelect::StageSelect()
{
	world_image = Texture("res/image/world1.png");

	world_num = 0;
	stage_num = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			stage_status[i][k] = StageStatus::UNCLEAR;
		}
	}

	stage.pos = Vec2i(-600, -50);
	stage.size = 200;

	cursol.pos = Vec2i(-600, -50);
	cursol.size = 200;
}

void StageSelect::SetWorldNum(int num)
{
	world_num = num;
}

void StageSelect::StageClear(StageStatus status)
{
	stage_status[world_num][stage_num] = status;
}

int StageSelect::GetStageNum()
{
	return stage_num;
}

StageStatus StageSelect::IsWorldClear()
{
	if (stage_status[world_num][9] == StageStatus::CLEAR)
		return StageStatus::CLEAR;
	else
		return StageStatus::UNCLEAR;
}

void StageSelect::UpDate()
{
	MoveCursol();
}

void StageSelect::Draw()
{
	//�w�i
	drawFillBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, Color::blue);

	//���[���h�@���S
	drawTextureBox(-250, 300, 500, 150, 0, 0, 256, 64, world_image);

	//�X�e�[�W�A�C�R��
	for (int k = 0; k < 10; k++)
	{
		switch (stage_status[world_num][k])
		{
		case StageStatus::UNCLEAR:
			drawFillBox(stage.pos.x() + 250 * (k % 5), stage.pos.y() - 250 * (k / 5 % 10), stage.size, stage.size, Color::yellow);
			break;

		case StageStatus::CLEAR:
			drawFillBox(stage.pos.x() + 250 * (k % 5), stage.pos.y() - 250 * (k / 5 % 10), stage.size, stage.size, Color::cyan);
			break;
		}
	}

	//�J�[�\��
	drawBox(cursol.pos.x(), cursol.pos.y(), cursol.size, cursol.size, 10, Color::magenta);
}

SceneName StageSelect::Shift()
{
	if (env.isPushKey(GLFW_KEY_SPACE))
		return WORLDSELECT;
	if (env.isPushKey(GLFW_KEY_ENTER))
		return GAMEMAIN;

	return WORLDSELECT;
}


//***************************************************************
//�Q�[�����C��

//private


//public

//�R���X�g���N�^
GameMain::GameMain()
{

}

void GameMain::SetWorldNum(int num)
{
	world_num = num;
}

void GameMain::SetStageNum(int num)
{
	stage_num = num;
}

StageStatus GameMain::GetStageStatus()
{
	return StageStatus::CLEAR;
}

void GameMain::UpDate()
{

}

void GameMain::Draw()
{
	//�w�i
	drawFillBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, Color::red);
}

SceneName GameMain::Shift()
{
	return SceneName::STAGESELECT;
}
