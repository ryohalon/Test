#pragma once
#include "lib/framework.hpp"

struct Object
{
	Vec2f pos, size;
};

struct Player:Object
{
	Vec2f vector;
	bool jumpflag, speedupflag;
};

struct Status
{
	float camera, scroll, gravity;
	bool pose;
};
