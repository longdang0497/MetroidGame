#pragma once
#include "GameObject.h"
#include <cmath>
#include "Math.h"
#include "Define.h"
#include "Collision.h"

class Grid {
private:
	int numOfRow;
	int numOfColumn;
	GameObject* cells[DEFINE_ROW][DEFINE_COLUMN];
	float deltaTime;
public:
	Grid();
	Grid(int height, int width);
	~Grid();

	void add(GameObject *object);
	void resetGrid(int width, int height);
	bool handleCell(GameObject *, int row, int column);
	bool handleCollision(GameObject * a, GameObject *b);
	bool handleObject(GameObject *a, GameObject *b);
	bool updateGrid(GameObject*, float newPosX, float newPosY);
	void setDeltaTime(float deltaTime);
	float getDeltaTime();

	void handleSamus(GameObject*, GameObject*, COLLISION_DIRECTION, float collisionTime);
};
