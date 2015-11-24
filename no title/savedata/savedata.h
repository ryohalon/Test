#pragma once
#include "../topheader/topheader.h"

class SaveData
{
private:

	std::ofstream world_data_file;
	std::ofstream stage_data_file;
	int world_data[3];
	int stage_data[3][10];

public:

	SaveData();

	void SaveWorldData(StageStatus*);
	void SaveStageData(int, StageStatus*);
};