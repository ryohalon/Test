#pragma once
#include "../singleton/appenv/sin_appenv.h"
#include "../singleton/gamepad/sin_gamepad.h"



class Map
{
private:

	int map_chip_data[MapNum::WIDTHNUM][MapNum::HEIGHTNUM];

public:

	void UpDate();
	void Unit();
	void Draw();

};