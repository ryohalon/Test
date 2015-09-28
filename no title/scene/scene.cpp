#include "scene.h"

//�^�C�g��

//private

//�����x�̕ύX
float Title::ChangeAlpha()
{
	alpha_count += 25.0f;
	
	return ( (std::sin(alpha_count) + 1.0f) * 0.9f );
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


//���[���h�Z���N�g

//private


//public

//�R���X�g���N�^
WorldSelect::WorldSelect()
{
	world_image = Texture("res/image/world.png");

	world_num = 1;

	for (int i = 0; i < 3; i++)
	{
		worldstatus[0][i] = StageStatus::UNCLEAR;
	}

	world.pos = Vec2f(-200, -250);
	world.size = 400;

	cursol.pos = Vec2f(-200, -250);
	cursol.size = 400;
}

void WorldSelect::UpDate()
{

}

int WorldSelect::GetterWorld()
{
	return world_num;
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
		switch (worldstatus[0][i])
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
		return STAGESELECT;

	return WORLDSELECT;
}


//�X�e�[�W�Z���N�g

//private


//public

//�R���X�g���N�^
StageSelect::StageSelect()
{
	world_image = Texture("res/image/world1.png");
	
	world_num = 1;
	stage_num = 1;

	for (int i = 0; i < 2; i++)
	{
		for (int k = 0; k < 5; k++)
		{
			stagestatus[i][k] = StageStatus::UNCLEAR;
		}
	}

	stage.pos = Vec2f(-600, -50);
	stage.size = 200;

	cursol.pos = Vec2f(-600, -50);
	cursol.size = 200;
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
	//�w�i
	drawFillBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, Color::blue);

	//���[���h�@���S
	drawTextureBox(-250, 300, 500, 150, 0, 0, 256, 64, world_image);

	//�X�e�[�W�A�C�R��
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


//�Q�[�����C��

//private


//public

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
