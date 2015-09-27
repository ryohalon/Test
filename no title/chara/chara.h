#pragma once
#include "../lib/framework.hpp"

class Chara
{
private:

	struct Block
	{
		Vec2f pos, size, vector;
		int gravity;
		bool jump_flag, stop_flag;
	};

	void Gravity();
	void Direction();

public:

	void UpDate();
	void Unit();
	void Draw();
};