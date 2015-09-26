#include "operation.h"

void Operation(int& scene, Font font)
{
	Texture bg("res/image/bg_ope.png");
	Texture bg2("res/image/help_bg.png");
	Texture help("res/image/help.png");
	Texture player_s("res/image/player_s.png");
	Texture bg_help("res/image/bg_help.png");
	Texture bg_help2("res/image/bg_help2.png");
	Texture bg_help3("res/image/bg_help3.png");
	Texture gameend_logo("res/image/gameend_logo.png");
	Texture fall("res/image/fall.png");

	//���艹
	Media decision("res/sound/decision.wav");

	//�J���[
	Color color1 = Color::olive;
	Color color2 = Color::white;
	Color color3 = Color::white;
	Color color4 = Color::white;
	Color color5 = Color::olive;
	Color color6 = Color::olive;


	//�J�E���g
	int count = 0;




	while (scene == OPERATION || decision.isPlaying())
	{
		if (!env.isOpen()){ exit(0); }


		KeyPush(scene, count, color1, color2, color3, color4, color5, color6, decision);
		

		env.begin();

		drawTextureBox(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT, 0, 0, 512, 285, bg);
		drawTextureBox(-WIDTH / 2, -HEIGHT / 2 + 50, 512, HEIGHT, 45, 50, 467, 462, bg2);
		drawTextureBox(750, -HEIGHT / 2 - 320, 512, HEIGHT, 45, 50, 467, 462, bg2);

		if (count < 3)
		{
			drawTextureBox(-256, -128, 512, 256, 0, 0, 512, 256, help);
			font.draw("�Q�[���T�v", Vec2f(800.0f, -200.0f) - font.drawSize("�Q�[���T�v") / 2, color1);
			font.draw("������@", Vec2f(800.0f, -300.0f) - font.drawSize("������@") / 2, color2);
			font.draw("���ǂ�", Vec2f(800.0f, -400.0f) - font.drawSize("���ǂ�") / 2, color3);
			
		}

		if (count == 3 || count == 5)
		{
			drawTextureBox(-768, -320, 1536, 640, 0, 0, 2048, 1024, bg_help);
			font.draw("�Q�[�����", Vec2f(0.0f, 400.0f) - font.drawSize("�Q�[�����") / 2, Color::black);
			font.draw("����", Vec2f(0.0f, -400.0f) - font.drawSize("����") / 2, color5);
			font.draw("���ǂ�", Vec2f(800.0f, -400.0f) - font.drawSize("���ǂ�") / 2, color4);
		}

		if (count == 6 || count == 7)
		{
			drawTextureBox(-900, -256, 512, 512, 0, 0, 512, 512, bg_help2);
			drawTextureBox(-256, -256, 512, 512, 0, 0, 512, 512, fall);
			drawTextureBox(388, -256, 512, 512, 0, 0, 512, 512, bg_help3);
			drawTextureBox(-300, 230, 600, 256, 0, 0, 512, 128, gameend_logo);
			font.draw("������ʊO", Vec2f(-644, -320) - font.drawSize("������ʊO") / 2, Color::blue);
			font.draw("������", Vec2f(0, -320) - font.drawSize("������") / 2, Color::blue);
			font.draw("�ǂ�����", Vec2f(644, -320) - font.drawSize("�ǂ�����") / 2, Color::blue);
			font.draw("�O��", Vec2f(0.0f, -400.0f) - font.drawSize("�O��") / 2, color6);
			font.draw("���ǂ�", Vec2f(800.0f, -400.0f) - font.drawSize("���ǂ�") / 2, color4);
		}

		if (count == 4)
		{
			drawTextureBox(-WIDTH / 2, -HEIGHT / 2 - 100, WIDTH, HEIGHT, 0, 0, 2048, 1024, player_s);
			font.draw("S", Vec2f(-630, -250), Color::red);
			font.draw("���ǂ�", Vec2f(800.0f, -400.0f) - font.drawSize("���ǂ�") / 2, color4);
		}

		env.end();
	}
}




void KeyPush(int& scene, int& count, Color& color1, Color& color2, Color& color3, Color& color4, Color& color5, Color& color6, Media decision)
{
	bool keyflag = true;

	if (env.isPushKey(GLFW_KEY_ENTER))
	{
		decision.play();

		if ((count == 5 || count == 4 || count == 7) && keyflag == true)
		{
			count = 0;

			keyflag = false;
		}

		if (count == 3)
		{
			count = 6;

			color6 = Color::olive;
			color4 = Color::white;

			keyflag = false;
		}

		if (count == 6 && keyflag == true)
		{
			count = 3;

			color5 = Color::olive;
		}

		if (count == 0 && keyflag == true)
		{
			count = 3;

			color1 = Color::olive;
			color2 = Color::white;
			color3 = Color::white;
			color4 = Color::white;
			color5 = Color::olive;
			
		}

		if (count == 1)
		{
			count = 4;

			color1 = Color::olive;
			color2 = Color::white;
			color3 = Color::white;
			color4 = Color::olive;
		}

		if (count == 2){ scene = TITLE; }

	}

	if (env.isPushKey(GLFW_KEY_UP))
	{
		if (count == 1)
		{
			color1 = Color::olive;
			color2 = Color::white;

			count = 0;
		}

		if (count == 2)
		{
			color2 = Color::olive;
			color3 = Color::white;

			count = 1;
		}
		
	}


	if (env.isPushKey(GLFW_KEY_DOWN))
	{
		if (count == 1)
		{
			color2 = Color::white;
			color3 = Color::olive;

			count = 2;
		}

		if (count == 0)
		{
			color1 = Color::white;
			color2 = Color::olive;

			count = 1;
		}

	}

	if (env.isPushKey(GLFW_KEY_LEFT))
	{
		if (count == 5)
		{
			count = 3;

			color4 = Color::white;
			color5 = Color::olive;
		}

		if (count == 7)
		{
			count = 6;

			color6 = Color::olive;
			color4 = Color::white;
		}

	}

	if (env.isPushKey(GLFW_KEY_RIGHT))
	{
		if (count == 3)
		{
			count = 5;

			color4 = Color::olive;
			color5 = Color::white;
		}

		if (count == 6)
		{
			count = 7;

			color6 = Color::white;
			color4 = Color::olive;
		}
	}
}