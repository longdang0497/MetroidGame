#include "Grid.h"

// Lưu vào mảng 2 chiều
// Height khi quy đổi ra sẽ là row -> pos_y tương ứng với row
// Width khi quy đổi ra sẽ là column -> pos_x tương ứng column

Grid::Grid() {
	numOfRow = DEFINE_ROW;
	numOfColumn = DEFINE_COLUMN;
	for (int i = 0; i < numOfRow; i++)
	{
		for (int j = 0; j < numOfColumn; j++)
			cells[i][j] = NULL;
	}
	this->deltaTime = 0.0f;
}

Grid::Grid(int height, int width) {
	this->numOfRow = (int)ceil(height * BRICK_SIZE / CELL_SIZE);
	this->numOfColumn = (int)ceil(width * BRICK_SIZE / CELL_SIZE);

	for (int i = 0; i < numOfRow; i++)
	{
		for (int j = 0; j < numOfColumn; j++)
			cells[i][j] = NULL;
	}
	this->deltaTime = 0.0f;
}

Grid::~Grid() {
	
}

// Cái này là dùng danh sách liên kết đôi để lưu trữ và truy xuất object
// Nếu mà mình xác định vị trí object thuộc cell nào rồi thì mình đưa nó vào đầu danh sách liên kết đôi đó
// Ở đây 1 cell là 1 danh sách liên kết đôi
// Giải thuật ở dưới là thêm vào đầu dslk đôi
void Grid::add(GameObject* object) {
	// Lưu trữ lại giá trị cũ của object sau mỗi lần update
	object->setlastPosX(object->getPosX());
	object->setlastPosY(object->getPosY());

	// Xác định object đang nằm ở grid nào
	int column = floor(object->getPosX() / CELL_SIZE); // trừ đi 1 do mảng bắt đầu từ 0
	int row = floor(object->getPosY() / CELL_SIZE);


	// Thêm object vào đầu của list
	object->previousUnit = NULL;
	object->nextUnit = cells[row][column];
	cells[row][column] = object;

	if (object->nextUnit != NULL) {
		object->nextUnit->previousUnit = object;
	}
}

void Grid::resetGrid(int width, int height) {
	this->numOfRow = (int)ceil(height * BRICK_SIZE / CELL_SIZE);
	this->numOfColumn = (int)ceil(width * BRICK_SIZE / CELL_SIZE);

	for (int i = 0; i < numOfRow; i++)
	{
		for (int j = 0; j < numOfColumn; j++)
			cells[i][j] = NULL;
	}
	this->deltaTime = 0.0f;
}

// Dùng để xét cái ô cell hiện tại, như là va chạm của object mình đang xét với các object còn lại
// Kế bên đó là xét với các cell lân cận
// Theo người ta nói các cell càn xét thêm là:
//		1 ô trên,
//		1 ô trái trên
//		1 ô trái
//		1 ô trái dưới
// Ở đây ta cho vào vòng lặp là xét tất cả các object với nhau
void Grid::handleCell(GameObject* object, int row, int column) {
	GameObject *cell = cells[row][column];
	if (object != NULL) {
		if ((object->getType() != BRICK || object->getType() != ITEM) && object->isActive != false) {
			// Đầu tiên là xét trong chính cell của nó trước
			this->handleObject(object, cell);

			// Còn đây là xét với các cell kế bên
			if (row > 0 && column > 0)
				this->handleObject(object, cells[row - 1][column - 1]); // trai tren
			if (row > 0)
				this->handleObject(object, cells[row - 1][column]); // phia tren
			if (column > 0)
				this->handleObject(object, cells[row][column - 1]); // phia trai
			if (column > 0 && row < numOfRow - 1)
				this->handleObject(object, cells[row - 1][column + 1]); // trai duoi
		}
	}
}

// Dùng để xét giữa object đang xét với các object còn lại trong cell hoặc cell lân cận
// Nếu mà khoảng cách giữa object đang xét với các object khác nhỏ hơn khoảng cách có thể va chạm
// Lúc đó sẽ xét va chạm
void Grid::handleObject(GameObject *object, GameObject* otherObject) {
	while (otherObject != NULL) {
		if (object != otherObject) {
			// Mình phải tính va chạm là từ khoảng cách giữa 2 điểm từ tâm của nó
			int x1 = (int)((object->pos_x + object->width) / 2);
			int y1 = (int)((object->pos_y + object->height) / 2);
			D3DXVECTOR2 objectPos(x1, y1);

			int x2 = (int)((otherObject->pos_x + otherObject->width) / 2);
			int y2 = (int)((otherObject->pos_y + otherObject->height) / 2);
			D3DXVECTOR2 otherPos(x2, y2);
			if (Math::distance(objectPos, otherPos) < 50) {
				handleCollision(object, otherObject);
			}
		}
		otherObject = otherObject->nextUnit;
	}
}

// Xét va chạm và cập nhật tình trạng của 2 object
void Grid::handleCollision(GameObject *object, GameObject *otherObject) {
	COLLISION_DIRECTION collisionDirection = NONE;
	float collisionTime = object->sweptAABB(otherObject, collisionDirection, this->getDeltaTime());
	float remainingTime = 1.0f - collisionTime;
	if (remainingTime != 0.0f && remainingTime < 1.0f) {
		if (object->getType() == SAMUS) {
			object->setActive(false);
		}
	}
}

// Ta sẽ tính toán và cập nhật vị trí của các object đó đang thuộc grid nào, bao gồm:
//		Samus
//		Đạn
//		Enemy
void Grid::updateGrid(vector<GameObject*> listObject) {
	for (int i = 0; i < listObject.size(); i++) {
		GameObject* object = listObject[i];
		
		// Kiểm tra xem nó có thay đổi cell hay không
		int oldRow = floor(object->getlastPosY() / CELL_SIZE);
		int oldColumn = floor(object->getlastPosX() / CELL_SIZE);

		int newRow = floor(object->getPosY() / CELL_SIZE);
		int newColumn = floor(object->getPosX() / CELL_SIZE);

		// Cập nhật lại vị trí last Post của object
		object->setlastPosX(object->getPosX());
		object->setlastPosY(object->getPosY());

		// Nếu không thay đổi cell thì thoát ra
		if (oldRow == newRow && oldColumn == newColumn) {
			this->handleCell(object, oldRow, oldColumn);
			return;
		}


		// Xóa object ra khỏi cell hiện tại và cập nhật và cell mới
		if (object->previousUnit != NULL)
			object->previousUnit->nextUnit = object->nextUnit;
		if (object->nextUnit != NULL)
			object->nextUnit->previousUnit = object->previousUnit;

		// Nếu object đang là đứng đầu
		if (cells[oldRow][oldColumn] == object)
			cells[oldRow][oldColumn] = object->nextUnit;

		this->add(object);

		this->handleCell(object, newRow, newColumn);
	}
}

void Grid::setDeltaTime(float deltaTime) {
	this->deltaTime = deltaTime;
}

float Grid::getDeltaTime() {
	return this->deltaTime;
}