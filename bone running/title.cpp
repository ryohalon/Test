#include "title.h"

void Title(int& scene, Font& font, bool& start_flag)
{
	//画像
	Texture title("res/image/title.png");
	Texture bone_image("res/image/bone.png");

	//決定音
	Media decision("res/sound/decision.wav");

	//点滅
	float alpha;
	int alpha_count = 0.0f;

	//セレクト時のカウント
	int select_count = 0;

	//カラー
	Color c_gamestart = Color::olive;
	Color c_solo = Color::olive;
	Color c_multi = Color::black;
	Color c_tutorial = Color::black;
	Color c_option = Color::black;
	Color c_training = Color::olive;
	Color c_operation = Color::black;
	Color c_back = Color::black;

	




	//画像呼び込み
	Texture floor_image("res/image/floor.png");
	Texture dog_image("res/image/dog.png");
	Texture skeleton_image("res/image/skeleton.png");
	Texture bg = Texture("res/image/gm_bg.png");
	Vec2f bg_pos = Vec2f(-WIDTH / 2, -HEIGHT / 2);

	//サウンド
	Media skeletonjump("res/sound/skeletonjump.wav");
	Media dogjump("res/sound/dogjump.wav");
	Media dogdash("res/sound/dogdash.wav");
	Media skeletondash("res/sound/skeletondash.wav");

	//アニメーション
	int index = 4;
	int index2 = 0;
	int animation_count = 0;

	//for文で使う
	int i;
	int k;

	//プレイヤー
	Player skeleton, dog;

	//プレイヤー (ガイコツ)
	skeleton.pos.x() = 0.0f;
	skeleton.pos.y() = -160.0f;
	skeleton.size.x() = 64.0f;
	skeleton.size.y() = 80.0f;
	skeleton.vector.x() = 20.0f;
	skeleton.vector.y() = 0.0f;
	skeleton.jumpflag = false;
	skeleton.speedupflag = false;

	//プレイヤー (犬)
	dog.pos.x() = -700.0f;
	dog.pos.y() = -160.0;
	dog.size.x() = 128.0f;
	dog.size.y() = 64.0f;
	dog.vector.x() = 20.0f;
	dog.vector.y() = 0.0f;
	dog.jumpflag = false;
	dog.speedupflag = false;

	//床
	Object floor;

	//ステータス
	Status status;
	status.camera = 0.0f;
	status.scroll = 20.0;
	status.gravity = 0.2f;
	status.pose = false;


	//床
	int mapchip[50][50] =
	{														   //20																					     //50
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
	};
	float mapchip_pos_x[50][50];
	float mapchip_pos_y[50][50];
	float map_pos_x = -2048.0f;
	float map_pos_y = 352.0f;
	float map_size_xy = 128.0f;
	for (i = 0; i < 50; ++i)
	{
		for (k = 0; k < 50; ++k)
		{
			mapchip_pos_x[i][k] = map_pos_x;
			mapchip_pos_y[i][k] = map_pos_y;

			map_pos_x += map_size_xy;
		}

		map_pos_x = -2048.0f;
		map_pos_y -= map_size_xy;
	}










	while (scene == TITLE || decision.isPlaying())
	{
		if (!env.isOpen()){ exit(0); }

		env.begin();

		status.camera += status.scroll;

		if (mapchip_pos_x[0][33] - status.camera < -WIDTH / 2)
		{
			status.camera = 0;
		}
		

		//当たり判定
		for (i = 0; i < Geography::HEIGHTNUM; ++i)
		{
			for (k = 0; k < Geography::WIDTHNUM; ++k)
			{
				if (mapchip[i][k] == Geography::FLOOR)
				{
					floor.pos = Vec2f(mapchip_pos_x[i][k], mapchip_pos_y[i][k]);
					floor.size = Vec2f(map_size_xy, map_size_xy);

					HitFlag(skeleton, floor, status, mapchip[i - 1][k], mapchip[i - 1][k + 1], mapchip[i][k + 1], mapchip[i + 1][k], i, k);

					HitFlag(dog, floor, status, mapchip[i - 1][k], mapchip[i - 1][k + 1], mapchip[i][k + 1], mapchip[i + 1][k], i, k);
				}
			}
		}

		/////////////////////////////////////////////////////////////////////////
		//アニメーション
		/////////////////////////////////////////////////////////////////////////
		Animation(index, index2, animation_count);

		drawTextureBox(bg_pos.x(), bg_pos.y(), WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, bg);

		drawTextureBox(-450, 350, 1200, 200, 0, 0, 1000, 100, title);

		drawTextureBox(-180, 325, 200, 200, 0, 0, 512, 512, bone_image);

		drawTextureBox(15, 320, 200, 200, 0, 0, 512, 512, bone_image, Color::white, 1.5f, Vec2f(1.0f, 1.0f), Vec2f(1.0f, 1.0f));

		//地形
		for (i = 0; i < Geography::HEIGHTNUM; ++i)
		{
			for (k = 0; k < Geography::WIDTHNUM; ++k)
			{
				if (mapchip[i][k] == FLOOR)
				{
					if (mapchip_pos_x[i][k] + map_size_xy - status.camera >= -(WIDTH / 2) && mapchip_pos_x[i][k] - status.camera < WIDTH / 2)
					{
						drawTextureBox(mapchip_pos_x[i][k] - status.camera, mapchip_pos_y[i][k], map_size_xy, map_size_xy, 0, 0, 64, 64, floor_image);
					}
				}
			}
		}

		//犬
		drawTextureBox(dog.pos.x(), dog.pos.y(), dog.size.x(), dog.size.y(), 128 * index, 0, 100, 50, dog_image);

		//ガイコツ
		drawTextureBox(skeleton.pos.x(), skeleton.pos.y(), skeleton.size.x(), skeleton.size.y(), 128 * index2 + 30, 0, 98, 230, skeleton_image);





		if (start_flag == false)
		{
			PressEnter(font, start_flag, alpha, alpha_count, decision);

			if (env.isPushKey(GLFW_KEY_ENTER))
			{
				start_flag = true;

				decision.play();
			}

			env.flushInput();
		}
		else if (start_flag == true)
		{
			Select(font, scene, decision, select_count, c_gamestart, c_solo, c_multi, c_tutorial, c_option, c_training, c_operation, c_back);
		}

		env.end();
	}

	env.flushInput();
}

