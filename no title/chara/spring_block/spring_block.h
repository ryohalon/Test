#pragma once
#include "../chara.h"

class Spring_Block : public Character
{
private:

	Block* spring_block = nullptr;

	void NotStoped();
	void Gravity();
	void Move();
	void MoveLeft();
	void MoveRight();
	void Jump();
	void IsJump();
	void Stop();
	void Stoped();

public:

	Spring_Block();
	~Spring_Block();

	const float spring_power = -10.0f;

	CharaType GetCharaType();
	Vec2f GetPos();
	Vec2f GetSize();
	bool GetStopFlag();
	void SetPos(Vec2f);
	void SetVector(Vec2f);
	void SetJump_Flag(bool);

	void Init();
	void Update();
	void Draw();
};