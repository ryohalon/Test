#pragma once
#include "../appenv/sin_appenv.h"


class Pad
{
private:

	// 接続されているGamePad数を取得
	size_t gamepad_num = App::Get().numGamePad();

public:

	static GamePad& Pad::Get()
	{
		// 0番目のGamePadを取得
		GamePad& pad = App::Get().gamePad(0);

		return pad;
	}
};