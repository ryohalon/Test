#pragma once
#include "../../topheader/topheader.h"



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
	void Alpha();

public:

	Title();

	void UpDate();
	void Draw();
	SceneName Shift();

};