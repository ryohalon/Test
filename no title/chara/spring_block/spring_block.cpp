#include "spring_block.h"

//private

void Spring_Block::NotStoped()
{
	Gravity();
	Move();
	Jump();
	Stop();
}

void Spring_Block::Gravity()
{
	if (spring_block->vector.y() < spring_block->max_gravity)
		spring_block->vector.y() += spring_block->gravity;

	spring_block->pos.y() -= spring_block->vector.y();
}

void Spring_Block::Move()
{
	MoveRight();
	MoveLeft();

	spring_block->pos.x() += spring_block->vector.x();
}

void Spring_Block::MoveLeft()
{
	if (Pad::Get().isPressButton(16))
	{
		if (spring_block->vector.x() > -spring_block->max_vector.x())
			spring_block->vector.x() -= spring_block->speed.x();

		if (spring_block->vector.x() < -spring_block->max_vector.x())
			spring_block->vector.x() = -spring_block->max_vector.x();
	}
	else if (!Pad::Get().isPressButton(16))
	{
		if (spring_block->vector.x() < 0.0f)
			spring_block->vector.x() += spring_block->speed.x() / spring_block->inertia;
	}
}

void Spring_Block::MoveRight()
{
	if (Pad::Get().isPressButton(14))
	{
		if (spring_block->vector.x() < spring_block->max_vector.x())
			spring_block->vector.x() += spring_block->speed.x();

		if (spring_block->vector.x() > spring_block->max_vector.x())
			spring_block->vector.x() = spring_block->max_vector.x();
	}
	else if (!Pad::Get().isPressButton(14))
	{
		if (spring_block->vector.x() > 0.0f)
			spring_block->vector.x() -= spring_block->speed.x() / spring_block->inertia;
	}
}

void Spring_Block::Jump()
{
	if (spring_block->jump_flag == false)
		IsJump();

	if (spring_block->speed.y() == 0.0f)
		return;

	if (spring_block->jump_limit > 0)
	{
		if (Pad::Get().isPressButton(1))
		{
			spring_block->jump_limit--;
		}
		else if (!Pad::Get().isPressButton(1))
		{
			spring_block->jump_limit = 0;
		}
	}

	if (spring_block->jump_limit == 0)
		spring_block->speed.y() -= 1.0f;

	if (spring_block->speed.y() == 0.0f)
		spring_block->jump_limit = 16;


	spring_block->pos.y() += spring_block->speed.y();
}

void Spring_Block::IsJump()
{
	if (!Pad::Get().isPushButton(1))
		return;

	if (Pad::Get().isPushButton(1))
	{
		spring_block->jump_flag = true;
		spring_block->speed.y() = spring_block->max_vector.y();

		return;
	}
}

void Spring_Block::Stop()
{
	if (!Pad::Get().isPushButton(0) || spring_block->stop_flag != false)
		return;

	spring_block->stop_flag = true;
}

void Spring_Block::Stoped()
{

}

//public

Spring_Block::Spring_Block()
{
	spring_block = new Block(
		CharaType::SPRING,
		Vec2f(64.0f, 64.0f),
		Vec2f(1.0f, 0.0f),
		Vec2f(10.0f, 15.0f),
		1.0f,
		5.0f,
		2.0f,
		16);
}

Spring_Block::~Spring_Block()
{
	if (spring_block != nullptr)
		delete spring_block;
}

CharaType Spring_Block::GetCharaType()
{
	return spring_block->type;
}

Vec2f Spring_Block::GetPos()
{
	return spring_block->pos;
}

Vec2f Spring_Block::GetSize()
{
	return spring_block->size;
}

bool Spring_Block::GetStopFlag()
{
	return spring_block->stop_flag;
}

void Spring_Block::SetPos(Vec2f pos)
{
	spring_block->pos = pos;
}

void Spring_Block::SetVector(Vec2f vector)
{
	spring_block->vector = vector;
}

void Spring_Block::SetJump_Flag(bool jump_flag)
{
	spring_block->jump_flag = jump_flag;
}

void Spring_Block::Init()
{

}

void Spring_Block::Update()
{
	if (spring_block->stop_flag == false)
		NotStoped();
	else if (spring_block->stop_flag == true)
		Stoped();

}

void Spring_Block::Draw()
{
	drawFillBox(
		spring_block->pos.x(), spring_block->pos.y(),
		spring_block->size.x(), spring_block->size.y(),
		Color::green);
}