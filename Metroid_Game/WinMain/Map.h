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



using namespace std;

class Map {
public:
	Map(LPD3DXSPRITE spriteHandler, LPDIRECT3DTEXTURE9 texture,string filePath, DeviceManager *deviceManager, int x, int y, int width, int height);

	~Map();

	void drawMap();

	void Update();
	void Update(int _roomID);

	// Đặt giới hạn load map
	void setLimitation(int x, int y, int width, int height);

	// Load map lên
	bool loadMap(string filePath);

	LPDIRECT3DDEVICE9 getDevice();
	LPDIRECT3DTEXTURE9 getTexture();
	vector<string> getStringMap();

private:
	std::string filePath;
	vector<string> stringMap;
	int roomID;
	Sprite *sprite;

	DeviceManager *deviceManager;

	//Start coordinate of the camera
	int camera_X;
	int camera_Y;

	//TODO: 
	int widthLimitation;
	int heightLimitation;

	LPDIRECT3DTEXTURE9 texture;

};