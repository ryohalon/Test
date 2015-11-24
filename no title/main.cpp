#include "scenemanager/scenemanager.h"


int main()
{

	App::Get();

	SceneManager* scenemanager = new SceneManager();

	scenemanager->MainLoop();
}
