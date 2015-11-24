#include "stageselect.h"


//private

//�J�[�\�����ړ�������֐�
void StageSelect::MoveCursol()
{
	//�E�ړ�
	if (stage_num > -1 && stage_num < 10)
	{
		if (Pad::Get().isPushButton(14))
		{
			//�N���A���Ă��Ȃ��Ǝ��̃X�e�[�W�ɃJ�[�\�����ړ����Ȃ�
			if (stage_status[world_num][stage_num] == StageStatus::CLEAR)
			{
				if (stage_num == 9)
				{
					if (stage_status[world_num][9] != StageStatus::LOCKED)
					{
						cursol.pos = Vec2i(-600, -50);
						stage_num = 0;
					}
				}
				else if (stage_num == 4)
				{
					cursol.pos = Vec2i(-600, -300);
					stage_num++;
				}
				else if (stage_num != 9)
				{
					cursol.pos.x() += 250;
					stage_num++;
				}
			}
		}
	}

	//���ړ�
	if (stage_num > -1 && stage_num < 10)
	{

		if (Pad::Get().isPushButton(16))
		{
			if (stage_num == 5)
			{
				cursol.pos = Vec2i(400, -50);
				stage_num--;
			}
			else if (stage_num == 0)
			{
				if (stage_status[world_num][9] != StageStatus::LOCKED)
				{
					cursol.pos = Vec2i(400, -300);
					stage_num = 9;
				}
			}
			else
			{
				cursol.pos.x() -= 250;
				stage_num--;
			}
		}
	}

	//���ړ�
	if (stage_num > -1 && stage_num < 5)
	{
		if (Pad::Get().isPushButton(15))
		{
			//���̃X�e�[�W���J������ĂȂ���΃J�[�\�����ړ����Ȃ�
			if (stage_status[world_num][stage_num + 5] != StageStatus::LOCKED)
			{
				cursol.pos.y() -= 250;

				stage_num += 5;
			}
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
StageSelect::StageSelect() :
world_image("res/image/world1.png"),
world_num(0),
stage_num(0)
{
	for (int i = 0; i < 3; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			if (k != 0)
				stage_status[i][k] = StageStatus::LOCKED;
			else if (k == 0)
				stage_status[i][k] = StageStatus::UNCLEAR;
		}
	}
}

//���[���h�ԍ����󂯎��֐�
void StageSelect::SetWorldNum(int num)
{
	world_num = num;
}

//�X�e�[�W���N���A�������̏����l������֐�
void StageSelect::IsStageClear(StageStatus status)
{
	//�N���A�ς݂̏ꍇ�͂���Ȃ�
	if (stage_status[world_num][stage_num] == StageStatus::UNCLEAR)
		stage_status[world_num][stage_num] = status;

	//�N���A�����ꍇ�Ɏ��̃X�e�[�W���J������
	//�X�e�[�W10�͎��̃X�e�[�W���Ȃ��̂ŏ������Ȃ�
	if (status == StageStatus::CLEAR && stage_num != 9)
	{
		if (stage_status[world_num][stage_num + 1] == StageStatus::LOCKED)
			UnlockedNextStage();
	}
}

//���̃X�e�[�W���J������֐�
void StageSelect::UnlockedNextStage()
{
	stage_status[world_num][stage_num + 1] = StageStatus::UNCLEAR;
}

//�X�e�[�W�ԍ���n���֐�
int StageSelect::GetStageNum()
{
	return stage_num;
}

//�X�e�[�W�̃N���A����n���֐�
StageStatus* StageSelect::GetStageStatus()
{
	return *stage_status;
}

StageStatus StageSelect::IsWorldClear()
{
	if (stage_status[world_num][9] == StageStatus::CLEAR)
		return StageStatus::CLEAR;
	else
		return StageStatus::UNCLEAR;
}
//�X�e�[�W10���N���A�������Ń��[���h�N���A�����߂Ă���

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
			drawFillBox(stage_icon.pos.x() + 250 * (k % 5), stage_icon.pos.y() - 250 * (k / 5 % 10), stage_icon.size, stage_icon.size, Color::yellow);
			break;

		case StageStatus::CLEAR:
			drawFillBox(stage_icon.pos.x() + 250 * (k % 5), stage_icon.pos.y() - 250 * (k / 5 % 10), stage_icon.size, stage_icon.size, Color::cyan);
			break;

		case StageStatus::LOCKED:
			drawFillBox(stage_icon.pos.x() + 250 * (k % 5), stage_icon.pos.y() - 250 * (k / 5 % 10), stage_icon.size, stage_icon.size, Color::gray);
			break;
		}
	}

	//�J�[�\��
	drawBox(cursol.pos.x(), cursol.pos.y(), cursol.size, cursol.size, 10, Color::magenta);
}

//�V�[���؂�ւ��̊֐�
SceneName StageSelect::Shift()
{
	if (Pad::Get().isPushButton(1))
		return SceneName::WORLDSELECT;
	if (Pad::Get().isPushButton(2))
		return SceneName::GAMEMANAGER;

	return SceneName::WORLDSELECT;
}