#pragma once
#include "../../singleton/appenv/sin_appenv.h"
#include "../../singleton/gamepad/sin_gamepad.h"



//******************************************************************
//�^�C�g��

class Title
{
private:

	//�^�C�g��
	Texture title;
	//Press Start
	Texture press_start;

	//�����x
	float alpha;
	float alpha_count;

	float ChangeAlpha();

public:

	Title();

	void UpDate();
	void Draw();
	SceneName Shift();

};