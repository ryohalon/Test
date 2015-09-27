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

public:

	void UpDate();
	void Draw();
	SceneName Shift();

};


//******************************************************************
//ワールドセレクト

class WorldSelect
{
private:

	int world_num;

public:

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

	int world_num;
	int stage_num;
	StageStatus stagestatus[2][5];

	struct Stage
	{
		Vec2f pos;
		int size;
	};
	Stage stage;

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