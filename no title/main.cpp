#include "lib/framework.hpp"
#include "singleton/appenv/sin_appenv.h"
#include "singleton/gamepad/sin_gamepad.h"
#include "scenemanager/scenemanager.h"
#include "scene/title/title.h"
#include "scene/worldselect/worldselect.h"
#include "scene/stageselect/stageselect.h"
#include "scene/option/option.h"
#include "scene\gamemanager\gamemanager.h"
#include "chara/chara.h"
#include "map/map.h"
#include <iostream>


int main()
{

	App::Get();

	SceneManager scenemanager;

	while (App::Get().isOpen())
	{
		scenemanager.UpDate();

		scenemanager.Shift();

		App::Get().begin();

		scenemanager.Draw();

		App::Get().end();

	}
}
