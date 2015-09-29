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
//�^�C�g��

class Title
{
private:

	//�^�C�g��
	Texture title;
	//Press Start
	Texture press_start;

	//�����x
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
//���[���h�Z���N�g

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
//�X�e�[�W�Z���N�g

class StageSelect
{
private:

	Texture world_image;

	int world_num;
	int stage_num;
	StageStatus stage_status[3][10];

	//�}�b�v�A�C�R��
	struct Stage
	{
		Vec2i pos;
		int size;
	};
	Stage stage;

	//�J�[�\��
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
//�Q�[�����C��

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
//�I�v�V�����i��ꂽ��Ō�ɍ�邩���j

class Option
{
private:

public:

	void UpDate();
	void Draw();
	SceneName Shift();

};