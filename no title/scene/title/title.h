#pragma once
#include "../../topheader/topheader.h"



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
	void Alpha();

public:

	Title();

	void UpDate();
	void Draw();
	SceneName Shift();

};