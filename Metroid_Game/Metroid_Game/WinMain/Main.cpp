#include <windows.h>
#include "Game.h"
#include "Metroid.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Metroid metroid(hInstance, L"Metroid game", GAME_SCREEN_RESOLUTION_640_480_24, 0, 80);

	metroid.GameInit();
	metroid.GameRun();

	return 0;
}