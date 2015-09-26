#include "gamemain.h"


void GameMain(Font font, int& scene, int& score, int& hiscore, int& bone, int ranking[6], char name[3])
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
	Media BGM("res/sound/BGM.wav");
	Media skeletonjump("res/sound/skeletonjump.wav");
	Media dogjump("res/sound/dogjump.wav");
	Media dogdash("res/sound/dogdash.wav");
	Media skeletondash("res/sound/skeletondash.wav");

	//決定音
	Media decision("res/sound/decision.wav");

	BGM.gain(0.2f);
	dogjump.gain(0.3f);
	dogdash.gain(0.2f);

	//フォント
	std::string score_display;
	std::string hiscore_display;

	//ポーズ
	Color color1 = Color::red;
	Color color2 = Color::white;

	int pose_count = 0;

	//アニメーション
	int index = 4;
	int index2 = 0;
	int animation_count = 0;

	//for文で使う
	int i;
	int k;

	//プレイヤー間の距離
	float players_distance = 0.0f;

	//リザルト
	int count = 0;
	float alpha = 0.0f;
	int result_branch;

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
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
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



	//////////////////////////////////////////////////////////////////////////
	//スタート前
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

	int time = 0;
	Vec2f start = Vec2f(-1024.0f, 0.0f);

	while (start.x() < 2048.0f)
	{
		if (start.x() < -250.0f){ start.x() += 50.0f; }
		if (start.x() >= -250.0f && start.x() < 0.0f){ start.x() += 5.0f; }
		if (start.x() >= 0.0f){ start.x() += 50.0f; }

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

		font.draw("start", Vec2f(start.x(), start.y()), Color::red);

		env.end();
	}


	score = 0;
	BGM.play();
	BGM.looping(true);



	///////////////////////////////////////////////////////////////////////
	//ゲーム本編
	while (scene == MULTI_GAMEMAIN || scene == RESULT || decision.isPlaying())

	{
		if (!env.isOpen()){ exit(0); }


		if (scene == MULTI_GAMEMAIN)
		{

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

			//ポーズ
			Pose(font, scene, status, skeleton, dog, color1, color2, pose_count, decision);

			//げーむおーばー
			GameOver(skeleton, dog, status, scene, result_branch, BGM);

			Repeat(skeleton, dog, status, mapchip_pos_x[0][314], bg_pos, bg2_pos);

			//スコア
			Score(score, hiscore, score_display, hiscore_display, players_distance, skeleton, dog, status.pose);


			////////////////////////////////////////////////////////////////////////
			//背景ループ
			////////////////////////////////////////////////////////////////////////
			Bg(bg_pos, bg2_pos, status);


			Cheat(score, scene, skeleton, dog, status);

		}


		/////////////////////////////////////////////////////////////////////////
		//アニメーション
		/////////////////////////////////////////////////////////////////////////
		Animation(index, index2, animation_count);






		env.begin();

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
		drawTextureBox(dog.pos.x() - status.camera, dog.pos.y(), dog.size.x(), dog.size.y(), 128 * index, 0, 100, 50, dog_image);

		//ガイコツ
		drawTextureBox(skeleton.pos.x() - status.camera, skeleton.pos.y(), skeleton.size.x(), skeleton.size.y(), 128 * index2 + 30, 0, 98, 230, skeleton_image);

		//スコア
		font.draw(score_display + "m", Vec2f(0.0f, 460.0f) - font.drawSize(score_display + "m") / 2, Color::white);
		font.draw(hiscore_display + "m",
			Vec2f(1010.0f - font.drawSize(hiscore_display + "m").x(), 460.0f - font.drawSize(hiscore_display + "m").y() / 2), Color::red);


		//ポーズ
		if (status.pose == true)
		{
			drawFillBox(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT, Color(0.0f, 0.0f, 0.0f, 0.7f));

			font.draw("タイトル", Vec2f(0, 140) - font.drawSize("タイトル") / 2, color1);
			font.draw("再開", Vec2f(0, -140) - font.drawSize("再開") / 2, color2);
		}

		if (scene == RESULT && count < 60)
		{
			count += 1;
			alpha += 0.02f;

			drawFillBox(-(WIDTH / 2), -(HEIGHT / 2), WIDTH, HEIGHT, Color(0.0, 0.0, 0.0, alpha));
		}

		env.end();


		if (scene == RESULT && count == 60)
		{
			Result(scene, result_branch, score, hiscore, players_distance, font, ranking, name);
		}

	}
}

