#include "option.h"

void Option(int& scene, Font& font)
{
	Texture bg = Texture("res/image/bg_ope.png");
	//���艹
	Media decision("res/sound/decision.wav");

	while (scene == OPTION || decision.isPlaying())
	{
		if (!env.isOpen()){ exit(0); }

		if (env.isPushKey(GLFW_KEY_ENTER))
		{ 
			scene = TITLE;

			decision.play();
		}

		env.begin();

		//�w�i
		drawTextureBox(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT, 0, 0, 512, 285, bg);

		font.draw("���ǂ�", Vec2f(800.0f, -400.0f) - font.drawSize("���ǂ�") / 2, Color::olive);

		env.end();
	}

	env.flushInput();
}