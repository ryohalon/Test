#pragma once
#include "../../lib/framework.hpp"
#include "../appenv/sin_appenv.h"

class Pad
{
private:

	// �ڑ�����Ă���GamePad�����擾
	size_t gamepad_num = App::Get().numGamePad();

public:

	static GamePad& Pad::Get()
	{
		// 0�Ԗڂ�GamePad���擾
		GamePad& pad = App::Get().gamePad(0);

		return pad;
	}
};