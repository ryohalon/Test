#include "stageselect.h"


//private

//カーソルを移動させる関数
void StageSelect::MoveCursol()
{
	//右移動
	if (stage_num > -1 && stage_num < 10)
	{
		if (Pad::Get().isPushButton(14))
		{
			//クリアしていないと次のステージにカーソルが移動しない
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

	//左移動
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

	//下移動
	if (stage_num > -1 && stage_num < 5)
	{
		if (Pad::Get().isPushButton(15))
		{
			//下のステージが開放されてなければカーソルが移動しない
			if (stage_status[world_num][stage_num + 5] != StageStatus::LOCKED)
			{
				cursol.pos.y() -= 250;

				stage_num += 5;
			}
		}
	}

	//上移動
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

//コンストラクタ
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

//ワールド番号を受け取る関数
void StageSelect::SetWorldNum(int num)
{
	world_num = num;
}

//ステージをクリアしたかの情報を獲得する関数
void StageSelect::IsStageClear(StageStatus status)
{
	//クリア済みの場合はいらない
	if (stage_status[world_num][stage_num] == StageStatus::UNCLEAR)
		stage_status[world_num][stage_num] = status;

	//クリアした場合に次のステージを開放する
	//ステージ10は次のステージがないので処理しない
	if (status == StageStatus::CLEAR && stage_num != 9)
	{
		if (stage_status[world_num][stage_num + 1] == StageStatus::LOCKED)
			UnlockedNextStage();
	}
}

//次のステージを開放する関数
void StageSelect::UnlockedNextStage()
{
	stage_status[world_num][stage_num + 1] = StageStatus::UNCLEAR;
}

//ステージ番号を渡す関数
int StageSelect::GetStageNum()
{
	return stage_num;
}

//ステージのクリア情報を渡す関数
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
//ステージ10をクリアしたかでワールドクリアを決めている

void StageSelect::UpDate()
{
	MoveCursol();
}

void StageSelect::Draw()
{
	//背景
	drawFillBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, Color::blue);

	//ワールド　ロゴ
	drawTextureBox(-250, 300, 500, 150, 0, 0, 256, 64, world_image);

	//ステージアイコン
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

	//カーソル
	drawBox(cursol.pos.x(), cursol.pos.y(), cursol.size, cursol.size, 10, Color::magenta);
}

//シーン切り替えの関数
SceneName StageSelect::Shift()
{
	if (Pad::Get().isPushButton(1))
		return SceneName::WORLDSELECT;
	if (Pad::Get().isPushButton(2))
		return SceneName::GAMEMANAGER;

	return SceneName::WORLDSELECT;
}