#include "fall_block.h"

//private

void Fall_Block::NotStoped()
{
	Gravity();
	Move();
	Jump();
	Stop();
}

void Fall_Block::Gravity()
{
	if (fall_block->vector.y() < fall_block->max_gravity)
		fall_block->vector.y() += fall_block->gravity;

	fall_block->pos.y() -= fall_block->vector.y();
}

void Fall_Block::Move()
{
	MoveRight();
	MoveLeft();

	fall_block->pos.x() += fall_block->vector.x();
}

void Fall_Block::MoveLeft()
{
	if (Pad::Get().isPressButton(16))
	{
		if (fall_block->vector.x() > -fall_block->max_vector.x())
			fall_block->vector.x() -= fall_block->speed.x();

		if (fall_block->vector.x() < -fall_block->max_vector.x())
			fall_block->vector.x() = -fall_block->max_vector.x();
	}
	else if (!Pad::Get().isPressButton(16))
	{
		if (fall_block->vector.x() < 0.0f)
			fall_block->vector.x() += fall_block->speed.x() / fall_block->inertia;
	}
}

void Fall_Block::MoveRight()
{
	if (Pad::Get().isPressButton(14))
	{
		if (fall_block->vector.x() < fall_block->max_vector.x())
			fall_block->vector.x() += fall_block->speed.x();

		if (fall_block->vector.x() > fall_block->max_vector.x())
			fall_block->vector.x() = fall_block->max_vector.x();
	}
	else if (!Pad::Get().isPressButton(14))
	{
		if (fall_block->vector.x() > 0.0f)
			fall_block->vector.x() -= fall_block->speed.x() / fall_block->inertia;
	}
}

void Fall_Block::Jump()
{
	if (fall_block->jump_flag == false)
		IsJump();

	if (fall_block->speed.y() == 0.0f)
		return;

	if (fall_block->jump_limit > 0)
	{
		if (Pad::Get().isPressButton(1))
		{
			fall_block->jump_limit--;
		}
		else if (!Pad::Get().isPressButton(1))
		{
			fall_block->jump_limit = 0;
		}
	}

	if (fall_block->jump_limit == 0)
		fall_block->speed.y() -= 1.0f;

	if (fall_block->speed.y() == 0.0f)
		fall_block->jump_limit = 16;


	fall_block->pos.y() += fall_block->speed.y();
}

void Fall_Block::IsJump()
{
	if (!Pad::Get().isPushButton(1))
		return;

	if (Pad::Get().isPushButton(1))
	{
		fall_block->jump_flag = true;
		fall_block->speed.y() = fall_block->max_vector.y();

		return;
	}
}

void Fall_Block::Stop()
{
	if (!Pad::Get().isPushButton(0) || fall_block->stop_flag != false)
		return;

	fall_block->stop_flag = true;
	fall_block->vector = Vec2f::Zero();
}

void Fall_Block::Stoped()
{
	if (fall_block->stop_flag != true || fall_flag != true)
		return;

	Fall();

	if (fall_block->pos.y() + fall_block->size.y() < -WIN_HEIGHT / 2)
		fall_flag = false;
}

void Fall_Block::Fall()
{
	if (fall_block->vector.y() < max_fall_speed)
		fall_block->vector.y() += fall_speed;

	fall_block->pos.y() -= fall_block->vector.y();
}

//public

Fall_Block::Fall_Block() :
fall_flag(false),
fall_speed(0.5f),
max_fall_speed(2.5f)
{
	fall_block = new Block(
		CharaType::FALL,
		Vec2f(64.0f, 64.0f),
		Vec2f(1.0f, 0.0f),
		Vec2f(10.0f, 15.0f),
		1.0f,
		5.0f,
		2.0f,
		16);
}

Fall_Block::~Fall_Block()
{
	if (fall_block != nullptr)
		delete fall_block;
}

CharaType Fall_Block::GetCharaType()
{
	return fall_block->type;
}

Vec2f Fall_Block::GetPos()
{
	return fall_block->pos;
}

Vec2f Fall_Block::GetSize()
{
	return fall_block->size;
}

bool Fall_Block::GetStopFlag()
{
	return fall_block->stop_flag;
}

void Fall_Block::SetFallFlag(bool fall_flag)
{
	this->fall_flag = fall_flag;
}

void Fall_Block::SetPos(Vec2f pos)
{
	fall_block->pos = pos;
}

void Fall_Block::SetVector(Vec2f vector)
{
	fall_block->vector = vector;
}

void Fall_Block::SetJump_Flag(bool jump_flag)
{
	fall_block->jump_flag = jump_flag;
}

void Fall_Block::SetFall_Flag(bool fall_flag)
{
	this->fall_flag = fall_flag;
}

void Fall_Block::Init()
{

}

void Fall_Block::Update()
{
	if (fall_block->stop_flag == false)
		NotStoped();
	else if (fall_block->stop_flag == true)
		Stoped();

}

void Fall_Block::Draw()
{
	drawFillBox(
		fall_block->pos.x(), fall_block->pos.y(),
		fall_block->size.x(), fall_block->size.y(),
		Color::blue);
}