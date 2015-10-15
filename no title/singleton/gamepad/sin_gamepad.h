#pragma once
#include "../../lib/framework.hpp"
#include "../appenv/sin_appenv.h"

class Pad
{
private:

	// Ú‘±‚³‚ê‚Ä‚¢‚éGamePad”‚ğæ“¾
	size_t gamepad_num = App::Get().numGamePad();

public:

	static GamePad& Pad::Get()
	{
		// 0”Ô–Ú‚ÌGamePad‚ğæ“¾
		GamePad& pad = App::Get().gamePad(0);

		return pad;
	}
};