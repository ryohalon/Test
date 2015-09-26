#pragma once
#include "lib/framework.hpp"
#include "gamemain.h"

void Title(int& scene, Font& font, bool& start_flag);

void PressEnter(Font& font, bool& start_flag, float& alpha, int& alpha_count, Media decision);

void Select(Font& font, int& scene, Media decision, int& select_count,
	Color& c_gamestart, Color& c_solo, Color& c_multi, Color& c_tutorial,
	Color& c_option, Color& c_training, Color& c_operation, Color& c_back);

void KeyOperation(Font& font, int& scene, int& select_count,
	Color& c_gamestart, Color& c_tutorial, Color& c_option, Color& c_training, Color& c_operation, Color& c_back, Color& c_multi, Color& c_solo, Media decision);

void TitleGameMain(Font font, int& scene);