void PressEnter(Font& font, bool& start_flag, float& alpha, int& alpha_count, Media decision)
{
	alpha_count += 50.0f;
	alpha = (std::sin(alpha_count) + 1.0f) * 0.9f;

	font.draw("PRESS ENTER", Vec2f(0.0f - font.drawSize("PRESS ENTER").x() / 2, 0.0f - font.drawSize("PRESS ENTER").y() * 3), Color(0.0f, 0.0f, 0.0f, alpha));
}

void Select(Font& font, int& scene, Media decision, int& select_count,
	Color& c_gamestart, Color& c_solo, Color& c_multi, Color& c_tutorial,
	Color& c_option, Color& c_training, Color& c_operation, Color& c_back)
{

	KeyOperation(font, scene, select_count, c_gamestart, c_tutorial, c_option, c_training, c_operation, c_back, c_multi, c_solo, decision);

	if (select_count < 3)
	{
		font.draw("ゲームスタート", Vec2f(0.0f, -100.0f) - font.drawSize("ゲームスタート") / 2, c_gamestart);
		font.draw("チュートリアル", Vec2f(0.0f, -200.0f) - font.drawSize("チュートリアル") / 2, c_tutorial);
		font.draw("オプション", Vec2f(0.0f, -300.0f) - font.drawSize("オプション") / 2, c_option);
	}
	else if (select_count >= 3 && select_count < 6)
	{
		font.draw("トレーニング", Vec2f(0.0f, -100.0f) - font.drawSize("トレーニング") / 2, c_training);
		font.draw("ヘルプ", Vec2f(0.0f, -200.0f) - font.drawSize("ヘルプ") / 2, c_operation);
		font.draw("もどる", Vec2f(0.0f, -300.0f) - font.drawSize("もどる") / 2, c_back);
	}
	else if (select_count >= 6 && select_count < 9)
	{
		font.draw("1PLAYER", Vec2f(0, -100) - font.drawSize("one Player") / 2, c_solo);
		font.draw("2PAYER", Vec2f(25, -200) - font.drawSize("two Player") / 2, c_multi);
		font.draw("もどる", Vec2f(-50.0f, -300.0f) - font.drawSize("もどる") / 2, c_back);
	}
}

void KeyOperation(Font& font, int& scene, int& select_count, Color& c_gamestart, Color& c_tutorial, Color& c_option, Color& c_training, Color& c_operation, Color& c_back, Color& c_multi, Color& c_solo, Media decision)
{
	if (env.isPushKey(GLFW_KEY_UP))
	{
		if (select_count == 1)
		{
			select_count = 0;

			c_gamestart = Color::olive;
			c_tutorial = Color::black;
		}

		if (select_count == 2)
		{
			select_count = 1;

			c_tutorial = Color::olive;
			c_option = Color::black;
		}

		if (select_count == 4)
		{
			select_count = 3;

			c_training = Color::olive;
			c_operation = Color::black;
		}

		if (select_count == 5)
		{
			select_count = 4;

			c_operation = Color::olive;
			c_back = Color::black;
		}

		if (select_count == 7)
		{
			select_count = 6;

			c_solo = Color::olive;
			c_multi = Color::black;
		}

		if (select_count == 8)
		{
			select_count = 7;

			c_multi = Color::olive;
			c_back = Color::black;
		}
	}

	if (env.isPushKey(GLFW_KEY_DOWN))
	{
		if (select_count == 1)
		{
			select_count = 2;

			c_tutorial = Color::black;
			c_option = Color::olive;
		}

		if (select_count == 0)
		{
			select_count = 1;

			c_gamestart = Color::black;
			c_tutorial = Color::olive;
		}

		if (select_count == 4)
		{
			select_count = 5;

			c_back = Color::olive;
			c_operation = Color::black;
		}

		if (select_count == 3)
		{
			select_count = 4;

			c_training = Color::black;
			c_operation = Color::olive;
		}

		if (select_count == 7)
		{
			select_count = 8;

			c_multi = Color::black;
			c_back = Color::olive;
		}

		if (select_count == 6)
		{
			select_count = 7;

			c_solo = Color::black;
			c_multi = Color::olive;
		}
	}

	if (env.isPushKey(GLFW_KEY_ENTER))
	{

		decision.play();

		switch (select_count)
		{
		case 0:
			select_count = 6;
			c_solo = Color::olive;
			c_multi = Color::black;
			c_back = Color::black;
			break;

		case 1:
			select_count = 3;
			c_training = Color::olive;
			c_operation = Color::black;
			c_back = Color::black;
			break;

		case 2:
			scene = OPTION;
			break;

		case 3:
			scene = TUTORIAL;
			break;

		case 4:
			scene = OPERATION;
			break;

		case 5:
			select_count = 0;
			c_gamestart = Color::olive;
			c_tutorial = Color::black;
			c_option = Color::black;
			break;

		case 6:
			scene = SOLO_MENU;
			break;

		case 7:
			scene = MULTI_MENU;
			break;

		case 8:
			select_count = 0;
			c_gamestart = Color::olive;
			c_tutorial = Color::black;
			c_option = Color::black;
			break;
		}
	}
}