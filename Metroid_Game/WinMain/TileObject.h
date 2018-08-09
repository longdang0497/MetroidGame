#pragma once
#include "GameObject.h"
#include "Sprite.h"

class TileObject : public GameObject
{

public:
	TileObject(float x, float y);
	~TileObject();

	//============== OVERRIDE VIRTUAL METHOD ===================
	void Update(float t);
	void Render();
	//============== END OVERRIDE VIRTUAL METHOD ===============

};
