#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include <windows.h>
#include <DxErr.h>
#include "Input.h"
#include "DeviceManager.h"
#include "DXGraphics.h"
#include "Texture.h"
#include "Sprite.h"
#include "Camera.h"

class Game
{
	protected:
		Camera * camera;
		DWORD _DeltaTime;		// Time between the last frame and current frame
		Input * _input;
		static Graphics * _dxgraphics;
		DeviceManager * _device;

		void CheckKey();
		// Render a single frame
		void _RenderFrame();

		//
		//====================== VIRTUAL METHOD ===========================
		//
		virtual void Update(float Delta) = 0;
		// Đã bỏ delta time cho phương thức Render
		virtual void RenderFrame(LPDIRECT3DDEVICE9) = 0;
		virtual void LoadResources(LPDIRECT3DDEVICE9) = 0;
		virtual void ProcessInput(LPDIRECT3DDEVICE9, float Delta) = 0;

		virtual void OnKeyDown(int KeyCode) = 0;
		virtual void OnKeyUp(int KeyCode) = 0;
		//======================= END VIRTUAL METHOD ======================

		//======================= Start texture ======================
		LPDIRECT3DTEXTURE9 playerTexture;
		LPDIRECT3DTEXTURE9 brickTexture;
		//======================= End Texture ========================

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

		void setPlayerTexture(LPDIRECT3DTEXTURE9);
		LPDIRECT3DTEXTURE9 getPlayerTexture();
		void setBrickTexture(LPDIRECT3DTEXTURE9);
		LPDIRECT3DTEXTURE9 getBrickTexture();
};

#endif
