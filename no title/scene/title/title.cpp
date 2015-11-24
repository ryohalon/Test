#include "title.h"



//private

//�����x�̕ύX
float Title::ChangeAlpha()
{
	alpha_count += 25.0f;

	return ((std::sin(alpha_count) + 1.0f) * 0.9f);
}

void Title::Alpha()
{
	alpha = ChangeAlpha();
}

//public

//�R���X�g���N�^
Title::Title() :
title("res/image/title.png"),
press_start("res/image/press_start.png"),
alpha(1.0f),
alpha_count(0.0f)
{}

void Title::UpDate()
{
	Alpha();
}

void Title::Draw()
{
	//�w�i
	drawFillBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, Color::white);

	//�^�C�g��
	drawTextureBox(-500, 200, 1000, 250, 0, 0, 512, 128, title);

	//Press Start
	drawTextureBox(-256, -200, 512, 128, 0, 0, 256, 64, press_start, Color(0, 0, 0, alpha));
}

//�V�[���؂�ւ��̊֐�
SceneName Title::Shift()
{
	return SceneName::WORLDSELECT;
}