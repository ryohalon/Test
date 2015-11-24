#include "gamemanager.h"


//private

void GameMain::Collision()
{
	HitCharaToBlock();

	if (chara.size() != 1)
		HitCharaToChara();
}

void GameMain::HitCharaToBlock()
{
	for (auto it : chara)
	{
		if (it->GetStopFlag() != false)
			continue;

		for (int i = 0; i < static_cast<int>(MapNum::HEIGHTNUM); i++)
		{
			for (int k = 0; k < static_cast<int>(MapNum::WIDTHNUM); k++)
			{
				if (map->GetMapType(i, k) == static_cast<int>(MapType::FLOOR))
				{
					switch (IsHitCharaToBlock(
						it->GetPos(),
						it->GetSize(),
						Vec2f(MAP_SIZE*k - WIN_WIDTH / 2,
						MAP_SIZE*-i + WIN_HEIGHT / 2 - MAP_SIZE),
						Vec2f(MAP_SIZE, MAP_SIZE),
						map->GetMapType(i - 1, k),
						map->GetMapType(i, k - 1),
						map->GetMapType(i, k + 1),
						map->GetMapType(i + 1, k)))
					{
					case CollisionType::TOP:
						it->SetPos(Vec2f(it->GetPos().x(), MAP_SIZE*-i + MAP_SIZE + WIN_HEIGHT / 2 - MAP_SIZE));
						it->SetJump_Flag(false);
						return;

					case CollisionType::LEFT:
						it->SetPos(Vec2f(MAP_SIZE*k - it->GetSize().x() - WIN_WIDTH / 2, it->GetPos().y()));
						break;

					case CollisionType::RIGHT:
						it->SetPos(Vec2f(MAP_SIZE*k + MAP_SIZE - WIN_WIDTH / 2, it->GetPos().y()));
						break;

					case CollisionType::DOWN:
						it->SetPos(Vec2f(it->GetPos().x(), MAP_SIZE*-i - it->GetSize().y() + WIN_HEIGHT / 2 - MAP_SIZE));
						break;

					case CollisionType::NONE:
						break;
					}
				}

				it->SetJump_Flag(true);
			}
		}
	}
}

CollisionType GameMain::IsHitCharaToBlock(
	Vec2f pos1,
	Vec2f size1,
	Vec2f pos2,
	Vec2f size2,
	int up,
	int left,
	int right,
	int down)
{
	if (up == static_cast<int>(MapType::NONE))
	{
		if (pos1.x() + size1.x() > pos2.x() &&
			pos1.x() < pos2.x() + size2.x())
		{
			if (pos1.y() > pos2.y() + size2.y() - 12.0f &&
				pos1.y() < pos2.y() + size2.y())
			{
				return CollisionType::TOP;
			}
		}
	}

	if (left == static_cast<int>(MapType::NONE))
	{
		if (pos1.x() + size1.x() > pos2.x() &&
			pos1.x() + size1.x() < pos2.x() + size2.x() / 2 - 12.0f)
		{
			if (pos1.y() + size1.y() >= pos2.y() &&
				pos1.y() < pos2.y() + size2.y())
			{
				return CollisionType::LEFT;
			}
		}
	}

	if (right == static_cast<int>(MapType::NONE))
	{
		if (pos1.x() > pos2.x() + size2.x() / 2 + 12.0f &&
			pos1.x() < pos2.x() + size2.x())
		{
			if (pos1.y() + size1.y() >= pos2.y() &&
				pos1.y() < pos2.y() + size2.y())
			{
				return CollisionType::RIGHT;
			}
		}
	}

	if (down == static_cast<int>(MapType::NONE))
	{
		if (pos1.x() + size1.x() > pos2.x() &&
			pos1.x() < pos2.x() + size2.x())
		{
			if (pos1.y() + size1.y() > pos2.y() &&
				pos1.y() + size1.y() < pos2.y() + 12.0f)
			{
				return CollisionType::DOWN;
			}
		}
	}

	return CollisionType::NONE;
}

void GameMain::HitCharaToChara()
{
	auto active_chara = chara.end() - 1;

	for (int i = 0; i < static_cast<int>(chara.size() - 1); i++)
	{
		switch (IsHitCharaToChara(
			chara[i]->GetCharaType(),
			(*active_chara)->GetPos(),
			(*active_chara)->GetSize(),
			chara[i]->GetPos(),
			chara[i]->GetSize()))
		{
		case CollisionType::TOP:
			(*active_chara)->SetPos(
				Vec2f((*active_chara)->GetPos().x(),
				chara[i]->GetPos().y() + chara[i]->GetSize().y()));

			if (chara[i]->GetCharaType() == CharaType::FALL)
				chara[i]->SetFall_Flag(true);

			if (chara[i]->GetCharaType() == CharaType::SPRING)
			{
				(*active_chara)->SetVector(Vec2f(0.0f, chara[i]->spring_power));

				break;
			}

			(*active_chara)->SetJump_Flag(false);

			break;

		case CollisionType::LEFT:
			if (chara[i]->GetCharaType() != CharaType::THIN)
			{
				(*active_chara)->SetPos(
					Vec2f(chara[i]->GetPos().x() - (*active_chara)->GetSize().x() - 1.0f,
					(*active_chara)->GetPos().y()));
			}

			break;

		case CollisionType::RIGHT:
			if (chara[i]->GetCharaType() != CharaType::THIN)
			{
				(*active_chara)->SetPos(
					Vec2f(chara[i]->GetPos().x() + chara[i]->GetSize().x() + 1.0f,
					(*active_chara)->GetPos().y()));
			}

			break;

		case CollisionType::DOWN:
			if (chara[i]->GetCharaType() != CharaType::THIN)
			{
				(*active_chara)->SetPos(
					Vec2f((*active_chara)->GetPos().x(),
					chara[i]->GetPos().y() - (*active_chara)->GetSize().y()));
			}

			break;

		case CollisionType::NONE:
			break;
		}
	}
}

