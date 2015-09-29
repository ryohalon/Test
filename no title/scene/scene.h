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

	StageStatus world_status[3];

	struct World
	{
		Vec2i pos;
		int size;
	};
	World world;

	struct Cursol
	{
		Vec2i pos;
		int size;
	};
	Cursol cursol;
	
	void MoveCursol();

public:

	WorldSelect();

	void SetWorldClear(StageStatus);
	int GetWorldNum();

	void UpDate();
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
	StageStatus stage_status[3][10];

	//マップアイコン
	struct Stage
	{
		Vec2i pos;
		int size;
	};
	Stage stage;

	//カーソル
	struct Cursol
	{
		Vec2i pos;
		int size;
	};
	Cursol cursol;

	void MoveCursol();

public:

	StageSelect();

	void SetWorldNum(int);
	void StageClear(StageStatus);
	int GetStageNum();
	StageStatus IsWorldClear();

	void UpDate();
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

	GameMain();

	void SetWorldNum(int);
	void SetStageNum(int);
	StageStatus GetStageStatus();

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