void Score(int& score, int& hiscore, std::string& score_display, std::string& hiscore_display, float& players_distance, Player& skeleton, Player& dog, bool& pose)
{
	if (pose == false)
	{
		score += 1;

		score_display = std::to_string(score);
		hiscore_display = std::to_string(hiscore);

		players_distance += skeleton.pos.x() - dog.pos.x() + dog.size.x();
	}
}

void Gravity(Player& skeleton, Player& dog, Status& status)
{
	skeleton.vector.y() -= status.gravity;
	skeleton.pos.y() += skeleton.vector.y();

	dog.vector.y() -= status.gravity;
	dog.pos.y() += dog.vector.y();

	if (skeleton.vector.y() < -15.0f){ skeleton.vector.y() = -15.0f; }
	if (dog.vector.y() < -15.0f){ dog.vector.y() = -15.0f; }

}

void Move(Media skeletonjump, Media dogjump, Media dogdash, Media skeletondash, Player& dog, Player& skeleton, Status& status)
{
	SpeedUp(skeleton, dog, dogdash, skeletondash);

	dog.pos.x() += dog.vector.x();
	skeleton.pos.x() += skeleton.vector.x();

	status.camera += status.scroll;

	Jump(skeletonjump, dogjump, dog, skeleton, status);
}

void SpeedUp(Player& skeleton, Player& dog, Media dogdash, Media skeletondash)
{
	if (skeleton.speedupflag == false)
	{
		if (env.isPushKey('K'))
		{
			skeletondash.play();

			skeleton.speedupflag = true;

			skeleton.vector.x() = 40.0f;
		}
	}

	if (skeleton.speedupflag == true)
	{
		skeleton.vector.x() -= 1.0f;

		if (skeleton.vector.x() < 15.0f)
		{
			skeleton.vector.x() = 15.0f;

			skeleton.speedupflag = false;
		}
	}

	if (dog.speedupflag == false)
	{
		if (env.isPushKey('A'))
		{
			dogdash.play();

			dog.speedupflag = true;

			dog.vector.x() = 44.0f;
		}
	}

	if (dog.speedupflag == true)
	{
		dog.vector.x() -= 1.0f;

		if (dog.vector.x() < 14.0f)
		{
			dog.vector.x() = 14.0f;

			dog.speedupflag = false;
		}
	}
}

void Jump(Media skeletonjump, Media dogjump, Player& dog, Player& skeleton, Status& status)
{
	if (dog.jumpflag == false)
	{
		if (env.isPushKey('S'))
		{
			dogjump.play();

			dog.jumpflag = true;

			dog.vector.y() = 20.0f;
		}
	}

	if (dog.jumpflag == true)
	{
		dog.pos.y() += dog.vector.y();

		dog.vector.y() -= 1.0f;
	}

	if (skeleton.jumpflag == false)
	{
		if (env.isPushKey('L'))
		{
			skeletonjump.play();

			skeleton.jumpflag = true;

			skeleton.vector.y() = 20.0f;
		}
	}

	if (skeleton.jumpflag == true)
	{
		skeleton.pos.y() += skeleton.vector.y();

		skeleton.vector.y() -= 1.0f;
	}
}

void HitFlag(Player& player, Object& floor, Status& status, int& mapchip, int& mapchip2, int& mapchip3, int& mapchip4, int& i, int& k)
{
	if (IsHFTop(player, floor, mapchip))
	{
		player.pos.y() = floor.pos.y() + floor.size.y() + 1.0f;

		player.vector.y() = -10.0f;

		player.jumpflag = false;

		if (IsHFStep(mapchip2, mapchip3))
		{
			--i;
			--k;
		}
	}

	if (IsHFBottom(player, floor, mapchip4))
	{
		player.pos.y() = floor.pos.y() - player.size.y() - 1.0f;

		player.vector.y() *= -1.0f;

		if (IsHFStep(mapchip2, mapchip3))
		{
			--i;
			--k;
		}
	}

	if (IsHFLeft(player, floor)){ player.pos.x() = floor.pos.x() - player.size.x() - 1.0f; }

	HitScreen(player, status);
}

bool IsHFTop(Player& player, Object& floor, int& mapchip)
{
	return (player.pos.x() >= floor.pos.x() && player.pos.x() <= floor.pos.x() + floor.size.x() &&
		player.pos.y() < floor.pos.y() + floor.size.y() && player.pos.y() >= floor.pos.y() + floor.size.y() / 2) &&
		(mapchip == Geography::HOLE || mapchip == Geography::FACE || mapchip == Geography::BONE || mapchip == Geography::GETTED);
}

