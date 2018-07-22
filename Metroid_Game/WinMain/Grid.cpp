#include "Grid.h"
#include "Math.h"

Grid::Grid()
{
	collide = new Collision();
	//clear the grid
	for (int i = 0; i < NUM_CELLS; i++)
	{
		for (int j = 0; j < NUM_CELLS; j++)
			cells[i][j] = NULL;
	}

	// Allocate all the cells
	//const int BALLS_TO_RESERVE = 20;
	//m_cells.resize(NUM_CELLS);
	//for (int i = 0; i < m_cells.size(); i++) {
	//	m_cells[i].objectList.reserve(BALLS_TO_RESERVE);
	//}
}

Grid::~Grid()
{
}

void Grid::addFollowing(GameObject * object)
{
	objectFollowing = object;

}

void Grid::add(GameObject * object)
{
	//store the init position of object
	object->lastPosX = object->pos_x;
	object->lastPosY = object->pos_y;

	//determine which grid cells it is in.
	int cellX = (int)(object->pos_x / CELL_SIZE);
	int cellY = (int)(object->pos_y / CELL_SIZE);

	//Add to the front of list for the cell it's in.
	object->previousUnit = NULL;
	object->nextUnit = cells[cellX][cellY];
	cells[cellX][cellY] = object;

	if (object->nextUnit != NULL)
		object->nextUnit->previousUnit = object;
}

//Cell* Grid::getCell(int x, int y) {
//	if (x < 0) x = 0;
//	if (x >= NUM_CELLS) x = NUM_CELLS - 1;
//	if (y < 0) y = 0;
//	if (y >= NUM_CELLS) y = NUM_CELLS - 1;
//
//	return &m_cells[y * NUM_CELLS + x];
//}

//Cell* Grid::getCell(D3DXVECTOR2 pos) {
//	int cellX = (int)(pos.x / CELL_SIZE);
//	int cellY = (int)(pos.y / CELL_SIZE);
//
//	return getCell(cellX, cellY);
//}

//void Grid::handleCell(GameObject * object)
//{
//	GameObject * other;
//	while (object != NULL)
//	{
//		other = object->nextUnit;
//		while (other != NULL)
//		{
//			//if (object->pos_x == other->pos_x && object->pos_y == other->pos_y)
//				//handleAttack(object, other);
//			other = other->nextUnit;
//		}
//		object = object->nextUnit;
//	}
//
//	other = nullptr;
//	delete other;
//}

void Grid::handleCell(int x, int y)
{
	GameObject * object = cells[x][y];
	while (object != NULL)
	{
		handleObject(object, object->nextUnit);

		//try the neighboring cells
		//if any object in the neighboring cells is close enough to the edge
		//within the object to attack radius and we'll find the hit

		//the inner loop starts after the current object 
		//avoid comparing each pair of object compairing twice
		if (x > 0 && y > 0)
			handleObject(object, cells[x - 1][y - 1]);
		if (x > 0)
			handleObject(object, cells[x - 1][y]);
		if (y > 0)
			handleObject(object, cells[x][y - 1]);
		if (x > 0 && y < NUM_CELLS - 1)
			handleObject(object, cells[x - 1][y + 1]);

		object = object->nextUnit;
	}

	object = nullptr;
	delete object;
}

//Once all of the objects are nestled in their cells, we can let them start hacking at each other.
void Grid::handleCollision(GameObject * object_a, GameObject * object_b)
{
	bool isCollide = false;
	isCollide = collide->isInside(object_a->GetBound(), object_b->GetBound());
	if (isCollide == true)
	{
		MessageBox(NULL, L"Collided !!", L"Information", MB_OK);
	}
}

void Grid::handleObject(GameObject * object, GameObject * other)
{
	int attackDistance = 15;
	while (other != NULL)
	{
		D3DXVECTOR2 objectPos(object->pos_x, object->pos_y);
		D3DXVECTOR2 otherPos(other->pos_x, other->pos_y);
		if (Math::distance(objectPos, otherPos) < attackDistance)
			handleCollision(object, other);
		other = other->nextUnit;
	}
}

void Grid::UpdateCells(int x, int y, float delta)
{
	GameObject * object = cells[x][y];
	while (object != nullptr)
	{
		object->Update(delta);

		object = object->nextUnit;
	}
	object = nullptr;
	delete object;	
}

void Grid::UpdateGrid(float delta)
{
	for (int y = 0; y < NUM_CELLS; y++)
	{
		for (int x = 0; x < NUM_CELLS; x++)
		{
			if (Math::abs(x, followCellX) <= 5)
				if (Math::abs(y, followCellY) <= 5)
					UpdateCells(x,y,delta);
		}
	}
}

void Grid::RenderGrid()
{
	for (int y = 0; y < NUM_CELLS; y++)
	{
		for (int x = 0; x < NUM_CELLS; x++)
		{
			if (Math::abs(x, followCellX) <= 5)
				if (Math::abs(y, followCellY) <= 5)
					RenderCells(x, y);
		}
	}
}

void Grid::RenderCells(int x, int y)
{
	GameObject * object = cells[x][y];
	while (object != nullptr) 
	{
		object->Render();
		object = object->nextUnit;
	}

	object = nullptr;
	delete object;
}

void Grid::handleGrid()
{
	for (int y = 0; y < NUM_CELLS; y++)
	{
		for (int x = 0; x < NUM_CELLS; x++)
		{
			if (Math::abs(x, followCellX) <= 3)
				if (Math::abs(y, followCellY) <= 3)
					handleCell(x, y);
		}
	}

}

void Grid::CheckNewPos(int lastx, int lasty, int posx, int posy)
{
	//which cell the object was previously in
	int oldCellX = lastx;
	int oldCellY = lasty;

	//which cell the object is moving to
	int cellX = posx;
	int cellY = posy;

	//if object didn't change the cells at all, then finished.
	if (oldCellX == cellX && oldCellY == cellY) return;

	// Unlink it from the list of its old cell.
	if (objectFollowing->previousUnit != NULL)
		objectFollowing->previousUnit->nextUnit = objectFollowing->nextUnit;
	if (objectFollowing->nextUnit != NULL)
		objectFollowing->nextUnit->previousUnit = objectFollowing->previousUnit;

	// If it's the head of a list, remove it.
	if (cells[oldCellX][oldCellY] == objectFollowing)
		cells[oldCellX][oldCellY] = objectFollowing->nextUnit;

	// Add it back to the grid at its new cell.
	add(objectFollowing);
}

void Grid::Update(float delta)
{
	int lastFollowCellX = (int)(objectFollowing->lastPosX / CELL_SIZE);
	int lastFollowCellY = (int)(objectFollowing->lastPosY / CELL_SIZE);

	objectFollowing->Update(delta);	

	followCellX = (int)(objectFollowing->pos_x / CELL_SIZE);
	followCellY = (int)(objectFollowing->pos_y / CELL_SIZE);
	
	UpdateGrid(delta);
	//CheckNewPos(lastFollowCellX, lastFollowCellY, followCellX, followCellY);
	handleGrid();
}

void Grid::Render()
{
	objectFollowing->Render();
	RenderGrid();
}
