#include "worldselect.h"


//private

//カーソルを移動させる関数
void WorldSelect::MoveCursol()
{
	//右移動
	if (world_num > -1 && world_num < 2)
	{
		//ワールドをクリアしていないとカーソルは移動しない
		if (world_status[world_num] == StageStatus::CLEAR)
		{
			if (Pad::Get().isPushButton(14))
			{
				world.pos.x() -= 550;

				world_num++;
			}
		}
	}

	//左移動
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

//ワールドをクリアしたか情報を獲得する関数
void WorldSelect::IsWorldClear(StageStatus status)
{
	world_status[world_num] = status;

	//クリアした場合に次のワールドを開放する
	if (status == StageStatus::CLEAR)
		UnlockedNextWorld();
}

//次のワールドを開放する関数
void WorldSelect::UnlockedNextWorld()
{
	world_status[world_num + 1] = StageStatus::UNCLEAR;
}

//ワールド番号を渡す関数
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

		case StageStatus::LOCKED:
			drawFillBox(world.pos.x() + 550 * i, world.pos.y(), world.size, world.size, Color::gray);
			break;
		}
	}

	//カーソル
	drawBox(cursol.pos.x(), cursol.pos.y(), cursol.size, cursol.size, 10, Color::magenta);
}

//シーン切り替えの関数
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