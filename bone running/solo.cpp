#include "solo.h"

void S_GameMain(int& scene, int& bone, Font& font, int& score, int& hiscore, int& nbone)
{
	//画像呼び込み
	Texture floor_image("res/image/floor.png");
	Texture dog_image("res/image/dog.png");
	Texture skeleton_image("res/image/skeleton.png");
	Texture bone_image("res/image/bone.png");

	//アイテム個数
	std::string nb = std::to_string(nbone);

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
	dog.pos.x() = -1000.0f;
	dog.pos.y() = -160.0;
	dog.size.x() = 128.0f;
	dog.size.y() = 64.0f;
	dog.vector.x() = 18.3f;
	dog.vector.y() = 0.0f;
	dog.jumpflag = false;
	dog.speedupflag = false;

	//床
	Object floor;

	//ステータス
	Status status;
	status.camera = 0.0f;
	status.scroll = 18.0;
	status.gravity = 0.2f;
	status.pose = false;

	//アイテム獲得時
	bool nock_back = false;


	//床
	int mapchip[Geography::HEIGHTNUM][Geography::WIDTHNUM] =
	{														   //20																					     //50
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 3, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
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



	///////////////////////////////////////////////////////////////////////
	//ゲーム本編
	while (scene == SOLO_GAMEMAIN || scene == RESULT || decision.isPlaying())

	{
		if (!env.isOpen()){ exit(0); }


		if (scene == SOLO_GAMEMAIN)
		{


			BGM.looping(true);


			//重力
			Gravity(skeleton, dog, status);

			//AI
			DogAI(dog, status, dogjump, mapchip, mapchip_pos_x, mapchip_pos_y);

			//速度、ジャンプ
			S_Move(skeletonjump, dogjump, dogdash, skeletondash, dog, skeleton, status);

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

						DogHitFlag(dog, floor, status, mapchip[i - 1][k], mapchip[i - 1][k + 1], mapchip[i][k + 1], mapchip[i + 1][k], i, k);

						Born(dog, skeleton);
					}

					if (mapchip[i][k] == Geography::BONE || mapchip[i][k] == Geography::GETTED)
					{
						floor.pos = Vec2f(mapchip_pos_x[i][k], mapchip_pos_y[i][k]);

						BoneGet(skeleton, dog, status, mapchip[i][k], floor.pos, nock_back);
					}
				}
			}

			//アイテム使用
			AitemNockBack(dog, nock_back, nbone, nb);

			//ノックバック
			NockBack(dog, status, nock_back);

			//ポーズ
			Pose(font, scene, status, skeleton, dog, color1, color2, pose_count, decision);

			//げーむおーばー
			if (env.isPushKey(GLFW_KEY_ENTER))
			S_GameOver(skeleton, dog, status, scene, result_branch, BGM, nbone);


			S_Repeat(skeleton, dog, status, mapchip_pos_x[0][314], bg_pos, bg2_pos);

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

				if (mapchip[i][k] == BONE)
				{
					drawTextureBox(mapchip_pos_x[i][k] - status.camera, mapchip_pos_y[i][k], map_size_xy, map_size_xy, 0, 0, 512, 512, bone_image);
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

		//アイテム個数
		drawTextureBox(-1000.0f, 400.0f, 100.0f, 100.0f, 0.0f, 0.0f, 512.0f, 512.0f, bone_image);
		drawTextureBox(-1000.0f, 390.0f, 100.0f, 100.0f, 0.0f, 0.0f, 512.0f, 512.0f, bone_image);
		drawTextureBox(-1000.0f, 380.0f, 100.0f, 100.0f, 0.0f, 0.0f, 512.0f, 512.0f, bone_image);

		drawBox(-1000, 390, 100, 100, 5, Color::black);

		font.draw(nb, Vec2f(-840.0f, 440.0f) - font.drawSize(nb) / 2, Color::cyan);


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
			S_Result(scene, result_branch, score, hiscore, players_distance, bone, font, decision);
		}

	}
}

void S_Move(Media skeletonjump, Media dogjump, Media dogdash, Media skeletondash, Player& dog, Player& skeleton, Status& status)
{
	S_SpeedUp(skeleton, dog, dogdash, skeletondash);

	dog.pos.x() += dog.vector.x();
	skeleton.pos.x() += skeleton.vector.x();

	status.camera += status.scroll;

	S_Jump(skeletonjump, dog, skeleton, status);
}

void S_SpeedUp(Player& skeleton, Player& dog, Media dogdash, Media skeletondash)
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

