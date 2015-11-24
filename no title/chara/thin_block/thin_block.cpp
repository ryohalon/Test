#include "Thin_Block.h"

//private

void Thin_Block::NotStoped()
{
	Gravity();
	Move();
	Jump();
	Stop();
}

void Thin_Block::Gravity()
{
	if (thin_block->vector.y() < thin_block->max_gravity)
		thin_block->vector.y() += thin_block->gravity;

	thin_block->pos.y() -= thin_block->vector.y();
}

void Thin_Block::Move()
{
	MoveRight();
	MoveLeft();

	thin_block->pos.x() += thin_block->vector.x();
}

void Thin_Block::MoveLeft()
{
	if (Pad::Get().isPressButton(16))
	{
		if (thin_block->vector.x() > -thin_block->max_vector.x())
			thin_block->vector.x() -= thin_block->speed.x();

		if (thin_block->vector.x() < -thin_block->max_vector.x())
			thin_block->vector.x() = -thin_block->max_vector.x();
	}
	else if (!Pad::Get().isPressButton(16))
	{
		if (thin_block->vector.x() < 0.0f)
			thin_block->vector.x() += thin_block->speed.x() / thin_block->inertia;
	}
}

void Thin_Block::MoveRight()
{
	if (Pad::Get().isPressButton(14))
	{
		if (thin_block->vector.x() < thin_block->max_vector.x())
			thin_block->vector.x() += thin_block->speed.x();

		if (thin_block->vector.x() > thin_block->max_vector.x())
			thin_block->vector.x() = thin_block->max_vector.x();
	}
	else if (!Pad::Get().isPressButton(14))
	{
		if (thin_block->vector.x() > 0.0f)
			thin_block->vector.x() -= thin_block->speed.x() / thin_block->inertia;
	}
}

void Thin_Block::Jump()
{
	if (thin_block->jump_flag == false)
		IsJump();

	if (thin_block->speed.y() == 0.0f)
		return;

	if (thin_block->jump_limit > 0)
	{
		if (Pad::Get().isPressButton(1))
		{
			thin_block->jump_limit--;
		}
		else if (!Pad::Get().isPressButton(1))
		{
			thin_block->jump_limit = 0;
		}
	}

	if (thin_block->jump_limit == 0)
		thin_block->speed.y() -= 1.0f;

	if (thin_block->speed.y() == 0.0f)
		thin_block->jump_limit = 16;


	thin_block->pos.y() += thin_block->speed.y();
}

void Thin_Block::IsJump()
{
	if (!Pad::Get().isPushButton(1))
		return;

	if (Pad::Get().isPushButton(1))
	{
		thin_block->jump_flag = true;
		thin_block->speed.y() = thin_block->max_vector.y();

		return;
	}
}

void Thin_Block::Stop()
{
	if (!Pad::Get().isPushButton(0) || thin_block->stop_flag != false)
		return;

	thin_block->stop_flag = true;
}

void Thin_Block::Stoped()
{

}

//public

Thin_Block::Thin_Block()
{
	thin_block = new Block(
		CharaType::THIN,
		Vec2f(128.0f, 32.0f),
		Vec2f(1.0f, 0.0f),
		Vec2f(10.0f, 15.0f),
		0.7f,
		3.0f,
		2.0f,
		13);
}

Thin_Block::~Thin_Block()
{
	if (thin_block != nullptr)
		delete thin_block;
}

CharaType Thin_Block::GetCharaType()
{
	return thin_block->type;
}

Vec2f Thin_Block::GetPos()
{
	return thin_block->pos;
}

Vec2f Thin_Block::GetSize()
{
	return thin_block->size;
}

bool Thin_Block::GetStopFlag()
{
	return thin_block->stop_flag;
}

void Thin_Block::SetPos(Vec2f pos)
{
	thin_block->pos = pos;
}

void Thin_Block::SetVector(Vec2f vector)
{
	thin_block->vector = vector;
}

void Thin_Block::SetJump_Flag(bool jump_flag)
{
	thin_block->jump_flag = jump_flag;
}

void Thin_Block::Init()
{

}

void Thin_Block::Update()
{
	if (thin_block->stop_flag == false)
		NotStoped();
	else if (thin_block->stop_flag == true)
		Stoped();

}

void Thin_Block::Draw()
{
	drawFillBox(
		thin_block->pos.x(), thin_block->pos.y(),
		thin_block->size.x(), thin_block->size.y(),
		Color::gray);
}