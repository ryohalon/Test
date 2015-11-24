#include "map.h"

Map::Map()
{
	const char* map_txt = "res/stage_file/test_stage.txt";
	std::ifstream* map_file = new std::ifstream(map_txt);

	if (map_file->fail())
	{
		std::cerr << "ƒtƒ@ƒCƒ‹“Ç‚Ýž‚Ý‚ÉŽ¸”s‚µ‚Ü‚µ‚½\n";

		exit(0);
	}

	for (int i = 0; i < static_cast<int>(MapNum::HEIGHTNUM); i++)
	{
		for (int k = 0; k < static_cast<int>(MapNum::WIDTHNUM); k++)
		{
			*map_file >> map_chip_data[i][k];
		}
	}
}

int Map::GetMapType(int i, int k)
{
	return map_chip_data[i][k];
}

void Map::UpDate()
{

}

void Map::Init(int world_num, int stage_num)
{
	char* map_txt;

	switch (world_num)
	{
	case 1:
		switch (stage_num)
		{
		case 1:
			map_txt = "res/stage_file/world1/stage1.txt";
			break;
		}
		break;
	}

	std::ifstream* map_chip = new std::ifstream(map_txt);

	for (int i = 0; i < static_cast<int>(MapNum::HEIGHTNUM); i++)
	{
		for (int k = 0; k < static_cast<int>(MapNum::WIDTHNUM); k++)
		{
			*map_chip >> map_chip_data[i][k];
		}
	}

	delete map_txt;
	delete map_chip;
}

void Map::Draw()
{
	glPushMatrix();
	glTranslated(-WIN_WIDTH / 2, WIN_HEIGHT / 2 - MAP_SIZE, 0);
	for (int i = 0; i < static_cast<int>(MapNum::HEIGHTNUM); i++)
	{
		for (int k = 0; k < static_cast<int>(MapNum::WIDTHNUM); k++)
		{
			switch (map_chip_data[i][k])
			{
			case static_cast<int>(MapType::NONE) :
				break;

			case static_cast<int>(MapType::FLOOR) :
				drawFillBox(MAP_SIZE * k, MAP_SIZE * (-i), MAP_SIZE, MAP_SIZE, Color::red);
				break;

			/*case static_cast<int>(MapType::) :
				drawFillBox(MAP_SIZE * k, MAP_SIZE * (-i), MAP_SIZE, MAP_SIZE, Color::red);
				break;*/
			}
		}
	}
	glPopMatrix();
}