bool IsHFBottom(Player& player, Object& floor, int& mapchip4)
{
	return (player.pos.x() >= floor.pos.x() && player.pos.x() <= floor.pos.x() + floor.size.x() &&
		player.pos.y() + player.size.y() < floor.pos.y() + floor.size.y() / 2 && player.pos.y() + player.size.y() > floor.pos.y()) &&
		(mapchip4 == HOLE || mapchip4 == Geography::FACE);
}

bool IsHFStep(int& mapchip2, int& mapchip3)
{
	return ((mapchip2 == FLOOR) && (mapchip3 == FLOOR));
}

bool IsHFLeft(Player& player, Object& floor)
{
	return (player.pos.x() + player.size.x() >= floor.pos.x() && player.pos.x() + player.size.x() < floor.pos.x() + floor.size.x() &&
		player.pos.y() >= floor.pos.y() && player.pos.y() < floor.pos.y() + floor.size.y());
}

void HitScreen(Player& player, Status& status)
{
	if (player.pos.x() + player.size.x() - status.camera > Window::WIDTH / 2){ player.pos.x() = Window::WIDTH / 2 - player.size.x() + status.camera; }
}

void Pose(Font& font, int& scene, Status& status, Player& skeleton, Player& dog, Color& color1, Color& color2, int& count, Media decision)
{
	if (env.isPushKey(GLFW_KEY_SPACE))
	{
		status.pose = !status.pose;

		color1 = Color::red;
		color2 = Color::white;

		count = 0;

		decision.play();

		env.flushInput();
	}

	if (status.pose == true)
	{
		status.camera -= status.scroll;

		skeleton.pos -= skeleton.vector;

		dog.pos -= dog.vector;

		if (scene == MULTI_GAMEMAIN)
		{

		}

		if (env.isPushKey(GLFW_KEY_UP) && count == 1)
		{
			color1 = Color::red;
			color2 = Color::white;

			count = 0;

			env.flushInput();
		}

		if (env.isPushKey(GLFW_KEY_DOWN) && count == 0)
		{
			color1 = Color::white;
			color2 = Color::red;

			count = 1;

			env.flushInput();
		}

		if (count == 0)
		{
			Back(scene);
		}

		if (count == 1)
		{
			if (env.isPushKey(GLFW_KEY_ENTER))
			{
				status.pose = !status.pose;

				decision.play();

				env.flushInput();
			}
		}
	}
}

void Back(int& scene)
{
	if (env.isPushKey(GLFW_KEY_ENTER)){ scene = TITLE; }

	env.flushInput();
}

void GameOver(Player& skeleton, Player& dog, Status& status, int& scene, int& result_branch, Media& BGM)
{
	if (skeleton.pos.y() < -(HEIGHT / 2) ||
		skeleton.pos.x() <= dog.pos.x() + dog.size.x())
	{
		BGM.stop();

		scene = RESULT;

		result_branch = DOG_EAT;
	}

	if (dog.pos.y() < -(HEIGHT / 2) ||
		dog.pos.x() + dog.size.x() - status.camera < -(WIDTH / 2))
	{
		BGM.stop();

		scene = RESULT;

		result_branch = SKELETON_SAFETY;
	}
}

void Repeat(Player& skeleton, Player& dog, Status& status, float& map_pos_x, Vec2f& pos, Vec2f& pos2)
{
	if (map_pos_x - status.camera <= -(WIDTH / 2))
	{
		skeleton.pos.x() -= status.camera;
		dog.pos.x() -= status.camera;
		status.camera = 0.0f;
		pos.x() = -WIDTH / 2;
		pos2.x() = WIDTH * 3 / 2;
	}
}