void S_Jump(Media skeletonjump, Player& dog, Player& skeleton, Status& status)
{
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

void Born(Player& dog, Player& skeleton)
{
	if (dog.pos.y() < -HEIGHT / 2)
	{
		dog.pos.y() = 0.0f;
		dog.pos.x() = skeleton.pos.x() - WIDTH / 2;
	}
}

void DogAI(Player& dog, Status& status, Media dogjump,
	int mapchip[Geography::HEIGHTNUM][Geography::WIDTHNUM],
	float mapchip_pos_x[Geography::HEIGHTNUM][Geography::WIDTHNUM],
	float mapchip_pos_y[Geography::HEIGHTNUM][Geography::WIDTHNUM])
{
	for (int i = 0; i < Geography::HEIGHTNUM; ++i)
	{
		for (int k = 0; k < Geography::WIDTHNUM; ++k)
		{
			if (dog.pos.x() + dog.size.x() < mapchip_pos_x[i][k] + 128 &&
				dog.pos.x() + dog.size.x() > mapchip_pos_x[i][k] + 100 &&
				dog.pos.y() > mapchip_pos_y[i][k] &&
				dog.pos.y() < mapchip_pos_y[i][k] + 128)
			{
				if (mapchip[i][k] == FLOOR &&
					(mapchip[i][k + 1] == HOLE && (mapchip[i + 1][k + 1] == FLOOR || mapchip[i + 2][k + 1] == HOLE)) ||
					(mapchip[i - 1][k + 2] == FLOOR || mapchip[i][k + 1] == FACE) ||
					(mapchip[i][k + 2] == FLOOR && mapchip[i - 1][k + 2] == HOLE && mapchip[i - 2][k + 2] == FLOOR && mapchip[i - 2][k + 3] == FLOOR))
				{
					dogjump.play();
					dog.jumpflag = true;
					dog.vector.y() = 20.0f;

					/*dog.speedupflag = true;
					dog.vector.x() = 44.0f;*/

				}

			}
		}
	}
}

void BoneGet(Player skeleton, Player& dog, Status& status, int& mapchip, Vec2f mapchip_pos, bool& nock_back)
{
	if (nock_back == false && mapchip == BONE)
	{
		if (skeleton.pos.x() + skeleton.size.x() >= mapchip_pos.x() &&
			skeleton.pos.x() <= mapchip_pos.x() + 128 &&
			skeleton.pos.y() + skeleton.size.y() >= mapchip_pos.y() &&
			skeleton.pos.y() <= mapchip_pos.y() + 128)
		{
			nock_back = true;

			dog.vector.x() = -5.0f;

			mapchip = GETTED;
		}
	}

	if (mapchip == GETTED)
	{
		if (mapchip_pos.x() + 128 - status.camera < -WIDTH / 2)
		{
			mapchip = BONE;
		}
	}
}

void NockBack(Player& dog, Status& status, bool& nock_back)
{
	if (nock_back == true)
	{
		dog.vector.x() += 1.0f;

		if (dog.pos.x() - status.camera < -WIDTH / 2)
		{
			dog.vector.x() = 18.3f;

			nock_back = false;
		}

		if (dog.vector.x() == 18.0f)
		{
			dog.vector.x() = 18.3f;

			nock_back = false;
		}
	}
}

void DogHitFlag(Player& player, Object& floor, Status& status, int& mapchip, int& mapchip2, int& mapchip3, int& mapchip4, int& i, int& k)
{
	if (player.pos.y() < -HEIGHT / 2)
	{
		player.pos.y() = -HEIGHT / 2 + player.size.y();
	}

	if (IsDogHFTop(player, floor, mapchip))
	{
		player.pos.y() = floor.pos.y() + floor.size.y() + 1.0f;

		player.vector.y() = -10.0f;

		player.jumpflag = false;
	}
}

bool IsDogHFTop(Player& player, Object& floor, int& mapchip)
{
	return (player.pos.x() >= floor.pos.x() && player.pos.x() <= floor.pos.x() + floor.size.x() &&
		player.pos.y() < floor.pos.y() + floor.size.y() && player.pos.y() >= floor.pos.y());
}

void S_GameOver(Player& skeleton, Player& dog, Status& status, int& scene, int& result_branch, Media& BGM, int& nbone)
{
	if (skeleton.pos.y() < -(HEIGHT / 2) ||
		skeleton.pos.x() <= dog.pos.x() + dog.size.x())
	{
		BGM.stop();

		scene = RESULT;

		result_branch = DOG_EAT;

		nbone = 0;
	}
}

void S_Repeat(Player& skeleton, Player& dog, Status& status, float& map_pos_x, Vec2f& pos, Vec2f& pos2)
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

void S_Result(int& scene, int& result_branch, int& score, int& hiscore, float& players_distance, int& bone, Font& font, Media decision)
{
	//画像
	Texture dog_result_image("res/image/dog_result.png");
	Texture skeleton_result_image("res/image/skeleton_r.png");
	Texture skeleton_result_bg("res/image/skeleton_result_bg.png");
	Texture dog_result_bg("res/image/dog_result_bg2.png");

	//カウント
	int count = 0;

	//セレクトフラグ
	bool select_flag = true;

	//ゲーム内のお金
	int min_get_money = 100;
	float score_ratio = 1.0f;
	int score_ratio_up = 100;
	int score_ratio_up_norma = 100;
	bool score_ratio_up_flag = true;
	float distance_ratio = 1.0f;
	int distance_ratio_up = 100;
	bool distance_ratio_up_flag = true;
	int get_money = 100;

	//ランダム
	Random rand, rand2, rand3;
	rand.setSeed((std::time(nullptr)));
	if (rand(0.0f, 1.0f) > 0.5f){ rand2.setSeed((std::time(nullptr))); }
	else{ rand3.setSeed((std::time(nullptr))); }

	//ハイスコアの色
	float R, G, B;
	Color color;

	//カラー
	Color menu_color = Color::olive;
	Color  restart_color = Color::gray;

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


	if (hiscore < score){ result_branch = SKELETON_SAFETY; }
	else{ result_branch = DOG_EAT; }


	while (score_ratio_up_flag == true || distance_ratio_up_flag == true)
	{
		if (score >= score_ratio_up)
		{
			score_ratio += 0.1f;

			score_ratio_up += score_ratio_up_norma;

			score_ratio_up_norma += 50;
		}
		else{ score_ratio_up_flag = false; }

		if (players_distance <= distance_ratio_up)
		{
			distance_ratio += 0.1f;

			distance_ratio_up -= 10;

			if (players_distance < 20.0f && players_distance > 0.0f)
			{
				distance_ratio = 10.0f;
			}
		}
		else{ distance_ratio_up_flag = false; }
	}


	get_money = min_get_money * score_ratio * distance_ratio;

	std::string min_get_money_display = std::to_string(min_get_money);
	std::string get_money_display = std::to_string(get_money);

	std::ostringstream score_ratio_d;
	score_ratio_d << std::setprecision(2) << score_ratio;
	std::string score_ratio_display = score_ratio_d.str();

	std::ostringstream distance_ratio_d;
	distance_ratio_d << std::setprecision(2) << distance_ratio;
	std::string distance_ratio_display = distance_ratio_d.str();

	while (scene == RESULT || decision.isPlaying())
	{
		if (!env.isOpen()){ exit(0); }

		if (env.isPushKey(GLFW_KEY_LEFT))
		{
			menu_color = Color::olive;
			restart_color = Color::gray;

			select_flag = true;
		}
		if (env.isPushKey(GLFW_KEY_RIGHT))
		{
			menu_color = Color::gray;
			restart_color = Color::olive;

			select_flag = false;
		}
		if (count == 201)
		{
			if (env.isPushKey(GLFW_KEY_ENTER))
			{
				decision.play();

				if (hiscore < score){ hiscore = score; }

				bone += get_money;

				if (select_flag == true){ scene = SOLO_MENU; }
				else{ scene = S_RESTART; }

				env.flushInput();
			}
		}


		if (count < 201){ count += 1; }


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
			font.draw("獲得ボーン", Vec2f(10.0f, -120.0f - font.drawSize("獲得ボーン").y() / 2), Color::yellow);
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

		if (count > 135)
		{
			font.draw(min_get_money_display, Vec2f(50.0f, -200.0f - font.drawSize(min_get_money_display).y() / 2), Color::white);
			font.draw("✕" + score_ratio_display + "✕" + distance_ratio_display, Vec2f(50.0f + font.drawSize(min_get_money_display).x(), -200.0f - font.drawSize("✕" + score_ratio_display + "✕" + distance_ratio_display).y() / 2), Color::lime);

		}

		if (count > 165)
		{
			font.draw("=   " + get_money_display, Vec2f(820.0f - font.drawSize("=   " + get_money_display).x(), -280.0f - font.drawSize("= " + get_money_display).y() / 2), Color::white);
		}


		if (result_branch == DOG_EAT)
		{
			drawTextureBox(image.pos.x(), image.pos.y(), image.size.x(), image.size.y(), 0, 0, 512, 512, dog_result_image, Color::white);
		}

		if (result_branch == SKELETON_SAFETY)
		{
			drawTextureBox(image.pos.x(), image.pos.y(), image.size.x(), image.size.y(), 0, 0, 512, 512, skeleton_result_image, Color::white);
		}


		if (count > 200)
		{
			font.draw("メニュー", Vec2f(-100.0f - font.drawSize("めにゅ～").x(), -360.0f - font.drawSize("めにゅ～").y() / 2), menu_color);
			font.draw("リスタート", Vec2f(100.0f, -360.0f - font.drawSize("リスタート").y() / 2), restart_color);
		}


		env.end();
	}
}

void AitemNockBack(Player& dog, bool& nock_back, int& nbone, std::string& nb)
{
	if (nbone > 0)
	{
		if (nock_back == false)
		{
			if (env.isPressKey('O'))
			{
				nbone -= 1;

				nb = std::to_string(nbone);

				dog.vector.x() = -5.0f;

				nock_back = true;
			}
		}
	}

	if (env.isPushKey('N') && env.isPushKey('M'))
	{
		nock_back = true;

		dog.vector.x() = -5.0f;
	}

	if (env.isPushKey(GLFW_KEY_ENTER))
	{
		nock_back = true;
	}
}