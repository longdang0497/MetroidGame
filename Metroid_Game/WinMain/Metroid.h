#pragma once
#ifndef _METROID_H_
#define _METROID_H_

#include "Define.h"
#include "Game.h"
#include "Map.h"
#include "World.h"
#include "Grid.h"
#include <time.h>
#include "trace.h"
#include "utils.h"

class Metroid : public Game
{
protected:
	LPDIRECT3DSURFACE9 startscreen;
	LPDIRECT3DSURFACE9 introscreen;
	LPDIRECT3DSURFACE9 gameoverscreen;
	LPD3DXSPRITE spriteHandler;
	LPDIRECT3DTEXTURE9 _texture;
	World * world;
	CSound * intro;
	CSound * appear;
	GameSound *sound;
	Grid *grid;
private:
	void _InitBackground();
	void _InitSprites(LPDIRECT3DDEVICE9 d3ddv);
	void _InitPositions();

	DWORD start_jump;
	DWORD now_jump;
	DWORD tick_per_frame;

	Map *map;

	Texture texture;
public:
	Metroid(HINSTANCE hInstance, LPWSTR Name, int Mode, int IsFullScreen, int FrameRate);
	~Metroid();

	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddev);
	// ---------------------------
	virtual void Update(float Delta); //Kiểm tra screen Mode (bắt đầu, room1, room2,... hay gameover)
	virtual void UpdateIntro(float Delta);	//update màn hình intro của game
	virtual void UpdateFrame(float Delta);	//update các object trong game
	// -----------------------------
	virtual void Render(LPDIRECT3DDEVICE9 d3ddv);	//render từng screen mode (room1, room2,... hay gameover)
	virtual void RenderIntro(LPDIRECT3DDEVICE9 d3ddv);	//render màn hình intro 
	virtual void RenderStartScreen(LPDIRECT3DDEVICE9 d3ddv);	//render các scene chính (room1, room2...) trong game
	virtual void RenderGameOver(LPDIRECT3DDEVICE9 d3ddv);	//render màn hình gameover
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

	float time_jump;
	float time_freezing;
	float time_in_game;

	LPD3DXSPRITE getSpriteHandler();
	Map *getMap();
	Grid* getGrid();

	void setSamusBulletDirection(Bullet*);
};

#endif // !_METROID_
