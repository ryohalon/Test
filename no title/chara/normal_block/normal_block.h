#pragma once
#include "../chara.h"

class Normal_Block : public Character
{
private:

	Block* normal_block = nullptr;

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

	Normal_Block();
	~Normal_Block();

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