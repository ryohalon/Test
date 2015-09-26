#include "multi_menu.h"

void Menu(int& scene, Font& font, int ranking[6], char name[3])
{
	//�摜
	Texture bg = Texture("res/image/bg_ope.png");

	//���艹
	Media decision("res/sound/decision.wav");

	//�J�E���g
	int count = 6;

	//�����L���O
	std::string na[3];
	std::string rank[5];

	for (int i = 0; i < 5; ++i)
	{
		rank[i] = std::to_string(ranking[i]);

		if (i < 3)
		{
			na[i] = name[i];
		}
	}

	//�J���[
	Color color1 = Color::olive;
	Color color2 = Color::white;
	Color color3 = Color::white;
	Color color4 = Color::white;
	Color color5 = Color::white; 
	Color color6 = Color::white;
	Color color7 = Color::white;

	//�|�[�Y�t���O
	bool poseflag = false;

	while (scene == MULTI_MENU || decision.isPlaying())
	{
		if (!env.isOpen()){ exit (0); }


		PushKey(scene, count, poseflag, font, color1, color2, color3, color4, color5, color6, color7, decision);


		env.begin();

		//�w�i
		drawTextureBox(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT, 0, 0, 512, 285, bg);

		//�X�^�[�g�{�^��
		font.draw("�X�^�[�g", Vec2f(800.0f, -400.0f) - font.drawSize("�X�^�[�g") / 2, color1);

		//�����L���O
		font.draw("�����L���O", Vec2f(-500.0f, 350.0f) - font.drawSize("�����L���O") / 2, Color::yellow);

		for (int i = 0; i < 5; ++i)
		{
			font.draw(rank[i], Vec2f(-300.0f, 200.0f - 100.0f * i) - font.drawSize(rank[i]) / 2, Color::black);

			if (i < 3)
			{
				font.draw(na[i], Vec2f(-680.0f + 90.0f * i, 200.0f) - font.drawSize(na[i]) / 2, Color::teal);
			}
		}

		if (poseflag == true)
		{
			drawFillBox(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT, Color(0.0f, 0.0f, 0.0f, 0.7f));

			font.draw("�^�C�g����", Vec2f(0.0f, 50.0f) - font.drawSize("�^�C�g����") / 2, color1);
			font.draw("�ĊJ", Vec2f(0.0f, -50.0f) - font.drawSize("�ĊJ") / 2, color2);
		}


		env.end();

	}
}


void PushKey(int& scene, int& count, bool& poseflag, Font& font,
	Color& color1, Color& color2, Color& color3, Color& color4,
	Color& color5, Color& color6, Color& color7, Media decision)
{
	if (env.isPushKey(GLFW_KEY_SPACE))
	{
		decision.play();

		poseflag = !poseflag;

		color1 = Color::olive;
		color2 = Color::white;

		if (poseflag == true){ count = 0; }
		if (poseflag == false){ count = 6; }
	}

	if (env.isPushKey(GLFW_KEY_ENTER))
	{
		decision.play();

		if (count == 6)
		{
			scene = MULTI_GAMEMAIN;
		}
		
		if (poseflag == true)
		{
			if (count == 0){ scene = TITLE; }

			if (count == 1)
			{ 
				poseflag = false;

				count = 6;
			}
		}
	}

	if (env.isPushKey(GLFW_KEY_UP))
	{
		if (count == 1)
		{
			color1 = Color::olive;
			color2 = Color::white;

			count = 0;
		}
	}

	if (env.isPushKey(GLFW_KEY_DOWN))
	{
		if (count == 0)
		{
			color1 = Color::white;
			color2 = Color::olive;

			count = 1;
		}
	}
};
