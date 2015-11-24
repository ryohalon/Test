#include "savedata.h"

//                                                                            II  II
//             II                          II                                 II    II
//      IIIIIIIIIIIIIIII         IIIIIIIIIIIIIIIIIIIIII            IIIIIIIIIIIIIIIIIIII
//             II                II                  II            II         II
//   IIIIIIIIIIIIIIIIIIIIII           IIIIIIIIIIII                II          II
//            IIII                                               II           II
//          II II II               IIIIIIIIIIIIIIIIII           IIIIIIIIIII   II   II
//         II  II  II                   II  II                 II       II    II  II
//       III   II   III                II   II      II        II       II      IIII
//    III      II      III            II    II      II       II    II II        II  II
//             II                  III       IIIIIIII       II       II       II  II


//private



//public

//コンストラクタ
SaveData::SaveData()
{
	for (int i = 0; i < 3; ++i)
		world_data[i] = 0;

	for (int i = 0; i < 3; ++i)
	{
		for (int k = 0; k < 10; ++k)
		{
			stage_data[i][k] = 0;
		}
	}
}

//ワールドのクリア情報をセーブする関数
void SaveData::SaveWorldData(StageStatus* world_status)
{
	world_data_file.open("res/savedata/world_data.txt", std::ios::ate);

	for (int i = 0; i < 3; ++i)
	{
		world_data[i] = int(world_status[i]);

		world_data_file << world_data[i];

		if (i != 2)
			world_data_file << " ";
	}
}

//ステージのクリア情報をセーブする関数
void SaveData::SaveStageData(int world_num, StageStatus* stage_status)
{
	stage_data_file.open("res/savedata/stage_data.txt", std::ios::ate);

	for (int i = 0; i < 10; ++i)
	{
		stage_data[world_num][i] = int(stage_status[world_num]);

		stage_data_file << stage_data[world_num][i];

		if (i != 9)
			stage_data_file << " ";
	}
}