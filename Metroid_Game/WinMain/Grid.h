#pragma once
#include "GameObject.h"
#include "Math.h"
#include "Define.h"

#define ATTACK_DISTANCE 150.0f;

class Grid
{
private:
	static const int NUM_CELLS = 15;
	static const int CELL_SIZE = 128;
	float objPosX = 0;
	float objPosY = 0;
	GameObject * cells[NUM_CELLS][NUM_CELLS];
public:
	Grid();
	~Grid();

	void add(GameObject * object);
	void handleCell(GameObject * object);
	void handleCell(int x, int y);
	void handleCollision();
	void handleObject(GameObject * object, GameObject * other);

	void Update(GameObject * object, float posx, float posy);
};