void Result(int& scene, int& result_branch, int& score, int& hiscore, float& players_distance, Font& font, int ranking[6], char name[3])
{
	//画像
	Texture dog_result_image("res/image/dog_result.png");
	Texture skeleton_result_image("res/image/skeleton_r.png");
	Texture skeleton_result_bg("res/image/skeleton_result_bg.png");
	Texture dog_result_bg("res/image/dog_result_bg2.png");

	//カウント
	int count = 0;

	//ランダム
	Random rand, rand2, rand3;
	rand.setSeed((std::time(nullptr)));
	if (rand(0.0f, 1.0f) > 0.5f){ rand2.setSeed((std::time(nullptr))); }
	else{ rand3.setSeed((std::time(nullptr))); }

	//ハイスコアフラグ
	bool hiscore_flag = false;
	bool hiscore_flag2 = false;
	int i = 0;

	//ハイスコアの色
	float R, G, B;
	Color color;

	//カラー
	Color menu_color = Color::olive;

	//プレイヤー間の距離の平均
	int players_distance_i;
	int players_distance_d;
	players_distance = players_distance / (score * 10);
	players_distance_i = players_distance - (players_distance / 100);
	players_distance_d = (players_distance - players_distance_i) * 100 - 1;


	//フォント
	std::string score_display;
	std::string players_distance_display;
	std::string players_distance_i_display;
	std::string players_distance_d_display;
	score_display = std::to_string(score);
	players_distance_display = std::to_string(players_distance);
	players_distance_i_display = std::to_string(players_distance_i);
	players_distance_d_display = std::to_string(players_distance_d);


	Object image = { Vec2f(-375.0f, 515.0f), Vec2f(750.0f, 950.0f) };

	//ランキング
	int rank;
	std::string na[3];





	while (scene == RESULT)
	{
		if (!env.isOpen()){ exit(0); }

		if (count == 136)
		{
			if (env.isPushKey(GLFW_KEY_ENTER))
			{
				if (hiscore < score){ hiscore = score; }

				ranking[5] = score;

				for (int i = 5; i > 0; --i)
				{
					if (ranking[i] > ranking[i - 1])
					{
						rank = ranking[i - 1];
						ranking[i - 1] = ranking[i];
						ranking[i] = rank;
					}
				}

				scene = MULTI_MENU;

				env.flushInput();
			}
		}

		if (hiscore_flag == false && count == 135)
		{
			if (hiscore < score)
			{
				hiscore_flag = true;
			}
		}

		if (hiscore_flag == true && hiscore_flag2 == false)
		{
			u_int chara = env.getPushedKey();

			count--;

			if (chara  && PKey()) {
				name[i] = chara;
				na[i] = chara;
				i++;
			}

			if (i == 3)
			{
				hiscore_flag2 = true;
			}

			env.flushInput();
		}


		if (count < 136){ count += 1; }


		if (count <= 30){ image.pos.y() -= 33.0f; }
		if (count > 30 && count <= 45){ image.pos.x() -= 30.0f; }


		env.begin();


		if (result_branch == SKELETON_SAFETY)
		{
			drawTextureBox(-WIDTH / 2, -HEIGHT / 2, WIDTH + 410, HEIGHT, 0, 0, 1024, 512, skeleton_result_bg, Color(1.0f, 1.0f, 1.0f, 0.2f));
		}

		if (result_branch == DOG_EAT)
		{
			drawTextureBox(-WIDTH / 2, -HEIGHT / 2, WIDTH + 410, HEIGHT, 0, 0, 1024, 512, dog_result_bg, Color(1.0f, 1.0f, 1.0f, 0.5f));
		}

		if (count > 45)
		{
			font.draw("score", Vec2f(10.0f, 350.0f - font.drawSize(" score").y() / 2), Color::yellow);
			font.draw("プレイヤー間の距離平均", Vec2f(10.0f, 140.0f - font.drawSize("プレイヤー間の距離平均").y() / 2), Color::yellow);
		}
		if (count > 75)
		{
			if (score >= hiscore)
			{
				R = rand(0.1f, 1.0f);
				G = rand2(0.1f, 1.0f);
				B = rand3(0.1f, 1.0f);
				color = Color(R, G, B);

				font.draw("ハイスコア！！", Vec2f(500.0f, 440.0f) - font.drawSize("ハイスコア！！") / 2, color);
			}
			font.draw(score_display + "m", Vec2f(820.0f - font.drawSize(score_display + "m").x(), 250.0f - font.drawSize(score_display + "m").y() / 2), Color::white);
		}

		if (count > 105)
		{
			font.draw(players_distance_i_display + "m" + players_distance_d_display + "cm",
				Vec2f(820.0f - font.drawSize(players_distance_i_display + "m" + players_distance_d_display + "cm").x(),
				0.0f - font.drawSize(players_distance_i_display + "m" + players_distance_d_display + "cm").y() / 2),
				Color::white);

		}

		if (result_branch == DOG_EAT)
		{
			drawTextureBox(image.pos.x(), image.pos.y(), image.size.x(), image.size.y(), 0, 0, 512, 512, dog_result_image, Color::white);
		}

		if (result_branch == SKELETON_SAFETY)
		{
			drawTextureBox(image.pos.x(), image.pos.y(), image.size.x(), image.size.y(), 0, 0, 512, 512, skeleton_result_image, Color::white);
		}

		if (hiscore_flag == true && hiscore_flag2 == false)
		{
			drawFillBox(-WIDTH / 2, -HEIGHT / 2, WIDTH, HEIGHT, Color(0, 0, 0, 0.8));
			font.draw("名前を入力してね", Vec2f(450.0f, 180.0f) - font.drawSize("名前を入力してね") / 2, Color::white);
		}

		//ネーム
		if (score > hiscore)
		{
			for (int k = 0; k < i; ++k)
			{
				font.draw(na[k], Vec2f(350.0f + 90.0f * k, -250.0f) - font.drawSize(na[k]) / 2, Color::teal);
			}

			for (int k = 0; k < 3; ++k)
			{
				drawFillBox(310.0f + 90.0f * k, -300.0f, 80.0f, 10.0f, Color::white);
			}
		}

		if (count > 135)
		{
			font.draw("メニュー", Vec2f(500.0f - font.drawSize("めにゅ～").x() / 2, -360.0f - font.drawSize("めにゅ～").y() / 2), menu_color);
		}

		env.end();
	}
}

