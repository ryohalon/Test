#pragma once
#include "lib/framework.hpp"
#include "singleton.h"
#include "struct.h"
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>


enum Window
{
	HEIGHT = 1024,
	WIDTH = 2048
};

enum Scene
{
	TITLE,
	SOLO_MENU,
	MULTI_MENU,
	TUTORIAL,
	OPERATION,
	OPTION,
	SOLO_GAMEMAIN,
	MULTI_GAMEMAIN,
	RESULT,
	S_RESTART,
	RESTART
};

enum Geography
{
	HOLE,
	FLOOR,
	FACE,
	BONE,
	GETTED,
	HEIGHTNUM = 8,
	WIDTHNUM = 330
};

enum Result
{
	DOG_EAT,
	SKELETON_SAFETY
};

void GameMain(Font font, int& scene, int& score, int& hiscore, int& bone, int ranking[6], char name[3]);

void Score(int& score, int& hiscore, std::string& score_display, std::string& hiscore_display, float& players_distance, Player& skeleton, Player& dog, bool& pose);

void Gravity(Player& skeleton, Player& dog, Status& status);

void Move(Media skeletonjump, Media dogjump, Media dogdash, Media skeletondash, Player& dog, Player& skeleton, Status& status);

void SpeedUp(Player& skeleton, Player& dog, Media dogdash, Media skeletondash);

void Jump(Media skeletonjump, Media dogjump, Player& dog, Player& skeleton, Status& status);

void HitFlag(Player& player, Object& floor, Status& status, int& mapchip, int& mapchip2, int& mapchip3, int& mapchip4, int& i, int& k);

bool IsHFTop(Player& player, Object& floor, int& mapchip);

bool IsHFBottom(Player& player, Object& floor, int& mapchip4);

bool IsHFStep(int& mapchip2, int& mapchip3);

bool IsHFLeft(Player& player, Object& floor);

void HitScreen(Player& player, Status& status);

void Pose(Font& font, int& scene, Status& status, Player& skeleton, Player& dog, Color& color1, Color& color2, int& count, Media decision);

void Back(int& scene);

void GameOver(Player& skeleton, Player& dog, Status& status, int& scene, int& result_branch, Media& BGM);

void Repeat(Player& skeleton, Player& dog, Status& status, float& map_pos_x, Vec2f& pos, Vec2f& pos2);

void Result(int& scene, int& result_branch, int& score, int& hiscore, float& players_distance, Font& font, int ranking[6], char name[3]);

void Animation(int& index, int& index2, int& animation_count);

void Bg(Vec2f& pos, Vec2f& pos2, Status& camera);

bool PKey();











void Cheat(int& score, int& scene, Player& skeleton, Player& dog, Status& status);
