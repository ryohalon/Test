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
			Vec2f size,       //�T�C�Y
			Vec2f speed,        //�X�s�[�h
			Vec2f max_vector,   //�x�N�g����Max�l
			float gravity,      //�d�͂̑傫��
			float max_gravity,  //�d�͂�Max�l
			float inertia,      //�����̑傫��
			int jump_limit) :   //�W�����v�̍ő厞��
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