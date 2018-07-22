#pragma once
#include "GameObject.h"
#include "Math.h"
#include "Define.h"
#include "Collision.h"

#define ATTACK_DISTANCE 150.0f;

//struct Cell {
//	std::vector<GameObject *> objectList;
//};

class Grid
{
private:
	Collision * collide;
	static const int NUM_CELLS = 20;
	static const int CELL_SIZE = 128;
	GameObject * objectFollowing = nullptr;
	GameObject * cells[NUM_CELLS][NUM_CELLS];
	//GameObject * temp;
	//std::vector<Cell> m_cells;

	int followCellX;
	int followCellY;

	void handleGrid();
	//void handleCell(GameObject * object);
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
	
	/// Gets cell based on cell coordinates
	//Cell* getCell(int x, int y);
	/// Gets cell based on window coordinates
	//Cell* getCell(D3DXVECTOR2 pos);

	void CheckNewPos(int lastx, int lasty, int posx, int posy);
	void Update(float delta);
	void Render();
};
