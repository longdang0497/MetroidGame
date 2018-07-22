#pragma once
#include "GameObject.h"
#include "Sprite.h"

class TileObject : public GameObject
{
private:
	Sprite * tileMap;
public:
	char type;
	int x_pixel;
	int y_pixel;

	TileObject();
	~TileObject();

	void InitSprites(LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DTEXTURE9 texture);
	//============== OVERRIDE VIRTUAL METHOD ===================
	void Update(float t);
	void Render(char c, int index, D3DXVECTOR3 pos);
	//============== END OVERRIDE VIRTUAL METHOD ===============

	void setType(char value);
	char getType();

	void setXPixel(int value);
	int getXPixel();

	void setYPixel(int value);
	int getPixel();
};
