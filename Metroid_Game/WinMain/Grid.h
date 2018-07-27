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
public:
	Grid();
	Grid(int height, int width);
	~Grid();

	void add(GameObject *object);
	void handleCell(GameObject *, int row, int column);
	void handleCollision(GameObject * a, GameObject *b);
	void handleObject(GameObject *a, GameObject *b);
	void updateGrid(vector<GameObject*> listObject);

};