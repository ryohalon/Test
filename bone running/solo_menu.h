#pragma once
#include "lib/framework.hpp"
#include "gamemain.h"

void SoloMenu(int& scene, int& bone, Font& font, int& nbone);

void S_PushKey(int& scene, int& bone, int& count, bool& poseflag, Font& font, 
	Color& color1, Color& color2, Color& color3, Color& color4, 
	Color& color5, Color& color6, Color& color7, Media decision, int& nbone,
	std::string& bone_display, std::string& nb);