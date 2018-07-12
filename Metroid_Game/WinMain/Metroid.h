#pragma once
#ifndef _METROID_H_
#define _METROID_H_

#include "Define.h"
#include "Game.h"
#include "Texture.h"
#include "Sprite.h"
#include "Map.h"
#include "World.h"

class Metroid : public Game
{
protected:
	LPDIRECT3DSURFACE9 startscreen;
	LPD3DXSPRITE spriteHandler;
	World * world;
private:
	void _InitBackground();
	void _InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture);
	void _InitPositions();

	DWORD start_jump;
	DWORD now_jump;
	DWORD tick_per_frame;

	Map *map;
public:
	Metroid(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate);
	~Metroid();

	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddev);
	// ---------------------------
	virtual void Update(float Delta); //Kiểm tra screen Mode (bắt đầu, room1, room2,... hay gameover)
	virtual void UpdateFrame(float Delta);	//update các object trong game
	// -----------------------------
	virtual void Render(LPDIRECT3DDEVICE9 d3ddv);	//render từng screen mode (room1, room2,... hay gameover)
	virtual void RenderStartScreen(LPDIRECT3DDEVICE9 d3ddv);	//render các scene chính (room1, room2...) trong game
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv);		//render từng object trong game
	// ---------------------------
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);

	DWORD GetTickPerFrame();

	int screenMode;
	bool isFreezing;
	bool isOnFloor;
	bool isInGame;

	LPD3DXSPRITE getSpriteHandler();
	Map *getMap();
};

#endif // !_METROID_
