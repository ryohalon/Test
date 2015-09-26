#include "lib/framework.hpp"
#include<iostream>
#include<string>
using namespace std;

int main()
{
	AppEnv env(1500, 2000);

	//フォント
	Font font("res/msgothic.ttc");
	//フォントカラー
	Color color = Color::white;

	//音声
	Media baund("res/sound/baund.wav");
	Media start("res/sound/start.wav");
	Media BGM("res/sound/bgm.wav");
	Media clear("res/sound/clear.wav");

	baund.gain(2.0);

	//背景
	Texture haikei1("res/picture/haikei1.png");
	Texture haikei2("res/picture/haikei2.png");
	Texture haikei3("res/picture/haikei3.png");

	float x, y, sy, g, yv, syv, camera;

	//プレイヤー座標
	x = 0.0f;
	y = -850.0f;

	//残像
	float xz[18];
	float yz[18];
	float t[18];
	float to = 0.1f;
	int iz = 18;

	for (int i = 0; i < iz; ++i)
	{
		xz[i] = 0;
		yz[i] = -850;
	}

	for (int i = iz - 1; i > 0; --i)
	{
		t[i] = to;
		to += 0.01f;
	}
	//床
	sy = -850.0f;
	//足場
	float asibax[] = { 450, -50, -450, -750, 0, 200, 550, -350, 500, 0,
		-250, 300, 200, 170, 140, 110, 80, 50, 20, -10,
		-40, -70, -100, -70, -40, -10, 20, 50, 80, 110,
		140, 170, 200 };
	float asibay[] = { 900, 1200, 1500, 1800, 1800, 2200, 2300, 2500, 2500, 3000,
		2800, 3400, 3800, 3900, 4000, 4100, 4200, 4300, 4400, 4500,
		4600, 4700, 4800, 4900, 5000, 5100, 5200, 5300, 5400, 5500,
		5600, 5700, 5800 };

	//重力
	g = -0.6f;
	syv = 25.0f;
	yv = syv;


	int asibakazu;

	//画面スクロール
	camera = 0.0f;

	float sg1 = 0;
	float sg2 = 0;

	bool syh = true;
	bool kaf = true;
	bool chukan_flag = false;
	bool start_flag = false;
	bool time_flag = false;
	bool gaiyou = false;


	//タイム
	int stagetime1 = 0;
	char stm1 = 0;
	int stagetime2 = 0;
	char stm2 = 0;
	int stagetime3 = 0;
	char stm3 = 0;
	int stagetimesogo = 0;
	char stms = 0;
	float timecount = 0;
	int timehyojun = 60;
	string t1;
	string tm1;
	string t2;
	string tm2;
	string t3;
	string tm3;

	while (1)
	{
		env.begin();

		if (!env.isOpen()){ return 0; }

		//プレイヤー座標
		x = 0.0f;
		y = -850.0f;
		//床
		sy = -850.0f;

		//重力
		g = -0.6f;
		syv = 25.0f;
		yv = syv;

		//画面スクロール
		camera = 0.0f;

		syh = true;
		kaf = true;
		chukan_flag = false;
		start_flag = false;
		time_flag = false;

		//スタート画面
		while (1)
		{
			env.begin();

			if (!env.isOpen()){ return 0; }

			//背景
			drawTextureBox(-750, -1000 + camera, 1500, 8000, 0, 0, 1024, 2048, haikei1, Color::white);

			Vec2f pos = env.mousePosition();

			if (gaiyou == false)
			{

				if (pos.x() >= -420 && pos.x() <= 380 && pos.y() >= -520 && pos.y() <= -370)
				{
					color = Color::blue;

					if (env.isPushButton(Mouse::LEFT))
					{
						start.play();

						break;
					}
				}
				else
				{
					color = Color::white;
				}

				drawBox(-420, -520, 800, 150, 10, color);
				font.size(150);
				font.draw("Game Start", Vec2f(-400, -500), color);
				font.size(50);
				font.draw("※左クリック", Vec2f(-400, -600), Color::white);

				font.size(175);
				font.draw("クライミング", Vec2f(-700, 500), Color::magenta);
				font.draw("アタック!!", Vec2f(-150, 250), Color::red);

				font.size(50);
				font.draw("*操作方法*", Vec2f(-750, -700), Color::white);
				font.draw("SPACE::方向転換", Vec2f(-750, -800), Color::white);
				font.draw("G::ゲーム概要", Vec2f(400, -700), Color::white);

				if (env.isPushKey('G'))
				{
					gaiyou = true;
					start.play();
				}

			}
			else
			{
				font.size(100);
				font.draw("クライミングアタックとは？", Vec2f(-700, 700), Color::white);
				font.draw("各ステージをクリアし", Vec2f(-700, 100), Color::white);
				font.draw("タイムを競うゲームです", Vec2f(-500, -100), Color::white);
				font.draw("ENTER::タイトルに戻る", Vec2f(-600, -700), Color::white);

				if (env.isPushKey(GLFW_KEY_ENTER)){ gaiyou = false; }
			}

			env.end();
		}

		BGM.play();

		//第１ステージ
		while (1)
		{
			env.begin();

			if (!env.isOpen()){ return 0; }

			drawTextureBox(-750, -1000 + camera / 2, 1500, 8192, 0, 0, 1500, 8192, haikei3, Color::white);

			if (time_flag == true)
			{
				//タイム
				timecount++;

				if (timecount == timehyojun)
				{
					stagetime1++;

					timehyojun += 60;
				}

				if (stagetime1 == 60)
				{
					stm1++;

					stagetime1 = 0;
				}
			}



			if (chukan_flag == false)
			{
				if (start_flag == true)
				{

					BGM.looping(true);

					//重力
					yv += g;
					y += yv;

					if (yv < -25.0f){ yv = -25.0f; }


					if (y > -850)
					{
						if (y < 0)
						{
							sg1 = y / 10;
							sg1 = 85 + sg1;
						}
						else
						{
							sg2 = y / 10;
							sg1 = 85;
						}

						if (sg2 > 620){ sg2 = 620; }
					}

					drawBox(680, 100, 50, 725, 10, Color::white);

					if (sg1 + sg2 > 0)
					{
						drawFillBox(690, 110, 30, sg2 + sg1, Color::green);
					}
					font.size(55);
					font.draw("G", Vec2f(690, 830), Color::red);
					font.draw("S", Vec2f(690, 50), Color::yellow);
				}
				else
				{
					font.size(100);
					font.draw("SPACEで開始", Vec2f(-300, -950), Color::red);

					if (env.isPushKey(GLFW_KEY_SPACE))
					{
						start_flag = true;

						time_flag = true;

					}
				}

				//画面のスクロール
				if (y > 0)
				{
					camera -= yv;

					if (y + camera > 0){ camera--; }
				}
				else
				{
					camera = 0;
				}

				//壁判定
				if (kaf == true)
				{
					x += 10.0f;
				}
				if (x > 700)
				{
					kaf = false;

					baund.play();
				}
				if (kaf == false)
				{
					x -= 10.0;
				}
				if (x < -750)
				{
					kaf = true;

					baund.play();
				}
			}
			else
			{
				x += 10;

				string t1 = to_string(stagetime1);
				string tm1 = to_string(stm1);

				if (x > 750)
				{
					BGM.stop();

					font.size(300);
					font.draw(tm1 + ":" + t1, Vec2f(100, 500), Color::red);

					font.size(200);
					font.draw("Stage Clear!!", Vec2f(-600, -100), Color::yellow);
					font.size(100);
					font.draw("SPACEで次へ", Vec2f(-300, -250), Color::green);
					if (env.isPushKey(GLFW_KEY_SPACE)){ break; }
				}

			}

			//キー入力方向転換
			if (env.isPushKey(GLFW_KEY_SPACE)){ kaf = !kaf; }

			//床　当たり判定
			if (y < sy)
			{
				y = sy;
				yv = syv;

				baund.play();
			}

			//床
			drawLine(-750, -850 + camera, 750, -850 + camera, 5, Color::white);


			//足場１
			drawBox(0, -400 + camera, 200, -50, 10, Color::white);

			//足場１上の判定
			if (x + 50 > 0 && x < 200 && y <= -400 && y > -450)
			{
				y = -395;
				yv = syv;

				baund.play();
			}

			//足場１横の判定
			//左側面
			if (x + 50 >= 0 && x + 50 <= 20 && y > -450 && y < -400)
			{
				x = -50;
				kaf = !kaf;

				baund.play();
			}

			//右側面
			if (x >= 180 && x <= 200 && y > -450 && y < -400)
			{
				x = 200;
				kaf = !kaf;

				baund.play();
			}

			//足場１下の判定
			if (x + 50 >= 0 && x <= 200 && y > -500 && y <= -450)
			{
				syh = false;
			}

			if (syh == false && yv > 0 && y < -400)
			{
				yv = yv * -1.0f;
				y += yv;
				syh = true;

				baund.play();
			}

			//足場２
			drawBox(500, 0 + camera, 200, -50, 10, Color::white);

			//足場２上の判定
			if (x + 50 > 500 && x < 700 && y <= 0 && y >= -50)
			{
				y = 5;
				yv = syv;

				baund.play();
			}

			//足場２横の判定
			//左側面
			if (x + 50 >= 500 && x + 50 <= 520 && y > -50 && y < 0)
			{
				x = 450;
				kaf = !kaf;

				baund.play();
			}

			//右側面
			if (x >= 680 && x <= 700 && y > -50 && y < 0)
			{
				x = 700;
				kaf = !kaf;

				baund.play();
			}

			//足場２下の判定
			if (x + 50 >= 500 && x <= 700 && y >= -100 && y <= -50)
			{
				syh = false;
			}

			if (syh == false && yv > 0 && y < 0)
			{
				yv = yv * -1.0f;
				y += yv;
				syh = true;

				baund.play();
			}

			//足場３
			drawBox(300, 500 + camera, 200, -50, 10, Color::white);

			//足場３上の判定
			if (x + 50 > 300 && x < 500 && y <= 500 && y >= 450)
			{
				y = 505;
				yv = syv;

				baund.play();
			}

			//足場３横の判定
			//左側面
			if (x + 50 >= 300 && x + 50 <= 320 && y > 450 && y < 500)
			{
				x = 250;
				kaf = !kaf;

				baund.play();
			}

			//右側面
			if (x >= 480 && x <= 500 && y > 450 && y < 500)
			{
				x = 500;
				kaf = !kaf;

				baund.play();
			}

			//足場３下の判定
			if (x + 50 >= 300 && x <= 500 && y >= 400 && y <= 450)
			{
				syh = false;
			}

			if (syh == false && yv > 0 && y < 500)
			{
				yv = yv * -1.0f;
				y += yv;
				syh = true;

				baund.play();
			}

			//足場４
			drawBox(-100, 400 + camera, 200, -100, 10, Color::white);

			//足場４上の判定
			if (x + 50 > -100 && x < 100 && y <= 400 && y >= 350)
			{
				y = 405;
				yv = syv;

				baund.play();
			}

			//足場４横の判定
			//左側面
			if (x + 50 >= -100 && x + 50 <= -80 && y > 300 && y < 400)
			{
				x = -150;
				kaf = !kaf;

				baund.play();
			}

			//右側面
			if (x >= 80 && x <= 100 && y > 300 && y < 400)
			{
				x = 100;
				kaf = !kaf;

				baund.play();
			}

			//足場４下の判定
			if (x + 50 >= -100 && x <= 100 && y >= 250 && y <= 300)
			{
				syh = false;
			}

			if (syh == false && yv > 0 && y < 400)
			{
				yv = yv * -1.0f;
				y += yv;
				syh = true;

				baund.play();
			}


			//足場５
			drawBox(-300, -300 + camera, 150, -30, 10, Color::white);

			//足場５上の判定
			if (x + 50 > -300 && x < -150 && y <= -290 && y > -330)
			{
				y = -295;
				yv = syv;

				baund.play();
			}

			//足場５横の判定
			//左側面
			if (x + 50 >= -300 && x + 50 <= -260 && y > -350 && y < -300)
			{
				x = -350;
				kaf = !kaf;

				baund.play();
			}

			//右側面
			if (x >= -110 && x <= -150 && y > -350 && y < -300)
			{
				x = -150;
				kaf = !kaf;

				baund.play();
			}

			//足場５下の判定
			if (x + 50 >= -300 && x <= -150 && y >= -380 && y <= -330)
			{
				syh = false;
			}

			if (syh == false && yv > 0 && y < -300)
			{
				yv = yv * -1.0f;
				y += yv;
				syh = true;

				baund.play();
			}

			//足場６
			drawBox(-750, 50 + camera, 250, -50, 10, Color::white);

			//足場６上の判定
			if (x + 50 > -750 && x < -500 && y <= 50 && y >= 0)
			{
				y = 55;
				yv = syv;

				baund.play();
			}

			//足場６横の判定
			//右側面
			if (x >= -520 && x <= -500 && y > -50 && y < 0)
			{
				x = -500;
				kaf = !kaf;

				baund.play();
			}

			//足場６下の判定
			if (x + 50 >= -750 && x <= -500 && y >= -50 && y <= 0)
			{
				syh = false;
			}

			if (syh == false && yv > 0 && y < 0)
			{
				yv = yv * -1.0f;
				y += yv;
				syh = true;

				baund.play();
			}

			//足場７
			drawBox(-600, 500 + camera, 200, -50, 10, Color::white);

			//足場７上の判定
			if (x + 50 > -600 && x < -400 && y <= 500 && y > 450)
			{
				y = 500;
				yv = syv;

				baund.play();
			}

			//足場７横の判定
			//左側面
			if (x + 50 >= -600 && x + 50 <= -580 && y > 450 && y < 500)
			{
				x = -650;
				kaf = !kaf;

				baund.play();
			}

			//右側面
			if (x >= -420 && x <= -400 && y > 450 && y < 500)
			{
				x = -400;
				kaf = !kaf;

				baund.play();
			}

			//足場７下の判定
			if (x + 50 >= -600 && x <= -400 && y > 400 && y <= 450)
			{
				syh = false;
			}

			if (syh == false && yv > 0 && y < 500)
			{
				yv = yv * -1.0f;
				y += yv;
				syh = true;

				baund.play();
			}

			//足場８
			drawBox(asibax[0], asibay[0] + camera, 200, -10, 10, Color::white);

			//足場８上の判定
			if (x + 50 > asibax[0] && x < asibax[0] + 200 && y <= asibay[0] && y > asibay[0] - 30)
			{
				y = asibay[0] + 5;
				yv = syv;

				baund.play();
			}

			//足場9
			drawBox(asibax[1], asibay[1] + camera, 200, -10, 10, Color::white);

			//足場9上の判定
			if (x + 50 > asibax[1] && x < asibax[1] + 200 && y <= asibay[1] && y > asibay[1] - 30)
			{
				y = asibay[1] + 5;
				yv = syv;

				baund.play();
			}

			//足場10
			drawBox(asibax[2], asibay[2] + camera, 200, -10, 10, Color::white);

			//足場10上の判定
			if (x + 50 > asibax[2] && x < asibax[2] + 200 && y <= asibay[2] && y > asibay[2] - 30)
			{
				y = asibay[2] + 5;
				yv = syv;

				baund.play();
			}

			//足場11
			drawBox(asibax[3], asibay[3] + camera, 200, -10, 10, Color::white);

			//足場11上の判定
			if (x + 50 > asibax[3] && x < asibax[3] + 200 && y <= asibay[3] && y > asibay[3] - 30)
			{
				y = asibay[3] + 5;
				yv = syv;

				baund.play();
			}

			//足場12
			drawBox(asibax[4], asibay[4] + camera, 200, -10, 10, Color::white);

			//足場12上の判定
			if (x + 50 > asibax[4] && x < asibax[4] + 200 && y <= asibay[4] && y > asibay[4] - 30)
			{
				y = asibay[4] + 5;
				yv = syv;

				baund.play();
			}

			//足場13
			drawBox(asibax[5], asibay[5] + camera, 200, -10, 10, Color::white);

			//足場13上の判定
			if (x + 50 > asibax[5] && x < asibax[5] + 200 && y <= asibay[5] && y > asibay[5] - 30)
			{
				y = asibay[5] + 5;
				yv = syv;

				baund.play();
			}

			//足場14
			drawBox(asibax[6], asibay[6] + camera, 200, -10, 10, Color::white);

			//足場14上の判定
			if (x + 50 > asibax[6] && x < asibax[6] + 200 && y <= asibay[6] && y > asibay[6] - 30)
			{
				y = asibay[6] + 5;
				yv = syv;

				baund.play();
			}

			//足場15
			drawBox(asibax[7], asibay[7] + camera, 200, -10, 10, Color::white);

			//足場15上の判定
			if (x + 50 > asibax[7] && x < asibax[7] + 200 && y <= asibay[7] && y > asibay[7] - 30)
			{
				y = asibay[7] + 5;
				yv = syv;

				baund.play();
			}

			//足場16
			drawBox(asibax[8], asibay[8] + camera, 200, -10, 10, Color::white);

			//足場16上の判定
			if (x + 50 > asibax[8] && x < asibax[8] + 200 && y <= asibay[8] && y > asibay[8] - 30)
			{
				y = asibay[8] + 5;
				yv = syv;

				baund.play();
			}


			//足場17
			drawBox(asibax[9], asibay[9] + camera, 200, -10, 10, Color::white);

			//足場17上の判定
			if (x + 50 > asibax[9] && x < asibax[9] + 200 && y <= asibay[9] && y > asibay[9] - 30)
			{
				y = asibay[9] + 5;
				yv = syv;

				baund.play();
			}


			//足場18
			drawBox(asibax[10], asibay[10] + camera, 200, -10, 10, Color::white);

			//足場18上の判定
			if (x + 50 > asibax[10] && x < asibax[10] + 200 && y <= asibay[10] && y > asibay[10] - 30)
			{
				y = asibay[10] + 5;
				yv = syv;

				baund.play();
			}


			//足場19
			drawBox(asibax[11], asibay[11] + camera, 200, -10, 10, Color::white);

			//足場19上の判定
			if (x + 50 > asibax[11] && x < asibax[11] + 200 && y <= asibay[11] && y > asibay[11] - 30)
			{
				y = asibay[11] + 5;
				yv = syv;

				baund.play();
			}


			//足場20
			drawBox(asibax[12], asibay[12] + camera, 200, -10, 10, Color::white);

			//足場20上の判定
			if (x + 50 > asibax[12] && x < asibax[12] + 200 && y <= asibay[12] && y > asibay[12] - 30)
			{
				y = asibay[12] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場21
			drawBox(asibax[13], asibay[13] + camera, 200, -10, 10, Color::white);

			//足場21上の判定
			if (x + 50 > asibax[13] && x < asibax[13] + 200 && y <= asibay[13] && y > asibay[13] - 30)
			{
				y = asibay[13] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場22
			drawBox(asibax[14], asibay[14] + camera, 200, -10, 10, Color::white);

			//足場22上の判定
			if (x + 50 > asibax[14] && x < asibax[14] + 200 && y <= asibay[14] && y > asibay[14] - 30)
			{
				y = asibay[14] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場23
			drawBox(asibax[15], asibay[15] + camera, 200, -10, 10, Color::white);

			//足場23上の判定
			if (x + 50 > asibax[15] && x < asibax[15] + 200 && y <= asibay[15] && y > asibay[15] - 30)
			{
				y = asibay[15] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場24
			drawBox(asibax[16], asibay[16] + camera, 200, -10, 10, Color::white);

			//足場24上の判定
			if (x + 50 > asibax[16] && x < asibax[16] + 200 && y <= asibay[16] && y > asibay[16] - 30)
			{
				y = asibay[16] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場25
			drawBox(asibax[17], asibay[17] + camera, 200, -10, 10, Color::white);

			//足場25上の判定
			if (x + 50 > asibax[17] && x < asibax[17] + 200 && y <= asibay[17] && y > asibay[17] - 30)
			{
				y = asibay[17] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場26
			drawBox(asibax[18], asibay[18] + camera, 200, -10, 10, Color::white);

			//足場26上の判定
			if (x + 50 > asibax[18] && x < asibax[18] + 200 && y <= asibay[18] && y > asibay[18] - 30)
			{
				y = asibay[18] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場27
			drawBox(asibax[19], asibay[19] + camera, 200, -10, 10, Color::white);

			//足場27上の判定
			if (x + 50 > asibax[19] && x < asibax[19] + 200 && y <= asibay[19] && y > asibay[19] - 30)
			{
				y = asibay[19] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場28
			drawBox(asibax[20], asibay[20] + camera, 200, -10, 10, Color::white);

			//足場28上の判定
			if (x + 50 > asibax[20] && x < asibax[20] + 200 && y <= asibay[20] && y > asibay[20] - 30)
			{
				y = asibay[20] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場29
			drawBox(asibax[21], asibay[21] + camera, 200, -10, 10, Color::white);

			//足場29上の判定
			if (x + 50 > asibax[21] && x < asibax[21] + 200 && y <= asibay[21] && y > asibay[21] - 30)
			{
				y = asibay[21] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場30
			drawBox(asibax[22], asibay[22] + camera, 200, -10, 10, Color::white);

			//足場30上の判定
			if (x + 50 > asibax[22] && x < asibax[22] + 200 && y <= asibay[22] && y > asibay[22] - 30)
			{
				y = asibay[22] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場31
			drawBox(asibax[23], asibay[23] + camera, 200, -10, 10, Color::white);

			//足場31上の判定
			if (x + 50 > asibax[23] && x < asibax[23] + 200 && y <= asibay[23] && y > asibay[23] - 30)
			{
				y = asibay[23] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場32
			drawBox(asibax[24], asibay[24] + camera, 200, -10, 10, Color::white);

			//足場32上の判定
			if (x + 50 > asibax[24] && x < asibax[24] + 200 && y <= asibay[24] && y > asibay[24] - 30)
			{
				y = asibay[24] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場33
			drawBox(asibax[25], asibay[25] + camera, 200, -10, 10, Color::white);

			//足場33上の判定
			if (x + 50 > asibax[25] && x < asibax[25] + 200 && y <= asibay[25] && y > asibay[25] - 30)
			{
				y = asibay[25] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場34
			drawBox(asibax[26], asibay[26] + camera, 200, -10, 10, Color::white);

			//足場34上の判定
			if (x + 50 > asibax[26] && x < asibax[26] + 200 && y <= asibay[26] && y > asibay[26] - 30)
			{
				y = asibay[26] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場35
			drawBox(asibax[27], asibay[27] + camera, 200, -10, 10, Color::white);

			//足場35上の判定
			if (x + 50 > asibax[27] && x < asibax[27] + 200 && y <= asibay[27] && y > asibay[27] - 30)
			{
				y = asibay[27] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場36
			drawBox(asibax[28], asibay[28] + camera, 200, -10, 10, Color::white);

			//足場36上の判定
			if (x + 50 > asibax[28] && x < asibax[28] + 200 && y <= asibay[28] && y > asibay[28] - 30)
			{
				y = asibay[28] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場37
			drawBox(asibax[29], asibay[29] + camera, 200, -10, 10, Color::white);

			//足場37上の判定
			if (x + 50 > asibax[29] && x < asibax[29] + 200 && y <= asibay[29] && y > asibay[29] - 30)
			{
				y = asibay[29] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場38
			drawBox(asibax[30], asibay[30] + camera, 200, -10, 10, Color::white);

			//足場38上の判定
			if (x + 50 > asibax[30] && x < asibax[30] + 200 && y <= asibay[30] && y > asibay[30] - 30)
			{
				y = asibay[30] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場39
			drawBox(asibax[31], asibay[31] + camera, 200, -10, 10, Color::white);

			//足場39上の判定
			if (x + 50 > asibax[31] && x < asibax[31] + 200 && y <= asibay[31] && y > asibay[31] - 30)
			{
				y = asibay[31] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//足場40
			drawBox(asibax[32], asibay[32] + camera, 200, -10, 10, Color::white);

			//足場40上の判定
			if (x + 50 > asibax[32] && x < asibax[32] + 200 && y <= asibay[32] && y > asibay[32] - 30)
			{
				y = asibay[32] + 5;
				yv = syv;

				camera -= 30;

				baund.play();
			}

			//中間足場
			drawBox(500, 6200 + camera, 250, -50, 10, Color::red);

			//中間足場上の判定
			if (x + 50 > 500 && x < 750 && y <= 6200 && y > 6160)
			{
				y = 6205;

				clear.play();

				chukan_flag = true;
				time_flag = false;
			}

			//中間足場横の判定
			//左側面
			if (x + 50 >= 500 && x + 50 <= 520 && y > 6200 && y < 6150)
			{
				x = 450;
				kaf = !kaf;

				baund.play();
			}

			//中間足場下の判定
			if (x + 50 >= 500 && x <= 750 && y > 6100 && y <= 6150)
			{
				syh = false;
			}

			if (syh == false && yv > 0 && y < 6200)
			{
				yv = yv * -1.0f;
				y += yv;
				syh = true;

				baund.play();
			}

			//プレイヤー
			drawFillBox(x, y + camera, 50, 50, Color(0, 1, 0));

			xz[0] = x;
			yz[0] = y;

			for (int i = iz - 1; i > 0; --i)
			{


				drawFillBox(xz[i], yz[i] + camera, 50, 50, Color(0, 1, 0, t[i]));

			}

			for (int i = iz - 1; i > 0; --i)
			{
				xz[i] = xz[i - 1];
				yz[i] = yz[i - 1];
			}



			//チート
			if (env.isPressKey(GLFW_KEY_0) && env.isPressKey(GLFW_KEY_UP))
			{
				y += 10;
				camera -= 10;
				yv = 0;
			}

			if (env.isPressKey('A') && env.isPressKey('S') && env.isPressKey('D') && env.isPressKey('F') && env.isPressKey(GLFW_KEY_ENTER))
			{
				y = 6205;
				x = 550;
				camera = -6205;
				yv = 0;
			}

			env.end();
		}



		//入力の初期化
		env.flushInput();

		//各ステータスの初期化

		clear.stop();

		//プレイヤー座標
		x = 0.0f;
		y = -850.0f;

		//床
		sy = -850.0f;

		//重力
		g = -0.6f;
		syv = 25.0f;
		yv = syv;

		//画面スクロール
		camera = 0.0f;

		syh = true;
		kaf = true;
		chukan_flag = false;
		start_flag = false;

		//足場
		int asiba3x[] = { -750, -400, -100, 350, 550, 450, 100, -300, -550, 0, 100, 550, 0,
			0, 300, 550, 200, -200, 200, -300, 0, 450, 300, -100, -500 };
		int asiba3y[] = { -650, -350, -100, 200, 550, 900, 1250, 1500, 1800, 2100, 2400, 2800, 2900,
			3300, 3600, 4000, 4200, 4200, 4400, 4700, 5000, 5100, 4900, 5000, 5400 };

		bool invisible[13] = {};

		int count = 0;
		int count2 = 0;
		int count3 = 0;
		int count4 = 0;
		int time = 180;
		int time2 = 180;
		int time3 = 1260;
		int time4 = 1260;

		int num = 13;
		int num2 = 14;
		int num3 = 13;
		int num4 = 14;

		asibakazu = 20;

		BGM.play();
		timecount = 0;
		timehyojun = 60;

		for (int i = 0; i < 6; ++i)
		{
			xz[i] = 0;
			yz[i] = -850;
		}

		sg1 = 0;
		sg2 = 0;

		for (int i = 0; i < iz; ++i)
		{
			xz[i] = 0;
			yz[i] = -850;
		}


		//第３ステージ
		while (1)
		{
			env.begin();

			if (!env.isOpen()){ return 0; }

			drawTextureBox(-750, -1000 + camera / 2, 1500, 8192, 0, 0, 1500, 8192, haikei3, Color::white);

			if (time_flag == true)
			{
				//タイム
				timecount++;

				if (timecount == timehyojun)
				{
					stagetime3++;

					timehyojun += 60;
				}

				if (stagetime3 == 60)
				{
					stm3++;

					stagetime3 = 0;
				}
			}

			if (chukan_flag == false)
			{
				if (start_flag == true)
				{
					//重力
					yv += g;
					y += yv;

					if (yv < -25.0f){ yv = -25.0f; }

					if (y > -850)
					{
						if (y < 0)
						{
							sg1 = y / 10;
							sg1 = 85 + sg1;
						}
						else
						{
							sg2 = y / 10;
							sg1 = 85;
						}

						if (sg2 > 560){ sg2 = 560; }
					}

					drawBox(680, 100, 50, 665, 10, Color::white);

					if (sg1 + sg2 > 0)
					{
						drawFillBox(690, 110, 30, sg2 + sg1, Color::green);
					}
					font.size(55);
					font.draw("G", Vec2f(690, 770), Color::red);
					font.draw("S", Vec2f(690, 50), Color::yellow);


				}
				else
				{
					font.size(100);
					font.draw("SPACEで開始", Vec2f(-300, -950), Color::red);

					if (env.isPushKey(GLFW_KEY_SPACE))
					{
						start_flag = true;
						time_flag = true;

					}
				}

				//画面のスクロール
				if (y > 0)
				{
					camera -= yv;
					if (y + camera > 0){ camera--; }
				}
				else
				{
					camera = 0;
				}

				//壁判定
				if (kaf == true)
				{
					x += 10.0f;
				}
				if (x > 700)
				{
					kaf = false;

					baund.play();
				}
				if (kaf == false)
				{
					x -= 10.0;
				}
				if (x < -750)
				{
					kaf = true;

					baund.play();
				}
			}
			else
			{
				x -= 10;

				t3 = to_string(stagetime3);
				tm3 = to_string(stm3);

				if (x < -750)
				{
					BGM.stop();

					font.size(300);
					font.draw(tm3 + ":" + t3, Vec2f(100, 500), Color::red);

					font.size(200);
					font.draw("Stage Clear!!", Vec2f(-600, -100), Color::yellow);
					font.size(100);
					font.draw("SPACEで次へ", Vec2f(-300, -250), Color::green);
					if (env.isPushKey(GLFW_KEY_SPACE)){ break; }

				}

			}

			//キー入力方向転換
			if (env.isPushKey(GLFW_KEY_SPACE)){ kaf = !kaf; }

			//床　当たり判定
			if (y < sy)
			{
				y = sy;
				yv = syv;

				baund.play();
			}

			//床
			drawLine(-750, -850 + camera, 750, -850 + camera, 5, Color::white);


			for (int i = 0; i < 13; i++)
			{
				if (invisible[i] == false)
				{

					//足場１上の判定
					if (x + 50 > asiba3x[i] && x < asiba3x[i] + 200 && y <= asiba3y[i] && y > asiba3y[i] - 50)
					{
						y = asiba3y[i] + 5;
						yv = syv;

						invisible[i] = true;

						baund.play();
					}


					//足場１横の判定
					//左側面
					if (x + 50 >= asiba3x[i] && x + 50 <= asiba3x[i] + 40 && y > asiba3y[i] - 50 && y < asiba3y[i])
					{
						x = asiba3x[i] - 50;
						kaf = !kaf;

						baund.play();
					}

					//右側面
					if (x >= asiba3x[i] + 160 && x <= asiba3x[i] + 200 && y > asiba3y[i] - 50 && y < asiba3y[i])
					{
						x = asiba3x[i] + 200;
						kaf = !kaf;

						baund.play();
					}

					//足場１下の判定
					if (x + 50 >= asiba3x[i] && x <= asiba3x[i] + 200 && y > asiba3y[i] - 100 && y <= asiba3y[i] - 40)
					{
						syh = false;
					}

					if (syh == false && yv > 0 && y < asiba3y[i])
					{
						yv = yv * -1.0f;
						y += yv;
						syh = true;

						baund.play();
					}

					drawBox(asiba3x[i], asiba3y[i] + camera, 200, -50, 10, Color::lime);
				}

				if (y < asiba3y[i] - 100){ invisible[i] = false; }
			}




			//中間
			drawBox(-750, 3000 + camera, 250, -50, 10, Color::white);

			//中間足場上の判定
			if (x + 50 > -750 && x < -500 && y <= 3000 && y > 2950)
			{
				y = 3005;
				yv = syv;

				baund.play();
			}

			//中間足場横の判定
			//右側面
			if (x + 50 >= -500 && x + 50 <= -520 && y > 2950 && y < 3000)
			{
				x = -500;
				kaf = !kaf;

				baund.play();
			}

			//中間足場下の判定
			if (x + 50 >= -750 && x <= -500 && y > 2900 && y <= 2950)
			{
				syh = false;
			}

			if (syh == false && yv > 0 && y < 3000)
			{
				yv = yv * -1.0f;
				y += yv;
				syh = true;

				baund.play();
			}

			count = (count + 1) % 2160;
			if (count == time)
			{
				num++;
				time += 180;
			}

			if (count == 0)
			{
				time = 180;
				num = 13;
			}

			//足場１上の判定
			if (x + 50 > asiba3x[num] && x < asiba3x[num] + 200 && y <= asiba3y[num] && y > asiba3y[num] - 50)
			{
				y = asiba3y[num] + 5;
				yv = syv;

				baund.play();
			}


			//足場１横の判定
			//左側面
			if (x + 50 >= asiba3x[num] && x + 50 <= asiba3x[num] + 40 && y > asiba3y[num] - 50 && y < asiba3y[num])
			{
				x = asiba3x[num] - 50;
				kaf = !kaf;

				baund.play();
			}

			//右側面
			if (x >= asiba3x[num] + 160 && x <= asiba3x[num] + 200 && y > asiba3y[num] - 50 && y < asiba3y[num])
			{
				x = asiba3x[num] + 200;
				kaf = !kaf;

				baund.play();
			}

			//足場１下の判定
			if (x + 50 >= asiba3x[num] && x <= asiba3x[num] + 200 && y > asiba3y[num] - 100 && y <= asiba3y[num] - 40)
			{
				syh = false;
			}

			if (syh == false && yv > 0 && y < asiba3y[num])
			{
				yv = yv * -1.0f;
				y += yv;
				syh = true;

				baund.play();
			}

			drawBox(asiba3x[num], asiba3y[num] + camera, 200, -50, 10, Color::blue);



			count2 = (count2 + 1) % 2160;
			if (count2 == time2)
			{
				num2++;
				time2 += 180;
			}

			if (count2 == 0)
			{
				time2 = 180;
				num2 = 14;
			}

			//足場１上の判定
			if (x + 50 > asiba3x[num2] && x < asiba3x[num2] + 200 && y <= asiba3y[num2] && y > asiba3y[num2] - 50)
			{
				y = asiba3y[num2] + 5;
				yv = syv;

				baund.play();
			}


			//足場１横の判定
			//左側面
			if (x + 50 >= asiba3x[num2] && x + 50 <= asiba3x[num2] + 40 && y > asiba3y[num2] - 50 && y < asiba3y[num2])
			{
				x = asiba3x[num2] - 50;
				kaf = !kaf;

				baund.play();
			}

			//右側面
			if (x >= asiba3x[num2] + 160 && x <= asiba3x[num2] + 200 && y > asiba3y[num2] - 50 && y < asiba3y[num2])
			{
				x = asiba3x[num2] + 200;
				kaf = !kaf;

				baund.play();
			}

			//足場１下の判定
			if (x + 50 >= asiba3x[num2] && x <= asiba3x[num2] + 200 && y > asiba3y[num2] - 100 && y <= asiba3y[num2] - 40)
			{
				syh = false;
			}

			if (syh == false && yv > 0 && y < asiba3y[num2])
			{
				yv = yv * -1.0f;
				y += yv;
				syh = true;

				baund.play();
			}

			drawBox(asiba3x[num2], asiba3y[num2] + camera, 200, -50, 10, Color::blue);

			count3 = (count3 + 1) % 3240;
			if (count3 == time3)
			{
				num3++;
				time3 += 180;
			}

			if (count3 == 0)
			{
				time3 = 1260;
				num3 = 13;
				count3 = 1080;
			}

			if (count3 >= 1080)
			{

				//足場１上の判定
				if (x + 50 > asiba3x[num3] && x < asiba3x[num3] + 200 && y <= asiba3y[num3] && y > asiba3y[num3] - 50)
				{
					y = asiba3y[num3] + 5;
					yv = syv;

					baund.play();
				}


				//足場１横の判定
				//左側面
				if (x + 50 >= asiba3x[num3] && x + 50 <= asiba3x[num3] + 40 && y > asiba3y[num3] - 50 && y < asiba3y[num3])
				{
					x = asiba3x[num3] - 50;
					kaf = !kaf;

					baund.play();
				}

				//右側面
				if (x >= asiba3x[num3] + 160 && x <= asiba3x[num3] + 200 && y > asiba3y[num3] - 50 && y < asiba3y[num3])
				{
					x = asiba3x[num3] + 200;
					kaf = !kaf;

					baund.play();
				}

				//足場１下の判定
				if (x + 50 >= asiba3x[num3] && x <= asiba3x[num3] + 200 && y > asiba3y[num3] - 100 && y <= asiba3y[num3] - 40)
				{
					syh = false;
				}

				if (syh == false && yv > 0 && y < asiba3y[num3])
				{
					yv = yv * -1.0f;
					y += yv;
					syh = true;

					baund.play();
				}

				drawBox(asiba3x[num3], asiba3y[num3] + camera, 200, -50, 10, Color::blue);

			}

			count4 = (count4 + 1) % 3240;
			if (count4 == time4)
			{
				num4++;
				time4 += 180;
			}

			if (count4 == 0)
			{
				time4 = 1260;
				num4 = 14;
				count4 = 1080;
			}


			if (count4 >= 1080)
			{

				//足場１上の判定
				if (x + 50 > asiba3x[num4] && x < asiba3x[num4] + 200 && y <= asiba3y[num4] && y > asiba3y[num4] - 50)
				{
					y = asiba3y[num4] + 5;
					yv = syv;

					baund.play();
				}


				//足場１横の判定
				//左側面
				if (x + 50 >= asiba3x[num4] && x + 50 <= asiba3x[num4] + 40 && y > asiba3y[num4] - 50 && y < asiba3y[num4])
				{
					x = asiba3x[num4] - 50;
					kaf = !kaf;

					baund.play();
				}

				//右側面
				if (x >= asiba3x[num4] + 160 && x <= asiba3x[num4] + 200 && y > asiba3y[num4] - 50 && y < asiba3y[num4])
				{
					x = asiba3x[num4] + 200;
					kaf = !kaf;

					baund.play();
				}

				//足場１下の判定
				if (x + 50 >= asiba3x[num4] && x <= asiba3x[num4] + 200 && y > asiba3y[num4] - 100 && y <= asiba3y[num4] - 40)
				{
					syh = false;
				}

				if (syh == false && yv > 0 && y < asiba3y[num4])
				{
					yv = yv * -1.0f;
					y += yv;
					syh = true;

					baund.play();
				}

				drawBox(asiba3x[num4], asiba3y[num4] + camera, 200, -50, 10, Color::blue);
			}

			//中間
			drawBox(-750, 5800 + camera, 250, -50, 10, Color::red);

			//中間足場上の判定
			if (x + 50 > -750 && x < -500 && y <= 5800 && y > 5750)
			{
				y = 5805;
				yv = syv;

				chukan_flag = true;
				time_flag = false;
				clear.play();
			}

			//中間足場横の判定
			//右側面
			if (x + 50 >= -500 && x + 50 <= -520 && y > 5750 && y < 5800)
			{
				x = -500;
				kaf = !kaf;

				baund.play();
			}

			//中間足場下の判定
			if (x + 50 >= -750 && x <= -500 && y > 5700 && y <= 5750)
			{
				syh = false;
			}

			if (syh == false && yv > 0 && y < 5800)
			{
				yv = yv * -1.0f;
				y += yv;
				syh = true;

				baund.play();
			}



			//チート
			if (env.isPressKey(GLFW_KEY_0) && env.isPressKey(GLFW_KEY_UP))
			{
				y += 10;
				camera -= 10;
				yv = 0;
			}

			if (env.isPressKey('A') && env.isPressKey('S') && env.isPressKey('D') && env.isPressKey('F') && env.isPressKey(GLFW_KEY_ENTER))
			{
				y = 5805;
				x = -600;
				camera = -6205;
				yv = 0;
			}

			//プレイヤー
			drawFillBox(x, y + camera, 50, 50, Color(0, 1, 0));

			xz[0] = x;
			yz[0] = y;

			for (int i = iz - 1; i > 0; --i)
			{


				drawFillBox(xz[i], yz[i] + camera, 50, 50, Color(0, 1, 0, t[i]));

			}

			for (int i = iz - 1; i > 0; --i)
			{
				xz[i] = xz[i - 1];
				yz[i] = yz[i - 1];
			}



			env.end();
		}


		//入力の初期化
		env.flushInput();

		//各ステータスの初期化

		clear.stop();

		//プレイヤー座標
		x = 0.0f;
		y = -850.0f;

		//床
		sy = -850.0f;

		//重力
		g = -0.6f;
		syv = 25.0f;
		yv = syv;

		//画面スクロール
		camera = 0.0f;

		syh = true;
		kaf = true;
		chukan_flag = false;
		start_flag = false;

		//足場(２ステージ)
		float asiba2x[] = { 0, 200, 100, -300, -700, 500, 350, 0,
			300, -200, -300, 400,
			0, 100, 300, 0 };
		float asiba2y[] = { -450, -150, 100, 500, 750, 1050, 1500, 1800,
			2000, 3000, 4100, 5100,
			2400, 3500, 4600, 5500 };

		//足場移動変数
		bool yokoidou_flag[] = { 1, 0, 1, 1, 0, 1, 0, 0,
			1, 1, 1, 0,
			0, 1, 1, 0 };
		int asixv[17] = {};
		int asibasokudo[] = { 5, 7, 2, 6, 4, 1, 7, 8,
			5, 2, 9, 5,
			1, 3, 7, 5 };
		//足場の数
		int asibakazu = 16;

		BGM.play();

		timecount = 0;
		timehyojun = 60;

		for (int i = 0; i < 6; ++i)
		{
			xz[i] = 0;
			yz[i] = -850;
		}

		sg1 = 0;
		sg2 = 0;

		for (int i = 0; i < iz; ++i)
		{
			xz[i] = 0;
			yz[i] = -850;
		}


		//第２ステージ
		while (1)
		{
			env.begin();

			if (!env.isOpen()){ return 0; }

			drawTextureBox(-750, -1000 + camera / 2, 1500, 8192, 0, 0, 1500, 8192, haikei3, Color::white);

			if (time_flag == true)
			{
				//タイム
				timecount++;

				if (timecount == timehyojun)
				{
					stagetime2++;

					timehyojun += 60;
				}

				if (stagetime2 == 60)
				{
					stm2++;

					stagetime2 = 0;
				}
			}

			if (chukan_flag == false)
			{
				if (start_flag == true)
				{
					//重力
					yv += g;
					y += yv;

					if (yv < -25.0f){ yv = -25.0f; }

					if (y > -850)
					{
						if (y < 0)
						{
							sg1 = y / 10;
							sg1 = 85 + sg1;
						}
						else
						{
							sg2 = y / 10;
							sg1 = 85;
						}

						if (sg2 > 540){ sg2 = 540; }
					}

					drawBox(680, 100, 50, 645, 10, Color::white);

					if (sg1 + sg2 > 0)
					{
						drawFillBox(690, 110, 30, sg2 + sg1, Color::green);
					}
					font.size(55);
					font.draw("G", Vec2f(690, 750), Color::red);
					font.draw("S", Vec2f(690, 50), Color::yellow);


				}
				else
				{
					font.size(100);
					font.draw("SPACEで開始", Vec2f(-300, -950), Color::red);

					if (env.isPushKey(GLFW_KEY_SPACE))
					{
						start_flag = true;
						time_flag = true;
					}
				}

				//画面のスクロール
				if (y > 0)
				{
					camera -= yv;
					if (y + camera > 0){ camera--; }
				}
				else
				{
					camera = 0;
				}

				//壁判定
				if (kaf == true)
				{
					x += 10.0f;
				}
				if (x > 700)
				{
					kaf = false;

					baund.play();
				}
				if (kaf == false)
				{
					x -= 10.0;
				}
				if (x < -750)
				{
					kaf = true;

					baund.play();
				}
			}
			else
			{
				x -= 10;

				t2 = to_string(stagetime2);
				tm2 = to_string(stm2);

				if (x < -750)
				{
					BGM.stop();

					font.size(300);
					font.draw(tm2 + ":" + t2, Vec2f(100, 500), Color::red);

					font.size(200);
					font.draw("Stage Clear!!", Vec2f(-600, -100), Color::yellow);
					font.size(100);
					font.draw("SPACEで結果発表へ", Vec2f(-300, -250), Color::green);
					if (env.isPushKey(GLFW_KEY_SPACE)){ break; }
				}

			}

			//キー入力方向転換
			if (env.isPushKey(GLFW_KEY_SPACE)){ kaf = !kaf; }

			//床　当たり判定
			if (y < sy)
			{
				y = sy;
				yv = syv;

				baund.play();
			}

			//床
			drawLine(-750, -850 + camera, 750, -850 + camera, 5, Color::white);

			for (int i = 0; i < asibakazu - 8; i++)
			{
				//足場１
				drawBox(asiba2x[i] + asixv[i], asiba2y[i] + camera, 200, -50, 10, Color::yellow);

				//横移動
				if (yokoidou_flag[i] == true){ asixv[i] += asibasokudo[i]; }
				else{ asixv[i] -= asibasokudo[i]; }
				if (asiba2x[i] + asixv[i] >= 550 || asiba2x[i] + asixv[i] <= -750){ yokoidou_flag[i] = !yokoidou_flag[i]; }

				//足場１上の判定
				if (x + 50 > asiba2x[i] + asixv[i] && x < asiba2x[i] + asixv[i] + 200 && y <= asiba2y[i] && y > asiba2y[i] - 50)
				{
					y = asiba2y[i] + 5;
					yv = syv;

					baund.play();
				}


				//足場１横の判定
				//左側面
				if (x + 50 >= asiba2x[i] + asixv[i] && x + 20 <= asiba2x[i] + asixv[i] + 40 && y > asiba2y[i] - 50 && y < asiba2y[i])
				{
					x = asiba2x[i] + asixv[i] - 50;
					kaf = !kaf;

					baund.play();
				}

				//右側面
				if (x >= asiba2x[i] + asixv[i] + 160 && x <= asiba2x[i] + asixv[i] + 180 && y > asiba2y[i] - 50 && y < asiba2y[i])
				{
					x = asiba2x[i] + asixv[i] + 200;
					kaf = !kaf;

					baund.play();
				}

				//足場１下の判定
				if (x + 50 >= asiba2x[i] + asixv[i] && x <= asiba2x[i] + asixv[i] + 200 && y > asiba2y[i] - 100 && y <= asiba2y[i] - 40)
				{
					syh = false;
				}

				if (syh == false && yv > 0 && y < asiba2y[i])
				{
					yv = yv * -1.0f;
					y += yv;
					syh = true;

					baund.play();
				}
			}


			for (int i = 8; i < asibakazu - 4; i++)
			{
				//足場１
				drawBox(asiba2x[i] + asixv[i], asiba2y[i] + asixv[i] + camera, 200, -50, 10, Color::yellow);

				//横移動
				if (yokoidou_flag[i] == true){ asixv[i] += asibasokudo[i]; }
				else{ asixv[i] -= asibasokudo[i]; }
				if (asiba2x[i] + asixv[i] >= asiba2x[i] + 200 || asiba2x[i] + asixv[i] <= asiba2x[i] - 200){ yokoidou_flag[i] = !yokoidou_flag[i]; }

				//足場１上の判定
				if (x + 50 > asiba2x[i] + asixv[i] && x < asiba2x[i] + asixv[i] + 200 && y <= asiba2y[i] + asixv[i] && y > asiba2y[i] + asixv[i] - 50)
				{
					y = asiba2y[i] + asixv[i] + 5;
					yv = syv;

					baund.play();
				}

				//足場１横の判定
				//左側面
				if (x + 50 >= asiba2x[i] + asixv[i] && x + 50 <= asiba2x[i] + asixv[i] + 40 && y > asiba2y[i] + asixv[i] - 50 && y < asiba2y[i] + asixv[i])
				{
					x = asiba2x[i] + asixv[i] - 50;
					kaf = !kaf;

					baund.play();
				}

				//右側面
				if (x >= asiba2x[i] + asixv[i] + 160 && x <= asiba2x[i] + asixv[i] + 200 && y > asiba2y[i] + asixv[i] - 50 && y < asiba2y[i] + asixv[i])
				{
					x = asiba2x[i] + asixv[i] + 200;
					kaf = !kaf;

					baund.play();
				}

				//足場１下の判定
				if (x + 50 >= asiba2x[i] + asixv[i] && x <= asiba2x[i] + asixv[i] + 200 && y > asiba2y[i] + asixv[i] - 100 && y <= asiba2y[i] + asixv[i] - 40)
				{
					syh = false;
				}

				if (syh == false && yv > 0 && y < asiba2y[i] + asixv[i])
				{
					yv = yv * -1.0f;
					y += yv;
					syh = true;

					baund.play();
				}
			}

			for (int i = 12; i < asibakazu; i++)
			{
				//足場１
				drawBox(asiba2x[i] + asixv[i], asiba2y[i] + asixv[i] + camera, 200, -50, 10, Color::yellow);

				//横移動
				if (yokoidou_flag[i] == true){ asixv[i] -= asibasokudo[i]; }
				else{ asixv[i] += asibasokudo[i]; }
				if (asiba2x[i] + asixv[i] >= asiba2x[i] + 200 || asiba2x[i] + asixv[i] <= asiba2x[i] - 200){ yokoidou_flag[i] = !yokoidou_flag[i]; }


				//足場１上の判定
				if (x + 50 > asiba2x[i] + asixv[i] && x < asiba2x[i] + asixv[i] + 200 && y <= asiba2y[i] + asixv[i] && y > asiba2y[i] + asixv[i] - 50)
				{
					y = asiba2y[i] + asixv[i] + 5;
					yv = syv;

					baund.play();
				}

				//足場１横の判定
				//左側面
				if (x + 50 >= asiba2x[i] + asixv[i] && x + 50 <= asiba2x[i] + asixv[i] + 40 && y > asiba2y[i] + asixv[i] - 50 && y < asiba2y[i] + asixv[i])
				{
					x = asiba2x[i] + asixv[i] - 50;
					kaf = !kaf;

					baund.play();
				}

				//右側面
				if (x >= asiba2x[i] + asixv[i] + 160 && x <= asiba2x[i] + asixv[i] + 200 && y > asiba2y[i] + asixv[i] - 50 && y < asiba2y[i] + asixv[i])
				{
					x = asiba2x[i] + asixv[i] + 200;
					kaf = !kaf;

					baund.play();
				}

				//足場１下の判定
				if (x + 50 >= asiba2x[i] + asixv[i] && x <= asiba2x[i] + asixv[i] + 200 && y > asiba2y[i] + asixv[i] - 100 && y <= asiba2y[i] + asixv[i] - 30)
				{
					syh = false;
				}

				if (syh == false && yv > 0 && y < asiba2y[i] + asixv[i])
				{
					yv = yv * -1.0f;
					y += yv;
					syh = true;

					baund.play();
				}
			}

			drawBox(300, 4000 + camera, 250, -50, 10, Color::white);

			//中間足場上の判定
			if (x + 50 > 300 && x < 550 && y <= 4000 && y > 3950)
			{
				y = 4005;

				yv = 25;

				baund.play();

			}

			//中間足場横の判定
			//右側面
			if (x + 50 >= 520 && x + 50 <= 550 && y > 3950 && y < 4000)
			{
				x = 550;
				kaf = !kaf;

				baund.play();
			}

			if (x + 50 >= 300 && x + 50 <= 330 && y > 3950 && y < 4000)
			{
				x = 250;
				kaf = !kaf;

				baund.play();
			}

			//中間足場下の判定
			if (x + 50 >= 300 && x <= 550 && y > 3900 && y <= 3950)
			{
				syh = false;
			}

			if (syh == false && yv > 0 && y < 4000)
			{
				yv = yv * -1.0f;
				y += yv;
				syh = true;

				baund.play();
			}




			//ゴール
			drawBox(-750, 5600 + camera, 250, -50, 10, Color::red);

			//中間足場上の判定
			if (x + 50 > -750 && x < -500 && y <= 5600 && y > 5560)
			{
				y = 5605;

				clear.play();

				chukan_flag = true;
				time_flag = false;
			}

			//中間足場横の判定
			//右側面
			if (x + 50 >= -500 && x + 50 <= -520 && y > 5550 && y < 5600)
			{
				x = -500;
				kaf = !kaf;

				baund.play();
			}

			//中間足場下の判定
			if (x + 50 >= -750 && x <= -500 && y > 5500 && y <= 5550)
			{
				syh = false;
			}

			if (syh == false && yv > 0 && y < 5600)
			{
				yv = yv * -1.0f;
				y += yv;
				syh = true;

				baund.play();
			}


			//チート
			if (env.isPressKey(GLFW_KEY_0) && env.isPressKey(GLFW_KEY_UP))
			{
				y += 10;
				camera -= 10;
				yv = 0;
			}

			if (env.isPressKey('A') && env.isPressKey('S') && env.isPressKey('D') && env.isPressKey('F') && env.isPressKey(GLFW_KEY_ENTER))
			{
				y = 5605;
				x = -550;
				camera = -5605;
				yv = 0;
			}

			//プレイヤー
			drawFillBox(x, y + camera, 50, 50, Color(0, 1, 0));

			xz[0] = x;
			yz[0] = y;

			for (int i = iz - 1; i > 0; --i)
			{

				drawFillBox(xz[i], yz[i] + camera, 50, 50, Color(0, 1, 0, t[i]));

			}

			for (int i = iz - 1; i > 0; --i)
			{
				xz[i] = xz[i - 1];
				yz[i] = yz[i - 1];
			}



			env.end();
		}

		//入力の初期化
		env.flushInput();

		clear.stop();

		int s = 0;
		bool retry = true;

		stagetimesogo = stagetime1 + stagetime2 + stagetime3;
		if (stagetimesogo >= 60)
		{
			stagetimesogo -= 60;
			s++;
		}
		stms = stm1 + stm2 + stm3 + s;

		Color color2 = Color::white;
		Color color3 = Color::white;

		while (1)
		{
			env.begin();

			if (!env.isOpen()){ return 0; }

			Vec2f pos = env.mousePosition();

			drawTextureBox(-750, -1000, 1500, 2000, 0, 0, 2048, 2048, haikei2, Color::white);

			string ts = to_string(stagetimesogo);
			string tsm = to_string(stms);

			font.size(300);
			font.draw("TOTAL", Vec2f(-400, 500), Color::red);
			font.draw(tsm + ":" + ts, Vec2f(-250, 0), Color::yellow);

			font.size(200);
			font.draw("Retry?", Vec2f(-275, -400), Color::white);
			font.draw("Y", Vec2f(-325, -750), color2);
			font.draw("     N", Vec2f(-325, -750), color3);
			font.draw("  or ", Vec2f(-325, -750), Color::white);
			font.size(100);
			font.draw("※左クリック or PressKey", Vec2f(-625, -900), Color::white);

			drawBox(-365, -775, 200, 200, 10, color2);
			drawBox(125, -775, 200, 200, 10, color3);


			if (env.isPushKey('Y')){ break; }
			if (pos.x() >= -365 && pos.x() <= -165 && pos.y() >= -775 && pos.y() <= -575)
			{
				color2 = Color::blue;

				if (env.isPushButton(Mouse::LEFT)){ break; }
				
			}
			else{ color2 = Color::white; }


			if (env.isPushKey('N'))
			{
				retry = false;
				break;
			}
			if (pos.x() >= 125 && pos.x() <= 325 && pos.y() >= -775 && pos.y() <= -575)
			{
				color3 = Color::blue;

				if (env.isPushButton(Mouse::LEFT))
				{
					retry = false;
					break;
				}
				
			}
			else{ color3 = Color::white; }

			env.end();
		}
		if (retry == false){ break; }

		env.end();
	}
}