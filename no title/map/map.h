#pragma once
#include "../topheader/topheader.h"



class Map
{
private:

	int map_chip_data[static_cast <int>(MapNum::HEIGHTNUM)][static_cast <int>(MapNum::WIDTHNUM)];

public:

	Map();

	int GetMapType(int, int);

	void Init(int, int);
	void UpDate();
	void Draw();

};