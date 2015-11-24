#pragma once
#include "../../topheader/topheader.h"
#include "../../map/map.h"
#include "../../chara/normal_block/normal_block.h"
#include "../../chara/fall_block/fall_block.h"
#include "../../chara/thin_block/thin_block.h"
#include "../../chara/spring_block/spring_block.h"



class GameMain
{
private:

	int world_num;
	int stage_num;

	Map* map;
	std::vector<Character*> chara;

	void Collision();

	void HitCharaToBlock();
	CollisionType IsHitCharaToBlock(
		Vec2f,
		Vec2f,
		Vec2f,
		Vec2f,
		int,
		int,
		int,
		int);

	void HitCharaToChara();
	CollisionType IsHitCharaToChara(CharaType, Vec2f, Vec2f, Vec2f, Vec2f);

	void IsPlayCharaStoped(bool);
	void AddToChara(CharaType);

public:

	GameMain();
	~GameMain();

	void SetWorldNum(int);
	void SetStageNum(int);
	int GetWorldNum();
	int GetStageNum();
	StageStatus GetStageStatus();

	void Init(int, int);
	void UpDate();
	void Draw();
	SceneName Shift();


	int a = 0;
};