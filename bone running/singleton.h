#pragma once
#include "lib/framework.hpp"

#define env App::get()

#define WIN_WIDTH (2048)
#define WIN_HEIGHT (1024)

class App
{
private:

public:

	static AppEnv& get()
	{
		static AppEnv s_env(WIN_WIDTH, WIN_HEIGHT, false, true);

		return s_env;
	}
};