#include "stageselect.h"



//***************************************************************
//�X�e�[�W�Z���N�g

//private
void StageSelect::MoveCursol()
{
	//���ړ�
	if (stage_num > -1 && stage_num < 9)
	{
		if (Pad::Get().isPushButton(14))
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
		if (Pad::Get().isPushButton(16))
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
		if (Pad::Get().isPushButton(15))
		{
			cursol.pos.y() -= 250;

			stage_num += 5;
		}
	}

	//��ړ�
	if (stage_num > 4 && stage_num < 10)
	{
		if (Pad::Get().isPushButton(13))
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
	if (Pad::Get().isPushButton(1))
		return WORLDSELECT;
	if (Pad::Get().isPushButton(2))
		return GAMEMANAGER;

	return WORLDSELECT;
}