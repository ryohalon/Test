#include "tutorial.h"

void Tutorial(int& scene, Font& font)
{
	//画像呼び込み
	Texture floor_image("res/image/floor.png");
	Texture dog_image("res/image/dog.png");
	Texture skeleton_image("res/image/skeleton.png");

	//背景画像
	Random rand;
	rand.setSeed(std::time(nullptr));
	int bg_count = rand(0, 5);
	Texture bg;
	Texture bg2;
	Vec2f bg_pos = Vec2f(-WIDTH / 2, -HEIGHT / 2);
	Vec2f bg2_pos = Vec2f(WIDTH * 3 / 2, -HEIGHT / 2);

	switch (bg_count)
	{
	case 0:
		bg = Texture("res/image/gm_bg.png");
		bg2 = Texture("res/image/gm_bg.png");
		break;

	case 1:
		bg = Texture("res/image/gm_bg2.png");
		bg2 = Texture("res/image/gm_bg2.png");
		break;

	case 2:
		bg = Texture("res/image/gm_bg3.png");
		bg2 = Texture("res/image/gm_bg3.png");
		break;

	case 3:
		bg = Texture("res/image/gm_bg4.png");
		bg2 = Texture("res/image/gm_bg4.png");
		break;

	case 4:
		bg = Texture("res/image/gm_bg5.png");
		bg2 = Texture("res/image/gm_bg5.png");
		break;

	case 5:
		bg = Texture("res/image/gm_bg6.png");
		bg2 = Texture("res/image/gm_bg6.png");
		break;
	}


	//サウンド
	Media skeletonjump("res/sound/skeletonjump.wav");
	Media dogjump("res/sound/dogjump.wav");
	Media dogdash("res/sound/dogdash.wav");
	Media skeletondash("res/sound/skeletondash.wav");

	//決定音
	Media decision("res/sound/decision.wav");

	//ポーズ
	Color color1 = Color::red;
	Color color2 = Color::white;

	int count = 0;

	//for文で使う
	int i;
	int k;

	//アニメーション
	int index = 4;
	int index2 = 0;
	int animation_count = 0;

	//プレイヤー
	Player skeleton, dog;

	//プレイヤー (ガイコツ)
	skeleton.pos.x() = 0.0f;
	skeleton.pos.y() = -160.0f;
	skeleton.size.x() = 64.0f;
	skeleton.size.y() = 80.0f;
	skeleton.vector.x() = 15.0f;
	skeleton.vector.y() = 0.0f;
	skeleton.jumpflag = false;
	skeleton.speedupflag = false;

	//プレイヤー (犬)
	dog.pos.x() = -700.0f;
	dog.pos.y() = -160.0;
	dog.size.x() = 128.0f;
	dog.size.y() = 64.0f;
	dog.vector.x() = 14.0f;
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
	int mapchip[Geography::HEIGHTNUM][Geography::WIDTHNUM] =
	{														   //20																					     //50
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
	float mapchip_pos_x[Geography::HEIGHTNUM][Geography::WIDTHNUM];
	float mapchip_pos_y[Geography::HEIGHTNUM][Geography::WIDTHNUM];
	float map_pos_x = -2048.0f;
	float map_pos_y = 352.0f;
	float map_size_xy = 128.0f;
	for (i = 0; i < Geography::HEIGHTNUM; ++i)
	{
		for (k = 0; k < Geography::WIDTHNUM; ++k)
		{
			mapchip_pos_x[i][k] = map_pos_x;
			mapchip_pos_y[i][k] = map_pos_y;

			map_pos_x += map_size_xy;
		}

		map_pos_x = -2048.0f;
		map_pos_y -= map_size_xy;
	}


	/////////////////////////////////////////////////////////////////////////////////////////////
	//チュートリアルスタート前
	Vec2f size = Vec2f(2048.0f, 512.0f);

	while (size.y() != 0.0f)
	{
		if (!env.isOpen()){ exit(0); }

		size.y() -= 8.0f;

		env.begin();

		drawTextureBox(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, bg);

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

				if (mapchip[i][k] == FACE)
				{
					drawTextureBox(mapchip_pos_x[i][k] - status.camera, mapchip_pos_y[i][k], map_size_xy, map_size_xy, 0, 0, 192, 64, floor_image);
				}
			}
		}

		//犬
		drawTextureBox(dog.pos.x() - status.camera, dog.pos.y(), dog.size.x(), dog.size.y(), 128 * index, 0, 100, 50, dog_image);

		//ガイコツ
		drawTextureBox(skeleton.pos.x() - status.camera, skeleton.pos.y(), skeleton.size.x(), skeleton.size.y(), 128 * index2 + 30, 0, 98, 230, skeleton_image);

		drawFillBox(-WIDTH / 2, -HEIGHT / 2, size.x(), size.y(), Color::black);
		drawFillBox(-WIDTH / 2, HEIGHT / 2, size.x(), -size.y(), Color::black);

		env.end();
	}




	/////////////////////////////////////////////////////////////////////////////////////////////
	//チュートリアル
	while (scene == TUTORIAL || decision.isPlaying())
	{
		if (!env.isOpen()){ exit(0); }

		env.begin();

		//重力
		Gravity(skeleton, dog, status);

		//速度、ジャンプ
		Move(skeletonjump, dogjump, dogdash, skeletondash, dog, skeleton, status);

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

		//リスタート
		Restart(dog, skeleton, status);

		//無限生成
		Repeat(skeleton, dog, status, mapchip_pos_x[0][314], bg_pos, bg2_pos);

		/////////////////////////////////////////////////////////////////////////
		//ポーズ
		Pose(font, scene, status, skeleton, dog, color1, color2, count, decision);

		/////////////////////////////////////////////////////////////////////////
		//アニメーション
		Animation(index, index2, animation_count);


		////////////////////////////////////////////////////////////////////////
		//背景ループ
		////////////////////////////////////////////////////////////////////////
		Bg(bg_pos, bg2_pos, status);


		///////////////////////////////////////////////////////////////////////
		//表示処理

		drawTextureBox(bg_pos.x() - status.camera, bg_pos.y(), WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, bg);
		drawTextureBox(bg2_pos.x() - status.camera, bg2_pos.y(), -WIDTH, HEIGHT, 0, 0, WIDTH, HEIGHT, bg2);

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

				if (mapchip[i][k] == FACE)
				{
					drawTextureBox(mapchip_pos_x[i][k] - status.camera, mapchip_pos_y[i][k], map_size_xy, map_size_xy, 0, 0, 192, 64, floor_image);
				}
			}
		}

		//犬
		font.draw("A / ダッシュ", Vec2f(dog.pos.x() + dog.size.x() / 2 - font.drawSize("A / ダッシュ").x() / 2 - status.camera,
			dog.pos.y() + dog.size.y() + font.drawSize("A / ダッシュ").y() * 2),
			Color::lime);
		font.draw("S / ジャンプ", Vec2f(dog.pos.x() + dog.size.x() / 2 - font.drawSize("A / ダッシュ").x() / 2 - status.camera,
			dog.pos.y() + dog.size.y() + font.drawSize("A / ダッシュ").y()),
			Color::lime);

		drawTextureBox(dog.pos.x() - status.camera, dog.pos.y(), dog.size.x(), dog.size.y(), 128 * index, 0, 100, 50, dog_image);

		//ガイコツ
		font.draw("K / ダッシュ", Vec2f(skeleton.pos.x() + skeleton.size.x() / 2 - font.drawSize("K / ダッシュ").x() / 2 - status.camera,
			skeleton.pos.y() + skeleton.size.y() + font.drawSize("K / ダッシュ").y() * 2),
			Color::red);
		font.draw("L / ジャンプ", Vec2f(skeleton.pos.x() + skeleton.size.x() / 2 - font.drawSize("L / ジャンプ").x() / 2 - status.camera,
			skeleton.pos.y() + skeleton.size.y() + font.drawSize("L / ジャンプ").y()),
			Color::red);

		
		font.draw("SPACE / ポーズ", Vec2f(WIDTH / 2 - font.drawSize("SPACE / ポーズ").x(), -HEIGHT / 2), Color::yellow);


		drawTextureBox(skeleton.pos.x() - status.camera, skeleton.pos.y(), skeleton.size.x(), skeleton.size.y(), 128 * index2 + 30, 0, 98, 230, skeleton_image);

		//ポーズ
		if (status.pose == true)
		{
			drawFillBox(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT, Color(0.0f, 0.0f, 0.0f, 0.7f));

			font.draw("タイトル", Vec2f(0, 80) - font.drawSize("タイトル") / 2, color1);
			font.draw("再開", Vec2f(0, -80) - font.drawSize("再開") / 2, color2);
		}


		env.end();
	}

	env.flushInput();
}

void Restart(Player& dog, Player& skeleton, Status& status)
{
	if (dog.pos.x() + dog.size.x() - status.camera < -WIDTH / 2 ||
		dog.pos.y() < -(HEIGHT / 2) ||
		skeleton.pos.y() < -(HEIGHT / 2) ||
		skeleton.pos.x() <= dog.pos.x() + dog.size.x())
	{
		skeleton.pos = Vec2f(status.camera, 0.0f);
		skeleton.vector = Vec2f(15.0f, -15.0f);
		dog.pos = Vec2f(status.camera - 700.0f, 0.0f);
		dog.vector = Vec2f(14.0f, -15.0f);
		skeleton.speedupflag = false;
		skeleton.jumpflag = false;
		dog.speedupflag = false;
		dog.jumpflag = false;
	}
}