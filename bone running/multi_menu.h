#pragma once
#include "lib/framework.hpp"
#include "gamemain.h"

void Menu(int& scene, Font& font, int ranking[6], char name[3]);

void PushKey(int& scene, int& count, bool& poseflag, Font& font, 
	Color& color1, Color& color2, Color& color3, Color& color4, 
	Color& color5, Color& color6, Color& color7, Media decision);

void Ranking(Font font, int& score);