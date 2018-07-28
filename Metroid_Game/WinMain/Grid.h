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
	void handleCell(GameObject *, int row, int column);
	void handleCollision(GameObject * a, GameObject *b);
	void handleObject(GameObject *a, GameObject *b);
	void updateGrid(vector<GameObject*> listObject);
	void setDeltaTime(float deltaTime);
	float getDeltaTime();
};