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
#include "TileObject.h"
#include "Grid.h"

class Camera;

using namespace std;

class Map {
public:
	Map(LPD3DXSPRITE spriteHandler, string filePath, LPDIRECT3DDEVICE9 d3ddev, int left, int top);

	~Map();

	void drawMap();
	void drawBrick(TileObject * value);

	void Update(int _roomID);
	void UpdateMap(RECT);

	// Đặt giới hạn load map
	void setLimitation(int x, int y, int width, int height);
	RECT getBoundary();

	// Load map lên
	bool loadMap(string filePath);

	vector<string> getStringMap();

	static const int count = 0;
	TileObject * tileMap;
private:
	Grid * grid;
	std::string filePath;
	vector<string> stringMap;
	vector<TileObject *> drawBrickArray = vector<TileObject *> ();
	int roomID;
	LPDIRECT3DTEXTURE9 _texture;
	LPDIRECT3DDEVICE9 d3ddev;

	//Start coordinate of the camera
	RECT m_boundary = RECT();

	//TODO: 
	int widthLimitation;
	int heightLimitation;

	int m_max_Row;
	int m_max_Column;
};