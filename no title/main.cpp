#include "lib/framework.hpp"
#include "singleton/singleton.h"
#include "scenemanager/scenemanager.h"
#include "scene/scene.h"
#include "chara/chara.h"
#include "map/map.h"
#include <iostream>


int main()
{

	env;

	SceneManager scenemanager;

	while (env.isOpen())
	{

		scenemanager.UpDate();

		scenemanager.Shift();

		env.begin();

		scenemanager.Draw();

		env.end();

	}
}
