#pragma once
#include "../singleton/singleton.h"

enum SceneName
{
	TITLE,
	WORLDSELECT,
	STAGESELECT,
	GAMEMAIN,
};

enum StageStatus
{
	UNCLEAR,
	CLEAR,
};


//******************************************************************
//タイトル

class Title
{
private:

	//タイトル
	Texture title;
	//Press Start
	Texture press_start;

	//透明度
	float alpha;
	float alpha_count;

	float ChangeAlpha();

public:

	Title();

	void UpDate();
	void Draw();
	SceneName Shift();

};


//******************************************************************
//ワールドセレクト

class WorldSelect
{
private:

	Texture world_image;

	int world_num;

	StageStatus worldstatus[1][3];

	struct World
	{
		Vec2f pos;
		int size;
	};
	World world;

	struct Cursol
	{
		Vec2f pos;
		int size;
	};
	Cursol cursol;
	
public:

	WorldSelect();

	void UpDate();
	int GetterWorld();
	void Draw();
	SceneName Shift();
};


//****************************************************************
//ステージセレクト

class StageSelect
{
private:

	Texture world_image;

	int world_num;
	int stage_num;
	StageStatus stagestatus[2][5];

	struct Stage
	{
		Vec2f pos;
		int size;
	};
	Stage stage;

	struct Cursol
	{
		Vec2f pos;
		int size;
	};
	Cursol cursol;

public:

	StageSelect();

	void UpDate();
	int GetterStage();
	void Draw();
	SceneName Shift();

};


//****************************************************************
//ゲームメイン

class GameMain
{
private:

	int world_num;
	int stage_num;

public:

	void UpDate();
	void Draw();
	SceneName Shift();

};


//****************************************************************
//オプション（作れたら最後に作るかも）

class Option
{
private:

public:

	void UpDate();
	void Draw();
	SceneName Shift();

};