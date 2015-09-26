#include "solo_menu.h"

void SoloMenu(int& scene, int& bone, Font& font, int& nbone)
{
	//画像
	Texture bone_image("res/image/bone.png");
	Texture bg = Texture("res/image/bg_ope.png");
	Texture bg2("res/image/help_bg.png");

	//決定音
	Media decision("res/sound/decision.wav");

	//ボーン
	std::string bone_display = std::to_string(bone);

	//カウント
	int count = 3;

	//カラー
	Color color1 = Color::olive;
	Color color2 = Color::white;
	Color color3 = Color::white;
	Color color4 = Color::olive;
	Color color5 = Color::white;
	Color color6 = Color::white;
	Color color7 = Color::white;

	//ポーズフラグ
	bool poseflag = false;

	//アイテム個数
	std::string nb = std::to_string(nbone);

	while (scene == SOLO_MENU || decision.isPlaying())
	{
		if (!env.isOpen()){ exit(0); }


		S_PushKey(scene, bone, count, poseflag, font,
			color1, color2, color3, color4, color5, color6, color7, 
			decision, nbone, bone_display, nb);


		env.begin();

		//背景
		drawTextureBox(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT, 0, 0, 512, 285, bg);
		drawTextureBox(-WIDTH / 2, -HEIGHT / 2 + 50, 512, HEIGHT, 45, 50, 467, 462, bg2);
		drawTextureBox(-WIDTH / 2 + 512, -HEIGHT / 2, 512, HEIGHT, 45, 50, 467, 462, bg2);

		//アイテム
		drawTextureBox(700.0f, 150.0f, 100.0f, 100.0f, 0.0f, 0.0f, 512.0f, 512.0f, bone_image);
		drawTextureBox(700.0f, 160.0f, 100.0f, 100.0f, 0.0f, 0.0f, 512.0f, 512.0f, bone_image);
		drawTextureBox(700.0f, 170.0f, 100.0f, 100.0f, 0.0f, 0.0f, 512.0f, 512.0f, bone_image);
		
		drawBox(700, 160, 100, 100, 5, Color::black);
		font.draw("ホネ", Vec2f(660.0f - font.drawSize("ホネ").x(), 210.0f - font.drawSize("ホネ").y() / 2), color3);
		font.draw(nb, Vec2f(820.0f, 180.0f), Color::cyan);
		

		if (count == 2)
		{
			font.draw("1000", Vec2f(760.0f - font.drawSize("ホネ").x(), 120.0f - font.drawSize("ホネ").y() / 2), Color::black);
		}

		//お金
		drawTextureBox(1000.0f - 115.0f - font.drawSize(bone_display).x(), 435.0f - font.drawSize(bone_display).y() / 2,
			80.0f, 80.0f,
			0.0f, 0.0f, 512.0f, 512.0f, bone_image);
		font.draw(bone_display, Vec2f(1000.0f - 25.0f - font.drawSize(bone_display).x(), 445.0f - font.drawSize(bone_display).y() / 2), Color::white);

		//スタートボタン
		font.draw("スタート", Vec2f(800.0f, -400.0f) - font.drawSize("スタート") / 2, color4);

		if (poseflag == true)
		{
			drawFillBox(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT, Color(0.0f, 0.0f, 0.0f, 0.7f));

			font.draw("タイトルへ", Vec2f(0.0f, 50.0f) - font.drawSize("タイトルへ") / 2, color1);
			font.draw("再開", Vec2f(0.0f, -50.0f) - font.drawSize("再開") / 2, color2);
		}


		env.end();

	}
}


void S_PushKey(int& scene, int& bone, int& count, bool& poseflag, Font& font, 
	Color& color1, Color& color2, Color& color3, Color& color4,
	Color& color5, Color& color6, Color& color7, Media decision, int& nbone,
	std::string& bone_display, std::string& nb)
{
	if (env.isPushKey(GLFW_KEY_SPACE))
	{
		decision.play();

		poseflag = !poseflag;

		color1 = Color::olive;
		color2 = Color::white;
		color3 = Color::white;
		color4 = Color::olive;

		if (poseflag == true){ count = 0; }
		if (poseflag == false){ count = 3; }
	}

	if (env.isPushKey(GLFW_KEY_ENTER))
	{
		decision.play();

		if (count == 2)
		{
			if (bone >= 1000)
			{
				nbone++;

				bone -= 1000;

				nb = std::to_string(nbone);
				bone_display = std::to_string(bone);
			}
			
		}

		if (count == 3)
		{
			scene = SOLO_GAMEMAIN;
		}

		if (poseflag == true)
		{
			if (count == 0){ scene = TITLE; }

			if (count == 1)
			{
				poseflag = false;

				count = 3;
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

		if (count == 3)
		{
			color3 = Color::olive;
			color4 = Color::white;

			count = 2;
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

		if (count == 2)
		{
			color3 = Color::white;
			color4 = Color::olive;

			count = 3;
		}
	}
};
