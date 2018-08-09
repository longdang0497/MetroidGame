#pragma once
#include "Define.h"
#include "trace.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include "Math.h"
#include "Brick.h"
//#include "Metroid.h"

using namespace std;

class Map {
	struct brick {
		char type;
		int x_pixel;
		int y_pixel;
	};
public:
	Map(LPD3DXSPRITE spriteHandler, LPDIRECT3DTEXTURE9 texture, string filePath, int left, int top);

	~Map();

	void drawMap();
	void drawBrick(brick value);

	void Update(int _roomID);
	void UpdateMap(RECT);

	// Đặt giới hạn load map
	void setLimitation(int x, int y, int width, int height);
	RECT getBoundary();

	// Load map lên
	bool loadMap(string filePath);

	LPDIRECT3DTEXTURE9 getTexture();
	vector<string> getStringMap();

	static const int count = 0;

	int getRow();
	int getColumn();

	//Metroid * getMetroid();

	//void inputBrickToGrid(Metroid * metroid);
private:
	//Metroid * metroid;
	std::string filePath;
	vector<string> stringMap;
	vector<brick> drawBrickArray = vector<brick> ();
	int roomID;
	Sprite *sprite;

	//Start coordinate of the camera
	RECT m_boundary = RECT();

	//TODO: 
	int widthLimitation;
	int heightLimitation;

	int m_max_Row;
	int m_max_Column;

	LPDIRECT3DTEXTURE9 texture;
};