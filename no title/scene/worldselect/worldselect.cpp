#include "worldselect.h"



//***************************************************************
//ワールドセレクト

//private
void WorldSelect::MoveCursol()
{
	if (world_num > -1 && world_num < 2)
	{
		if (Pad::Get().isPushButton(14))
		{
			world.pos.x() -= 550;

			world_num++;
		}
	}

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

//コンストラクタ
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
	//背景
	drawFillBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, Color::green);

	//ワールド　ロゴ
	drawTextureBox(-250, 300, 500, 150, 0, 0, 256, 64, world_image);

	//ワールドアイコン
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

	//カーソル
	drawBox(cursol.pos.x(), cursol.pos.y(), cursol.size, cursol.size, 10, Color::magenta);
}

SceneName WorldSelect::Shift()
{
	if (Pad::Get().isPushButton(1))
		return TITLE;
	if (Pad::Get().isPushButton(2))
	{
		GetWorldNum();

		return STAGESELECT;
	}

	return WORLDSELECT;
}