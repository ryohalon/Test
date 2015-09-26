#include "lib/framework.hpp"
#include "singleton.h"
#include "struct.h"
#include "title.h"
#include "solo_menu.h"
#include "multi_menu.h"
#include "tutorial.h"
#include "operation.h"
#include "option.h"
#include "solo.h"
#include "gamemain.h"
#include "restart.h"
#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>


int main()
{
	env;

	//フォント
	Font font("res/font/keifont.ttf");
	font.size(80);

	//起動時に一回だけ表示
	bool start_flag = false;

	//シーン切り替え
	int scene = TITLE;

	///////////////////////////////////////////////////////////////
	//マルチ
	///////////////////////////////////////////////////////////////

	//ランキング
	int ranking[6] = { 2000, 1800, 1500, 1000, 500, 0};
	char name[3] = { 'U', 'M', 'R' };

	//スコア
	int score = 0;
	int hiscore = 2000;

	//所持金額
	int bone = 100;


	//////////////////////////////////////////////////////////////
	//ソロ
	//////////////////////////////////////////////////////////////

	//スコア　
	int s_score = 0;
	int s_hiscore = 0;

	//所持金額
	int s_bone = 100;

	//アイテム
	int nbone = 0;



	/////////////////////////////////////////////////////////////
	//メイン
	/////////////////////////////////////////////////////////////
	while (env.isOpen())
	{
		env.begin();

		switch (scene)
		{
		case TITLE:
			Title(scene, font, start_flag);
			break;

		case TUTORIAL:
			Tutorial(scene, font);
			break;

		case OPERATION:
			Operation(scene, font);
			break;

		case OPTION:
			Option(scene, font);
			break;

		case SOLO_MENU:
			SoloMenu(scene, s_bone, font, nbone);

		case MULTI_MENU:
			Menu(scene, font, ranking, name);
			break;

		case SOLO_GAMEMAIN:
			S_GameMain(scene, s_bone, font, s_score, s_hiscore, nbone);
			break;

		case MULTI_GAMEMAIN:
			GameMain(font, scene, score, hiscore, bone, ranking, name);
			break;

		case S_RESTART:
			S_Restart(scene);
			break;

		case RESTART:
			Restart(scene);
			break;
		}

		env.end();
	}
}
