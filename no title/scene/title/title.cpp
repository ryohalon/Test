#include "title.h"



//***************************************************************
//タイトル

//private

//透明度の変更
float Title::ChangeAlpha()
{
	alpha_count += 25.0f;

	return ((std::sin(alpha_count) + 1.0f) * 0.9f);
}

//public

//コンストラクタ
Title::Title()
{
	title = Texture("res/image/title.png");
	press_start = Texture("res/image/press_start.png");

	alpha = 1.0f;
	alpha_count = 0.0f;
}

void Title::UpDate()
{
	alpha = ChangeAlpha();
}

void Title::Draw()
{
	//背景
	drawFillBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, Color::white);

	//タイトル
	drawTextureBox(-500, 200, 1000, 250, 0, 0, 512, 128, title);

	//Press Start
	drawTextureBox(-256, -200, 512, 128, 0, 0, 256, 64, press_start, Color(0, 0, 0, alpha));
}

SceneName Title::Shift()
{
	return SceneName::WORLDSELECT;
}