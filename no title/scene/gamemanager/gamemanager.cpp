#include "gamemanager.h"



//***************************************************************
//�Q�[�����C��

//private


//public

//�R���X�g���N�^
GameMain::GameMain()
{

}

void GameMain::SetWorldNum(int num)
{
	world_num = num;
}

void GameMain::SetStageNum(int num)
{
	stage_num = num;
}

StageStatus GameMain::GetStageStatus()
{
	return StageStatus::CLEAR;
}

void GameMain::UpDate()
{

}

void GameMain::Draw()
{
	//�w�i
	drawFillBox(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT, Color::red);
}

SceneName GameMain::Shift()
{
	return SceneName::STAGESELECT;
}