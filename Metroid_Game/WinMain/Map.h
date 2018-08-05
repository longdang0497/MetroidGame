#pragma once
#include "Sprite.h"
#include "Texture.h"
#include "Define.h"
#include "trace.h"
#include<vector>
#include<iostream>
#include<fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include "Math.h"
#include <d3dx9.h>
#include "Grid.h"
#include "Brick.h"
class Camera;

using namespace std;

class Map {
	struct brick {
		char type;
		int x_pixel;
		int y_pixel;
	};
public:
	Map(LPD3DXSPRITE spriteHandler, string filePath, int left, int top);

	~Map();

	void drawMap();
	void drawBrick(brick value);

	void Update(int _roomID);
	void UpdateMap(RECT);

	// Đặt giới hạn load map
	void setLimitation(int width, int height);
	RECT getBoundary();

	// Load map lên
	bool loadMap(string filePath);

	LPDIRECT3DDEVICE9 getDevice();
	LPDIRECT3DTEXTURE9 getTexture();
	vector<string> getStringMap();

	static const int count = 0;

	void setGrid(Grid*);
	Grid* getGrid();

	void inputBrickToGrid();
private:
	Grid * grid;
	std::string filePath;
	vector<string> stringMap;
	vector<brick> drawBrickArray = vector<brick> ();
	int roomID;
	Sprite *sprite;

	DeviceManager *deviceManager;

	//Start coordinate of the camera
	RECT m_boundary = RECT();

	int top;
	int left;

	int widthLimitation;
	int heightLimitation;

	LPDIRECT3DDEVICE9 d3ddv;
	LPDIRECT3DTEXTURE9 mapTexture;
};