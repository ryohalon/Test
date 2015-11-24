#include "worldselect.h"


//private

//�J�[�\�����ړ�������֐�
void WorldSelect::MoveCursol()
{
	//�E�ړ�
	if (world_num > -1 && world_num < 2)
	{
		//���[���h���N���A���Ă��Ȃ��ƃJ�[�\���͈ړ����Ȃ�
		if (world_status[world_num] == StageStatus::CLEAR)
		{
			if (Pad::Get().isPushButton(14))
			{
				world.pos.x() -= 550;

				world_num++;
			}
		}
	}

	//���ړ�
	if (world_num > 0 && world_num < 3)
	{
		if (Pad::Get().isPushButton(16))
		{
			world.pos.x() += 550;

			world_num--;
		}
	}

}

//public

//�R���X�g���N�^
WorldSelect::WorldSelect() :
world_image("res/image/world.png"),
world_num(0)
{
	for (int i = 0; i < 3; i++)
	{
		if (i != 0)
			world_status[i] = StageStatus::LOCKED;
		else if (i == 0)
			world_status[i] = StageStatus::UNCLEAR;
	}
}

//���[���h���N���A�����������l������֐�
void WorldSelect::IsWorldClear(StageStatus status)
{
	world_status[world_num] = status;

	//�N���A�����ꍇ�Ɏ��̃��[���h���J������
	if (status == StageStatus::CLEAR)
		UnlockedNextWorld();
}

//���̃��[���h���J������֐�
void WorldSelect::UnlockedNextWorld()
{
	world_status[world_num + 1] = StageStatus::UNCLEAR;
}

//���[���h�ԍ���n���֐�
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

		case StageStatus::LOCKED:
			drawFillBox(world.pos.x() + 550 * i, world.pos.y(), world.size, world.size, Color::gray);
			break;
		}
	}

	//�J�[�\��
	drawBox(cursol.pos.x(), cursol.pos.y(), cursol.size, cursol.size, 10, Color::magenta);
}

//�V�[���؂�ւ��̊֐�
SceneName WorldSelect::Shift()
{
	if (Pad::Get().isPushButton(1))
		return SceneName::TITLE;
	if (Pad::Get().isPushButton(2))
	{
		GetWorldNum();

		return SceneName::STAGESELECT;
	}

	return SceneName::WORLDSELECT;
}