void Animation(int& index, int& index2, int& animation_count)
{
	index = animation_count / 3 % 6;

	index2 = animation_count / 3 % 4;

	animation_count += 1;
}

void Bg(Vec2f& pos, Vec2f& pos2, Status& status)
{
	if (pos.x() - status.camera <= -WIDTH * 3 / 2)
	{
		pos.x() += WIDTH * 2;
	}

	if (pos2.x() - status.camera <= -WIDTH / 2)
	{
		pos2.x() += WIDTH * 2;
	}
}

void Cheat(int& score, int& scene, Player& skeleton, Player& dog, Status& status)
{
	if (env.isPushKey('B') && env.isPressKey(GLFW_KEY_RIGHT_SHIFT)){ score += 1000; }

	if (env.isPushKey('B') && env.isPressKey(GLFW_KEY_LEFT_SHIFT))
	{
		skeleton.pos = Vec2f(status.camera, 0.0f);
		dog.pos = Vec2f(status.camera - 700.0f, 0.0f);
		skeleton.speedupflag = false;
		skeleton.jumpflag = false;
		dog.speedupflag = false;
		dog.jumpflag = false;
	}
}

bool PKey()
{
	if (env.isPushKey('Q'))
	{
		return true;
	}
	else if (env.isPushKey('W'))
	{
		return true;
	}
	else if (env.isPushKey('E'))
	{
		return true;
	}
	else if (env.isPushKey('R'))
	{
		return true;
	}
	else if (env.isPushKey('T'))
	{
		return true;
	}
	else if (env.isPushKey('Y'))
	{
		return true;
	}
	else if (env.isPushKey('U'))
	{
		return true;
	}
	else if (env.isPushKey('I'))
	{
		return true;
	}
	else if (env.isPushKey('O'))
	{
		return true;
	}
	else if (env.isPushKey('P'))
	{
		return true;
	}
	else if (env.isPushKey('A'))
	{
		return true;
	}
	else if (env.isPushKey('S'))
	{
		return true;
	}
	else if (env.isPushKey('D'))
	{
		return true;
	}
	else if (env.isPushKey('F'))
	{
		return true;
	}
	else if (env.isPushKey('G'))
	{
		return true;
	}
	else if (env.isPushKey('H'))
	{
		return true;
	}
	else if (env.isPushKey('J'))
	{
		return true;
	}
	else if (env.isPushKey('K'))
	{
		return true;
	}
	else if (env.isPushKey('L'))
	{
		return true;
	}
	else if (env.isPushKey('Z'))
	{
		return true;
	}
	else if (env.isPushKey('X'))
	{
		return true;
	}
	else if (env.isPushKey('C'))
	{
		return true;
	}
	else if (env.isPushKey('V'))
	{
		return true;
	}
	else if (env.isPushKey('B'))
	{
		return true;
	}
	else if (env.isPushKey('N'))
	{
		return true;
	}
	else if (env.isPushKey('M'))
	{
		return true;
	}
	else

	{
		return false;
	}
}
