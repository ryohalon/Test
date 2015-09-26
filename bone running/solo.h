#pragma once
#include "lib/framework.hpp"
#include "gamemain.h"

void S_GameMain(int& scene, int& bone, Font& font, int& score, int& hiscore, int& nbone);

void S_Move(Media skeletonjump, Media dogjump, Media dogdash, Media skeletondash, Player& dog, Player& skeleton, Status& status);

void S_SpeedUp(Player& skeleton, Player& dog, Media dogdash, Media skeletondash);

void S_Jump(Media skeletonjump, Player& dog, Player& skeleton, Status& status);

void Born(Player& dog, Player& skeleton);

void DogAI(Player& dog, Status& status, Media dogjump,
	int mapchip[Geography::HEIGHTNUM][Geography::WIDTHNUM],
	float mapchip_pos_x[Geography::HEIGHTNUM][Geography::WIDTHNUM],
	float mapchip_pos_y[Geography::HEIGHTNUM][Geography::WIDTHNUM]);

void BoneGet(Player skeleton, Player& dog, Status& status, int& mapchip, Vec2f mapchip_pos, bool& nock_back);

void NockBack(Player& dog, Status& status, bool& nock_back);

void DogHitFlag(Player& player, Object& floor, Status& status, int& mapchip, int& mapchip2, int& mapchip3, int& mapchip4, int& i, int& k);

bool IsDogHFTop(Player& player, Object& floor, int& mapchip);

void S_GameOver(Player& skeleton, Player& dog, Status& status, int& scene, int& result_branch, Media& BGM, int& nbone);

void S_Repeat(Player& skeleton, Player& dog, Status& status, float& map_pos_x, Vec2f& pos, Vec2f& pos2);

void S_Result(int& scene, int& result_branch, int& score, int& hiscore, float& players_distance, int& bone, Font& font, Media decision);

void AitemNockBack(Player& dog, bool& nock_back, int& nbone, std::string& nb);