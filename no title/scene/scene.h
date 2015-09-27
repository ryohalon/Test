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

public:

	void UpDate();
	void Draw();
	SceneName Shift();

};


//******************************************************************
//���[���h�Z���N�g

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
//�X�e�[�W�Z���N�g

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
//�Q�[�����C��

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
//�I�v�V�����i��ꂽ��Ō�ɍ�邩���j

class Option
{
private:

public:

	void UpDate();
	void Draw();
	SceneName Shift();

};