CollisionType GameMain::IsHitCharaToChara(
	CharaType type,
	Vec2f active_chara_pos,
	Vec2f active_chara_size,
	Vec2f stop_chara_pos,
	Vec2f stop_chara_size)
{

	if (active_chara_pos.x() + active_chara_size.x() > stop_chara_pos.x() &&
		active_chara_pos.x() < stop_chara_pos.x() + stop_chara_size.x())
	{
		if (active_chara_pos.y() > stop_chara_pos.y() + stop_chara_size.y() - 12.0f &&
			active_chara_pos.y() < stop_chara_pos.y() + stop_chara_size.y())
		{
			return CollisionType::TOP;
		}
	}

	if (active_chara_pos.x() + active_chara_size.x() > stop_chara_pos.x() &&
		active_chara_pos.x() + active_chara_size.x() < stop_chara_pos.x() + stop_chara_size.x() / 2 - 12.0f)
	{
		if (active_chara_pos.y() + active_chara_size.y() >= stop_chara_pos.y() &&
			active_chara_pos.y() < stop_chara_pos.y() + stop_chara_size.y())
		{
			return CollisionType::LEFT;
		}
	}



	if (active_chara_pos.x() > stop_chara_pos.x() + stop_chara_size.x() / 2 + 12.0f &&
		active_chara_pos.x() < stop_chara_pos.x() + stop_chara_size.x())
	{
		if (active_chara_pos.y() + active_chara_size.y() >= stop_chara_pos.y() &&
			active_chara_pos.y() < stop_chara_pos.y() + stop_chara_size.y())
		{
			return CollisionType::RIGHT;
		}
	}



	if (active_chara_pos.x() + active_chara_size.x() > stop_chara_pos.x() &&
		active_chara_pos.x() < stop_chara_pos.x() + stop_chara_size.x())
	{
		if (active_chara_pos.y() + active_chara_size.y() > stop_chara_pos.y() &&
			active_chara_pos.y() + active_chara_size.y() < stop_chara_pos.y() + 12.0f)
		{
			return CollisionType::DOWN;
		}
	}

	return CollisionType::NONE;
}

void GameMain::IsPlayCharaStoped(bool is_stoped)
{
	if (is_stoped != true)
		return;

	AddToChara(CharaType::SPRING);
}

void GameMain::AddToChara(CharaType chara_type)
{
	switch (chara_type)
	{
	case CharaType::NORMAL:
		chara.push_back(new Normal_Block);
		break;

	case CharaType::FALL:
		chara.push_back(new Fall_Block);
		break;

	case CharaType::THIN:
		chara.push_back(new Thin_Block);
		break;

	case CharaType::SPRING:
		chara.push_back(new Spring_Block);
	}
}

//public

//コンストラクタ
GameMain::GameMain()
{
	map = new Map();

	AddToChara(CharaType::NORMAL);
}

GameMain::~GameMain()
{
	for (auto it : chara)
	{
		delete it;
	}
}

void GameMain::SetWorldNum(int num)
{
	world_num = num;
}

void GameMain::SetStageNum(int num)
{
	stage_num = num;
}

int GameMain::GetWorldNum()
{
	return world_num;
}

int GameMain::GetStageNum()
{
	return stage_num;
}

StageStatus GameMain::GetStageStatus()
{
	if (Pad::Get().isPushButton(2))
		return StageStatus::CLEAR;
	if (Pad::Get().isPushButton(1))
		return StageStatus::UNCLEAR;

	return StageStatus::UNCLEAR;
}

void GameMain::Init(int world_num, int stage_num)
{
	map->Init(GetWorldNum(), GetStageNum());
}

void GameMain::UpDate()
{
	//map->UpDate();

	for (auto it : chara)
	{
		it->Update();
	}

	for (int i = 0; i < static_cast<int>(chara.size()); i++)
	{
		if (i == chara.size() - 1)
		{
			IsPlayCharaStoped(chara[i]->GetStopFlag());
		}
	}

	Collision();
}

void GameMain::Draw()
{
	//背景
	drawFillBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, Color::white);

	map->Draw();

	for (auto it : chara)
	{
		it->Draw();
	}
}

//シーン切り替えの関数
SceneName GameMain::Shift()
{
	return SceneName::STAGESELECT;
}