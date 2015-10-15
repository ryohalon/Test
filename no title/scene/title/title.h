#pragma once
#include "../../singleton/appenv/sin_appenv.h"
#include "../../singleton/gamepad/sin_gamepad.h"



//******************************************************************
//タイトル

class Title
{
private:

	//タイトル
	Texture title;
	//Press Start
	Texture press_start;

	//透明度
	float alpha;
	float alpha_count;

	float ChangeAlpha();

public:

	Title();

	void UpDate();
	void Draw();
	SceneName Shift();

};