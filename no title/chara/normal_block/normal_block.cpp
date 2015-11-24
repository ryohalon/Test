#include "normal_block.h"

//private

void Normal_Block::NotStoped()
{
	Gravity();
	Move();
	Jump();
	Stop();
}

void Normal_Block::Gravity()
{
	if (normal_block->vector.y() < normal_block->max_gravity)
		normal_block->vector.y() += normal_block->gravity;

	normal_block->pos.y() -= normal_block->vector.y();
}

void Normal_Block::Move()
{
	MoveRight();
	MoveLeft();

	normal_block->pos.x() += normal_block->vector.x();
}

void Normal_Block::MoveLeft()
{
	if (Pad::Get().isPressButton(16))
	{
		if (normal_block->vector.x() > -normal_block->max_vector.x())
			normal_block->vector.x() -= normal_block->speed.x();

		if (normal_block->vector.x() < -normal_block->max_vector.x())
			normal_block->vector.x() = -normal_block->max_vector.x();
	}
	else if (!Pad::Get().isPressButton(16))
	{
		if (normal_block->vector.x() < 0.0f)
			normal_block->vector.x() += normal_block->speed.x() / normal_block->inertia;
	}
}

void Normal_Block::MoveRight()
{
	if (Pad::Get().isPressButton(14))
	{
		if (normal_block->vector.x() < normal_block->max_vector.x())
			normal_block->vector.x() += normal_block->speed.x();

		if (normal_block->vector.x() > normal_block->max_vector.x())
			normal_block->vector.x() = normal_block->max_vector.x();
	}
	else if (!Pad::Get().isPressButton(14))
	{
		if (normal_block->vector.x() > 0.0f)
			normal_block->vector.x() -= normal_block->speed.x() / normal_block->inertia;
	}
}

void Normal_Block::Jump()
{
	if (normal_block->jump_flag == false)
		IsJump();

	if (normal_block->speed.y() == 0.0f)
		return;

	if (normal_block->jump_limit > 0)
	{
		if (Pad::Get().isPressButton(1))
		{
			normal_block->jump_limit--;
		}
		else if (!Pad::Get().isPressButton(1))
		{
			normal_block->jump_limit = 0;
		}
	}

	if (normal_block->jump_limit == 0)
		normal_block->speed.y() -= 1.0f;

	if (normal_block->speed.y() == 0.0f)
		normal_block->jump_limit = 16;


	normal_block->pos.y() += normal_block->speed.y();
}

void Normal_Block::IsJump()
{
	if (!Pad::Get().isPushButton(1))
		return;

	if (Pad::Get().isPushButton(1))
	{
		normal_block->jump_flag = true;
		normal_block->speed.y() = normal_block->max_vector.y();

		return;
	}
}

void Normal_Block::Stop()
{
	if (!Pad::Get().isPushButton(0) || normal_block->stop_flag != false)
		return;

	normal_block->stop_flag = true;
}

void Normal_Block::Stoped()
{

}

//public

Normal_Block::Normal_Block()
{
	normal_block = new Block(
		CharaType::NORMAL,
		Vec2f(64.0f, 64.0f),
		Vec2f(1.0f, 0.0f),
		Vec2f(10.0f, 15.0f),
		1.0f,
		5.0f,
		2.0f,
		16);
}

Normal_Block::~Normal_Block()
{
	if (normal_block != nullptr)
		delete normal_block;
}

CharaType Normal_Block::GetCharaType()
{
	return normal_block->type;
}

Vec2f Normal_Block::GetPos()
{
	return normal_block->pos;
}

Vec2f Normal_Block::GetSize()
{
	return normal_block->size;
}

bool Normal_Block::GetStopFlag()
{
	return normal_block->stop_flag;
}

void Normal_Block::SetPos(Vec2f pos)
{
	normal_block->pos = pos;
}

void Normal_Block::SetVector(Vec2f vector)
{
	normal_block->vector = vector;
}

void Normal_Block::SetJump_Flag(bool jump_flag)
{
	normal_block->jump_flag = jump_flag;
}

void Normal_Block::Init()
{

}

void Normal_Block::Update()
{
	if (normal_block->stop_flag == false)
		NotStoped();
	else if (normal_block->stop_flag == true)
		Stoped();
	
}

void Normal_Block::Draw()
{
	drawFillBox(
		normal_block->pos.x(), normal_block->pos.y(),
		normal_block->size.x(), normal_block->size.y(),
		Color::cyan);
}