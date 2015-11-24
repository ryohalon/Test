#pragma once
#include "../topheader/topheader.h"

class Character
{
protected:

	struct Block
	{
		CharaType type;
		Vec2f pos, size, vector, max_vector, speed;
		float gravity, max_gravity, inertia;
		int jump_limit;
		bool jump_flag, stop_flag;


		Block(
			CharaType type,
			Vec2f size,       //サイズ
			Vec2f speed,        //スピード
			Vec2f max_vector,   //ベクトルのMax値
			float gravity,      //重力の大きさ
			float max_gravity,  //重力のMax値
			float inertia,      //慣性の大きさ
			int jump_limit) :   //ジャンプの最大時間
			type(type),
			pos(Vec2f(0, 0)),
			size(size),
			vector(Vec2f(0.0f, 0.0f)),
			max_vector(max_vector),
			speed(speed),
			gravity(gravity),
			max_gravity(max_gravity),
			inertia(inertia),
			jump_limit(jump_limit),
			jump_flag(false),
			stop_flag(false)
		{};
	};

	virtual void NotStoped(){};
	virtual void Gravity(){};
	virtual void Move(){};
	virtual void MoveLeft(){};
	virtual void MoveRight(){};
	virtual void Jump(){};
	virtual void IsJump(){};
	virtual void Stop(){};
	virtual void Stoped(){};

public:

	Character(){}
	~Character(){}

	const float spring_power = 0.0f;

	virtual CharaType GetCharaType() = 0;
	virtual Vec2f GetPos() = 0;
	virtual Vec2f GetSize() = 0;
	virtual bool GetStopFlag() = 0;
	virtual void SetPos(Vec2f){};
	virtual void SetVector(Vec2f){};
	virtual void SetJump_Flag(bool){};
	virtual void SetFall_Flag(bool){};

	virtual void Init(){};
	virtual void Update(){};
	virtual void Draw(){};
};