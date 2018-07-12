#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include <windows.h>
#include <DxErr.h>
#include "Input.h"
#include "DeviceManager.h"
#include "DXGraphics.h"

class Game
{
	protected:
		DWORD _DeltaTime;		// Time between the last frame and current frame
		Input * _input;
		static Graphics * _dxgraphics;
		DeviceManager * _device;

		// Render a single frame
		void _RenderFrame();

		//
		//====================== VIRTUAL METHOD ===========================
		//
		virtual void Update(float Delta);
		// Đã bỏ delta time cho phương thức Render
		virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv);
		virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
		virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta);

		virtual void OnKeyDown(int KeyCode);
		virtual void OnKeyUp(int KeyCode);
		//======================= END VIRTUAL METHOD ======================

	public:
		//Doi tuong Direct Sound
		//static SoundManager *gameSound;
		Game();
		Game(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullscreen, int FrameRate);
		~Game();

		// Initialize the game with set parameters
		void GameInit();

		// Run game
		void GameRun();
};

#endif
