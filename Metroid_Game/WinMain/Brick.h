#pragma once
#include "GameObject.h"
class Brick :
	public GameObject
{

public:
	Brick();
	Brick(float x, float y, int width, int height);
	~Brick();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DTEXTURE9 texture);
	void Update(float t);
	void Render();
};

