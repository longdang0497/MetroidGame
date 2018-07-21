#pragma once
#include "GameObject.h"
#include "Math.h"
#include "Define.h"
#include "Collision.h"

#define ATTACK_DISTANCE 150.0f;

class Grid
{
private:
	Collision * collide;
	static const int NUM_CELLS = 20;
	static const int CELL_SIZE = 128;
	GameObject * objectFollowing = nullptr;
	GameObject * cells[NUM_CELLS][NUM_CELLS];

	int followCellX;
	int followCellY;

	void handleGrid();
	void handleCell(GameObject * object);
	void handleCell(int x, int y);
	void handleCollision(GameObject * object_a, GameObject * object_b);
	void handleObject(GameObject * object, GameObject * other);

	void UpdateCells(int x, int y, float delta);
	void UpdateGrid(float delta);

	void RenderGrid();
	void RenderCells(int x, int y);

public:
	Grid();
	~Grid();

	void addFollowing(GameObject * object);
	void add(GameObject * object);
	

	void CheckNewPos(int lastx, int lasty, int posx, int posy);
	void Update(float delta);
	void Render();
};
