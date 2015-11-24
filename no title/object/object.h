#pragma once
#include "../topheader/topheader.h"

//ÉJÅ[É\Éã
struct Object
{
	Vec2i pos;
	int size;

	Object(Vec2i pos, int size) :
		pos(pos),
		size(size)
	{}
};