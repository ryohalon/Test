#pragma once
#include "../topheader/topheader.h"

//�J�[�\��
struct Object
{
	Vec2i pos;
	int size;

	Object(Vec2i pos, int size) :
		pos(pos),
		size(size)
	{}
};