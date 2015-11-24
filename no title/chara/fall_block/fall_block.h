#pragma once
#include "../chara.h"

class Fall_Block : public Character
{
private:

	Block* fall_block = nullptr;
	bool fall_flag;
	float fall_speed;
	float max_fall_speed;

	void NotStoped();
	void Gravity();
	void Move();
	void MoveLeft();
	void MoveRight();
	void Jump();
	void IsJump();
	void Stop();
	void Stoped();
	void Fall();

public:

	Fall_Block();
	~Fall_Block();

	CharaType GetCharaType();
	Vec2f GetPos();
	Vec2f GetSize();
	bool GetStopFlag();
	void SetFallFlag(bool);
	void SetPos(Vec2f);
	void SetVector(Vec2f);
	void SetJump_Flag(bool);
	void SetFall_Flag(bool);

	void Init();
	void Update();
	void Draw();
};