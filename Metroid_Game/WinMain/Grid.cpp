#include "Grid.h"
#include "Samus.h"
#include "MaruMari.h"
#include "Ridley.h"
#include "Kraid.h"
#include "KraidBoomerang.h"
#include "BulletKraid.h"
#include "BulletRidley.h"
#include "Missble.h"
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
	this->numOfRow = (int)ceil((float)height * BRICK_SIZE / CELL_SIZE);
	this->numOfColumn = (int)ceil((float)width * BRICK_SIZE / CELL_SIZE);

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
bool Grid::handleCell(GameObject* object, int row, int column) {
	bool isCollision = false;
	GameObject *cell = cells[row][column];
	if (object != NULL) {
		if ((object->getType() != BRICK || object->getType() != ITEM) && object->isActive) {
			// Đầu tiên là xét trong chính cell của nó trước
			if (this->handleObject(object, cell))
				isCollision = true;

			// Còn đây là xét với các cell kế bên
			if (row > 0)
				if (this->handleObject(object, cells[row - 1][column])) // phia tren
					isCollision = true;
			if (row < this->numOfRow - 1)
				if (this->handleObject(object, cells[row + 1][column])) // phia duoi
					isCollision = true;

			if (object->vx <= 0) {    // Neu van toc nang giam thi xet ben trai
				if (row > 0 && column > 0)
					if (this->handleObject(object, cells[row - 1][column - 1])) // trai tren
						isCollision = true;
				if (column > 0)
					if (this->handleObject(object, cells[row][column - 1])) // phia trai
						isCollision = true;
				if (column > 0 && row < numOfRow - 1)
					if (this->handleObject(object, cells[row + 1][column - 1])) // trai duoi
						isCollision = true;
			}
			else {
				if (row > 0 && column < this->numOfColumn - 1)
					if (this->handleObject(object, cells[row - 1][column + 1])) // phai tren
						isCollision = true;
				if (column < this->numOfColumn - 1)
					if (this->handleObject(object, cells[row][column + 1]))    // ben phai
						isCollision = true;
				if (column < this->numOfColumn - 1 && row < this->numOfRow - 1)
					if (this->handleObject(object, cells[row + 1][column + 1])) // phai duoi
						isCollision = true;
			}
			
		}
	}
	return isCollision;
}

// Dùng để xét giữa object đang xét với các object còn lại trong cell hoặc cell lân cận
// Nếu mà khoảng cách giữa object đang xét với các object khác nhỏ hơn khoảng cách có thể va chạm
// Lúc đó sẽ xét va chạm
bool Grid::handleObject(GameObject *object, GameObject* otherObject) {
	bool isCollision = false;
	while (otherObject != NULL) {
		if (object != otherObject && otherObject->isActive) {
			// Mình phải tính va chạm là từ khoảng cách giữa 2 điểm từ tâm của nó
			int x1 = (int)((object->pos_x + object->width/2));
			int y1 = (int)((object->pos_y + object->height/2));
			D3DXVECTOR2 objectPos(x1, y1);

			int x2 = (int)((otherObject->pos_x + otherObject->width/2));
			int y2 = (int)((otherObject->pos_y + otherObject->height/2));
			D3DXVECTOR2 otherPos(x2, y2);
			if (Math::distance(objectPos, otherPos) < 150) {
				if (handleCollision(object, otherObject))
					isCollision = true;
			}
		}
		otherObject = otherObject->nextUnit;
	}
	return isCollision;
}

// Xét va chạm và cập nhật tình trạng của 2 object
bool Grid::handleCollision(GameObject *object, GameObject *otherObject) {
	COLLISION_DIRECTION collisionDirection = NONE;
	float collisionTime = object->sweptAABB(otherObject, collisionDirection, this->getDeltaTime());
	
	if (collisionDirection != NONE) {
		if (object->getType() == SAMUS) {
			this->handleSamus(object, otherObject, collisionDirection, collisionTime);
		}
		else if (object->getType() == ZOOMER_PINK || object->getType() == ZOOMER_YELLOW) {
			this->handleZoomer(object, otherObject, collisionDirection, collisionTime);
		}
		else if (object->getType() == BULLET) {
			this->handleSamusBullet(object, otherObject, collisionDirection, collisionTime);
		}
		else if (object->getType() == SKREE) {
			this->handleSkree(object, otherObject, collisionDirection, collisionTime);
		}
		else if (object->getType() == RIDLEY) {
			this->handleRidley(object, otherObject, collisionDirection, collisionTime);
		}
		else if (object->getType() == KRAID) {
			this->handleKraid(object, otherObject, collisionDirection, collisionTime);
		}
		else if (object->getType() == KRAID_BOMERANG) {
			this->handleBoomerang(object, otherObject, collisionDirection, collisionTime);
		}
		else if (object->getType() == KRAID_BULLET) {
			this->handleKraidBullet(object, otherObject, collisionDirection, collisionTime);
		}
		else if (object->getType() == RIDLEY_BULLET) {
			this->handleRidleyBullet(object, otherObject, collisionDirection, collisionTime);
		}
		else if (object->getType() == MISSIBLE) {
			this->handleMissible(object, otherObject, collisionDirection, collisionTime);
		}
		else if (object->getType() == SKREE_BULLET) {
			this->handleSkreeBullet(object, otherObject, collisionDirection, collisionTime);
		}
		return true;
	}
	else {
		return false;
	} 
}

void Grid::handleSamus(GameObject* object, GameObject* otherObject, COLLISION_DIRECTION collisionDirection, float collisionTime) {
	Samus* samus = dynamic_cast<Samus*>(object);
	//object->pos_y += object->vy * collisionTime *this->getDeltaTime();
	OBJECT_TYPE otherObjectType = otherObject->getType();
	if (collisionDirection == BOTTOM)
	{
		samus->isBottom = true;
		switch (otherObjectType) {
		case BRICK: {
			samus->isCollideWithEnemy = false;
			samus->isFallAfterCollide = false;
			object->pos_y += object->vy * collisionTime *this->getDeltaTime();
			samus->isOnGround = true;
			if (samus->isJumping) {
				samus->isJumping = false;
				samus->isFalling = false;
				if (!samus->getIsBall()) {
					samus->pos_y -= (64 - samus->getHeight());
					samus->setWidth(32);
					samus->setHeight(64);
					switch (samus->GetState()) {
					case JUMP_RIGHT: case MORPH_RIGHT:case FADE_RIGHT:{
						samus->SetState(STAND_RIGHT);
						samus->isMorphing = false;
						break;
					}
					case JUMP_LEFT: case MORPH_LEFT: case FADE_LEFT:{
						samus->SetState(STAND_LEFT);
						samus->isMorphing = false;
						break;
					}
					case JUMP_SHOOT_UP_LEFT: {
						samus->SetState(STAND_SHOOT_UP_LEFT);
						break;
					}

					case JUMP_SHOOT_UP_RIGHT: {
						samus->SetState(STAND_SHOOT_UP_RIGHT);
						break;
					}
				}
				
				}
			}

		}break;

		case MARU_MARI: {
			samus->isBottom = false;
			samus->pos_y += samus->vy *this->deltaTime;
			otherObject->setActive(false);
		}break;
			
		case ZOOMER_YELLOW: case ZOOMER_PINK: case SKREE: case KRAID: case SKREE_BULLET: case RIDLEY_BULLET: case KRAID_BOMERANG: case KRAID_BULLET:{
			if (!samus->isCollideWithEnemy) {
				samus->collideEnemy();
			}
			else {
				samus->isBottom = false;
			}
			break;
		}
		case EXPLOSION_BOMB: {
			samus->isBottom = false;
			break;
		}
		}
	}
	else if (collisionDirection == TOP) {
		samus->isTop = true;
		switch (otherObjectType) {
		case BRICK: {
			object->pos_y += object->vy * collisionTime*this->getDeltaTime();

			break;
		}
		case ZOOMER_YELLOW: case ZOOMER_PINK: case SKREE: case KRAID: case SKREE_BULLET: case RIDLEY_BULLET: case KRAID_BOMERANG: case KRAID_BULLET: {
			if (!samus->isCollideWithEnemy) {
				samus->collideEnemy();
			}
			else {
				samus->isTop = false;
			}
			break;
		}
		case EXPLOSION_BOMB: {
			samus->isTop = false;
			break;
		}
		}
	}
	else if (collisionDirection == RIGHT) {
		samus->isRight = true;
		switch (otherObjectType) {
		case BRICK:{
			object->pos_x += object->vx * collisionTime*this->getDeltaTime();
			break;
		}
		case GATE: {
			Gate* gate = dynamic_cast<Gate*>(otherObject);
			if (!otherObject->isActive || gate->getGateState() == OPEN) {
				samus->isRight = false;
			}
			else {
				object->pos_x += object->vx * collisionTime*this->getDeltaTime();
			}
			break;
		}
		case GATE_BLOCK: {
			samus->isRight = false;
			break;
		}
		case MARU_MARI: {
			samus->isRight = false;
			samus->pos_x += samus->vx *this->deltaTime;
			otherObject->setActive(false);
			break;
		}
		case ZOOMER_YELLOW: case ZOOMER_PINK: case SKREE: case KRAID: case SKREE_BULLET: case RIDLEY_BULLET: case KRAID_BOMERANG: case KRAID_BULLET: {
			if (!samus->isCollideWithEnemy) {
				samus->collideEnemy();
			}
			else {
				samus->isRight = false;
			}
			break;
		}
		case EXPLOSION_BOMB: {
			samus->isRight = false;
			break;
		}
		}
	}
	else if (collisionDirection == LEFT) {
		samus->isLeft = true;
		switch (otherObjectType) {
		case BRICK: {
			object->pos_x += object->vx * collisionTime*this->getDeltaTime();
			break;
		}
		case GATE: {
			Gate* gate = dynamic_cast<Gate*>(otherObject);
			if (!otherObject->isActive || gate->getGateState() == OPEN) {
				samus->isLeft = false;
			}
			else {
				object->pos_x += object->vx * collisionTime*this->getDeltaTime();
			}
			break;
		}
		case GATE_BLOCK: {
			samus->isLeft = false;
			break;
		}
		case MARU_MARI: {
			samus->isLeft = false;
			samus->pos_x += samus->vx *this->deltaTime;
			otherObject->setActive(false);
			break;
		}
		case ZOOMER_YELLOW: case ZOOMER_PINK: case SKREE: case KRAID: case SKREE_BULLET: case RIDLEY_BULLET: case KRAID_BOMERANG: case KRAID_BULLET: {
			if (!samus->isCollideWithEnemy) {
				samus->collideEnemy();
			}
			else {
				samus->isBottom = false;
			}
			break;
		}
		case EXPLOSION_BOMB: {
			samus->isLeft = false;
			break;
		}
		}

	}

}

// Xử lý zoomer khi va chạm với các thể loại object
void Grid::handleZoomer(GameObject* object, GameObject* otherObject, COLLISION_DIRECTION collisionDirection, float collisionTime) {
	Zoomer* zoomer = dynamic_cast<Zoomer*>(object);

	OBJECT_TYPE type = otherObject->getType();
	switch (collisionDirection) {
	case BOTTOM: {
		zoomer->setIsBottomCollided(true);
		if (type == BRICK || type == ITEM || type == GATE || type == GATE_BLOCK || type == MARU_MARI) {
			object->pos_y += object->vy * collisionTime * deltaTime;
		}
		else if (type == BULLET) {
			zoomer->setHealth(zoomer->getHealth() - 20);
			zoomer->setIsBottomCollided(false);
			if (zoomer->getHealth() == 0)
			{
				zoomer->isActive = false;
				zoomer->Destroy(zoomer->pos_x, zoomer->pos_y);
			}
			else {
				zoomer->setIsEnemyFreezed(true);
			}
			Bullet* bullet = dynamic_cast<Bullet*>(otherObject);
			bullet->Reset();
			zoomer->setIsBottomCollided(false);
		}
		else if (type == MISSIBLE) {
			zoomer->setIsBottomCollided(false);
			zoomer->setHealth(0);
			zoomer->Destroy(zoomer->pos_x, zoomer->pos_y);
			Missible* bullet = dynamic_cast<Missible*>(otherObject);
			bullet->Reset(0.0f, 0.0f);
		}
		else if (type == EXPLOSION_BOMB) {
			object->pos_y += object->vy * deltaTime;
			zoomer->setIsBottomCollided(false);
		}
		else if (type == SAMUS) {
			Samus* samus = dynamic_cast<Samus*>(otherObject);
			if (!samus->isCollideWithEnemy) {
				samus->collideEnemy();
			}
			zoomer->setIsBottomCollided(false);
		}
		else if (type == ZOOMER_YELLOW || type == ZOOMER_PINK || type == SKREE) {
			object->pos_y += object->vy * this->deltaTime;
			zoomer->setIsBottomCollided(false);
		}
		break;

	}

	case TOP: {
		zoomer->setIsTopCollided(true);
		if (type == BRICK || type == ITEM || type == GATE || type == GATE_BLOCK || type == MARU_MARI) {
			object->pos_y += object->vy * collisionTime * deltaTime;
		}
		else if (type == BULLET) {

			zoomer->setHealth(zoomer->getHealth() - 20);
			zoomer->setIsTopCollided(false);
			if (zoomer->getHealth() == 0)
			{
				zoomer->isActive = false;
				zoomer->Destroy(zoomer->pos_x, zoomer->pos_y);
			}
			else {
				zoomer->setIsEnemyFreezed(true);
			}
			Bullet* bullet = dynamic_cast<Bullet*>(otherObject);
			bullet->Reset();
		}
		else if (type == EXPLOSION_BOMB) {
			object->pos_y += object->vy * deltaTime;
			zoomer->setIsTopCollided(false);
		}
		else if (type == SAMUS) {
			Samus* samus = dynamic_cast<Samus*>(otherObject);
			if (!samus->isCollideWithEnemy) {
				samus->collideEnemy();
			}
			zoomer->setIsTopCollided(false);
		}
		else if (type == ZOOMER_YELLOW || type == ZOOMER_PINK || type == SKREE) {
			object->pos_y += object->vy * this->deltaTime;
			zoomer->setIsTopCollided(false);
		}
		else if (type == MISSIBLE) {
			zoomer->setIsTopCollided(false);
			zoomer->setHealth(0);
			zoomer->Destroy(zoomer->pos_x, zoomer->pos_y);
			Missible* bullet = dynamic_cast<Missible*>(otherObject);
			bullet->Reset(0.0f, 0.0f);

		}
		break;
	}

	case LEFT: {
		zoomer->setIsLeftCollided(true);
		if (type == BRICK || type == ITEM || type == GATE || type == GATE_BLOCK || type == MARU_MARI) {
			object->pos_x += object->vx * collisionTime *deltaTime;
		}
		else if (type == BULLET) {

			zoomer->setHealth(zoomer->getHealth() - 20);
			zoomer->setIsLeftCollided(false);
			if (zoomer->getHealth() == 0)
			{
				zoomer->isActive = false;
				zoomer->Destroy(zoomer->pos_x, zoomer->pos_y);
			}
			else {
				zoomer->setIsEnemyFreezed(true);
			}
			Bullet* bullet = dynamic_cast<Bullet*>(otherObject);
			bullet->Reset();
		}
		else if (type == EXPLOSION_BOMB) {
			object->pos_y += object->vy * deltaTime;
			zoomer->setIsLeftCollided(false);
		}
		else if (type == SAMUS) {
			Samus* samus = dynamic_cast<Samus*>(otherObject);
			if (!samus->isCollideWithEnemy) {
				samus->collideEnemy();
			}
			zoomer->setIsLeftCollided(false);
		}
		else if (type == ZOOMER_YELLOW || type == ZOOMER_PINK || type == SKREE) {
			object->pos_x += object->vx * this->deltaTime;
			zoomer->setIsLeftCollided(false);
		}
		else if (type == MISSIBLE) {
			zoomer->setIsLeftCollided(false);
			zoomer->setHealth(0);
			zoomer->Destroy(zoomer->pos_x, zoomer->pos_y);
			Missible* bullet = dynamic_cast<Missible*>(otherObject);
			bullet->Reset(0.0f, 0.0f);
		}
		break;
	}

	case RIGHT: {
		zoomer->setIsRightCollided(true);
		if (type == BRICK || type == ITEM || type == GATE || type == GATE_BLOCK || type == MARU_MARI) {
			object->pos_x += object->vx * collisionTime *deltaTime;
		}
		else if (type == BULLET) {

			zoomer->setHealth(zoomer->getHealth() - 20);
			zoomer->setIsRightCollided(false);
			if (zoomer->getHealth() == 0)
			{
				zoomer->isActive = false;
				zoomer->Destroy(zoomer->pos_x, zoomer->pos_y);
			}
			else {
				zoomer->setIsEnemyFreezed(true);
			}
			Bullet* bullet = dynamic_cast<Bullet*>(otherObject);
			bullet->Reset();
		}
		else if (type == EXPLOSION_BOMB) {
			object->pos_y += object->vy * deltaTime;
			zoomer->setIsRightCollided(false);
		}
		else if (type == SAMUS) {
			Samus* samus = dynamic_cast<Samus*>(otherObject);
			if (!samus->isCollideWithEnemy) {
				samus->collideEnemy();
			}
			zoomer->setIsRightCollided(false);
		}
		else if (type == ZOOMER_YELLOW || type == ZOOMER_PINK || type == SKREE) {
			object->pos_x += object->vx * this->deltaTime;
			zoomer->setIsRightCollided(false);
		}
		else if (type == MISSIBLE) {
			zoomer->setIsRightCollided(false);
			zoomer->setHealth(0);
			zoomer->Destroy(zoomer->pos_x, zoomer->pos_y);
			Missible* bullet = dynamic_cast<Missible*>(otherObject);
			bullet->Reset(0.0f, 0.0f);
		}
		break;
	}
	}
}

void Grid::handleSamusBullet(GameObject* object, GameObject* otherObject, COLLISION_DIRECTION collisionDirection, float collisionTime) {
	if (!object->isActive)
		return;

	Bullet* bullet = dynamic_cast<Bullet*>(object);
	OBJECT_TYPE type = otherObject->getType();

	switch (collisionDirection) {
	case TOP: {
		bullet->setIsTop(true);
		if (type == BRICK || type == BULLET || type == ITEM || type == EFFECT 
			|| type == BOMB_ITEM || type == MARU_MARI
			|| type == ENERGY_ITEM) {
			object->pos_y += object->vy * collisionTime * this->getDeltaTime();
			bullet->Reset();
		}
		else if (type == ZOOMER_YELLOW || type == ZOOMER_PINK)
		{
			Zoomer* zoomer = dynamic_cast<Zoomer*>(otherObject);

			zoomer->setHealth(zoomer->getHealth() - 20);

			if (zoomer->getHealth() <= 0)
			{
				zoomer->isActive = false;
				zoomer->Destroy(zoomer->pos_x, zoomer->pos_y);
			}
			else {
				zoomer->setIsEnemyFreezed(true);
			}
			bullet->Reset();
		}
		break;
	}

	case BOTTOM: {
		bullet->setIsBottom(true);
		// Khong lam gi ca
		break;
	}

	case LEFT: {
		bullet->setIsLeft(true);
		if (type == BRICK || type == BULLET || type == ITEM || type == EFFECT
			|| type == BOMB_ITEM || type == MARU_MARI || type == ENERGY_ITEM) {
			object->pos_x += object->vx * collisionTime * this->getDeltaTime();
			bullet->Reset();
		}
		else if (type == ZOOMER_YELLOW || type == ZOOMER_PINK)
		{
			Zoomer* zoomer = dynamic_cast<Zoomer*>(otherObject);

			zoomer->setHealth(zoomer->getHealth() - 20);
			if (zoomer->getHealth() <= 0)
			{
				zoomer->isActive = false;
				zoomer->Destroy(zoomer->pos_x, zoomer->pos_y);
			}
			else {
				zoomer->setIsEnemyFreezed(true);
			}
			bullet->Reset();
		}
		else if (type == GATE)
		{
			Gate* gate = dynamic_cast<Gate*>(otherObject);
			if (gate->getGateState() == CLOSE) {
				gate->setTimeStartOpen(GetTickCount());
			}
			bullet->Reset();
		}
		else if (type == RIDLEY || type == KRAID) {
			bullet->Reset();
		}
		break;
	}

	case RIGHT: {
		bullet->setIsRight(true);
		if (type == BRICK || type == BULLET || type == ITEM || type == EFFECT
			|| type == BOMB_ITEM || type == MARU_MARI
			|| type == ENERGY_ITEM ) {
			object->pos_x += object->vx * collisionTime * this->getDeltaTime();
			bullet->Reset();
		}
		else if (type == ZOOMER_YELLOW || type == ZOOMER_PINK)
		{
			Zoomer* zoomer = dynamic_cast<Zoomer*>(otherObject);

			zoomer->setHealth(zoomer->getHealth() - 20);

			if (zoomer->getHealth() <= 0)
			{
				zoomer->isActive = false;
				zoomer->Destroy(zoomer->pos_x, zoomer->pos_y);
			}
			else {
				zoomer->setIsEnemyFreezed(true);
			}
			bullet->Reset();
		}
		else if (type == GATE)
		{
			Gate* gate = dynamic_cast<Gate*>(otherObject);
			if (gate->getGateState() == CLOSE) {
				gate->setTimeStartOpen(GetTickCount());
			}
			bullet->Reset();
		}
		else if (type == RIDLEY || type == KRAID) {
			bullet->Reset();
		}
		break;
	}
	}

	if (type == SAMUS) {
		bullet->setIsTop(false);
		bullet->setIsLeft(false);
		bullet->setIsBottom(false);
		bullet->setIsRight(false);
	}
}

void Grid::handleSkree(GameObject *object, GameObject *otherObject, COLLISION_DIRECTION collisionDirection, float collisionTime)
{
	if (otherObject->getType() == BRICK && collisionDirection == BOTTOM) {
		Skree* skree = dynamic_cast<Skree*>(object);
		skree->pos_x += skree->vx *collisionTime*this->getDeltaTime();
		skree->pos_y += skree->vy * collisionTime*this->getDeltaTime();
		skree->setVelocityX(0);
		skree->setVelocityY(0);
		skree->setHealth(0.0f);
		skree->setState(LANDED);
	}
	else if (otherObject->getType() == SAMUS && otherObject->isActive) {
		// khi va cham vs quai thi bi vang ra
		Samus* samus = dynamic_cast<Samus*>(otherObject);
		if (!samus->isCollideWithEnemy) {
			samus->collideEnemy();
		}
	}
	else if (otherObject->getType() == BULLET) {
		Skree* skree = dynamic_cast<Skree*>(object);
		skree->setHealth(skree->getHealth() - 20);
		
		if (skree->getHealth() == 0)
		{
			skree->isActive = false;
			skree->Destroy(skree->pos_x, skree->pos_y);
		}

		Bullet* bullet = dynamic_cast<Bullet*>(otherObject);
		bullet->Reset();
	}
	else if (otherObject->getType() == MISSIBLE) {
		Skree* skree = dynamic_cast<Skree*>(object);
		skree->setHealth(0);
		skree->isActive = false;
		skree->Destroy(skree->pos_x, skree->pos_y);

		Missible* missible = dynamic_cast<Missible*>(otherObject);
		missible->Reset(0.0f, 0.0f);
	}

}

void Grid::handleSkreeBullet(GameObject *object, GameObject *otherObject, COLLISION_DIRECTION collisionDirection, float collisionTime)
{
	BulletSkree *bullet = dynamic_cast<BulletSkree*>(object);
	if (otherObject->getType() == SAMUS) {
		// khi va cham vs quai thi bi vang ra
		Samus* samus = dynamic_cast<Samus*>(otherObject);
		if (!samus->isCollideWithEnemy) {
			samus->collideEnemy();
		}
	}
	bullet->Reset(0.0f, 0.0f);
	bullet->setIsBottom(true);
}

void Grid::handleRidley(GameObject *object, GameObject *otherObject, COLLISION_DIRECTION collisionDirection, float collisionTime)
{
	Ridley* ridley = dynamic_cast<Ridley*>(object);
	OBJECT_TYPE otherObjectType = otherObject->getType();
	switch (collisionDirection) {
	case BOTTOM: {
		ridley->setIsBottomCollided(false);
		switch (otherObjectType) {
		case BRICK: {
			ridley->pos_y += ridley->vy*collisionTime*this->getDeltaTime();
			if (!collisionTime == 0.0f) {
				ridley->setTimePush(GetTickCount());
			}
			if (ridley->getRidleyState() == FLY_LEFT) {
				ridley->setRidleyState(SIT_LEFT);
			}
			else if (ridley->getRidleyState() == FLY_RIGHT) {
				ridley->setRidleyState(SIT_RIGHT);
			}
			ridley->setIsBottomCollided(true);
			break;
		}
		}
		break;
	}

	case TOP: {

		break;
	}

	case LEFT: {

		break;
	}

	case RIGHT: {

		break;
	}
	}
}

void Grid::handleRidleyBullet(GameObject *object, GameObject *otherObject, COLLISION_DIRECTION collisionDirection, float collisionTime)
{
	BulletRidley* bullet = dynamic_cast<BulletRidley*>(object);
	if (otherObject->getType() == SAMUS) {
		Samus* samus = dynamic_cast<Samus*>(otherObject);
		if (!samus->isCollideWithEnemy) {
			samus->collideEnemy();
			bullet->Reset(0.0f, 0.0f);
		}
	}
	
}

void Grid::handleKraid(GameObject *object, GameObject *otherObject, COLLISION_DIRECTION collisionDirection, float collisionTime)
{
	Kraid *kraid = dynamic_cast<Kraid*>(object);
	switch (collisionDirection) {
	case BOTTOM: {
		if (otherObject->getType() == BRICK) {
			kraid->setIsBottom(true);
			kraid->pos_y += kraid->vy *this->deltaTime *collisionTime;
		}
		break;
	}
	case TOP: {

		break;
	}
	case RIGHT: {
		kraid->setIsRight(false);
		switch (otherObject->getType()) {
		case SAMUS: {
			Samus* samus = dynamic_cast<Samus*>(otherObject);
			if (!samus->isCollideWithEnemy) {
				samus->collideEnemy();
			}
			break;
		}
		case BULLET: {

			break;
		}
		case MISSIBLE: {
			break;
		}
		default: {
			kraid->pos_x += kraid->vy *this->deltaTime  *collisionTime;
			kraid->setIsRight(true);
		}
		}
		
		break;
	}
	case LEFT: {
		kraid->setIsLeft(false);
		switch (otherObject->getType()) {
		case SAMUS: {
			Samus* samus = dynamic_cast<Samus*>(otherObject);
			if (!samus->isCollideWithEnemy) {
				samus->collideEnemy();
			}
			break;
		}
		case BULLET: {
			kraid->setHealth(kraid->getHealth() - 10);

			if (kraid->getHealth() == 0)
			{
				kraid->isActive = false;
				kraid->Destroy(kraid->pos_x, kraid->pos_y);
			}


			Bullet* bullet = dynamic_cast<Bullet*>(otherObject);
			bullet->Reset();
			break;
		}
		case MISSIBLE: {

			break;
		}
		default: {
			kraid->pos_x += kraid->vy *this->deltaTime  *collisionTime;
			kraid->setIsLeft(true);
		}
		}
		break;
	}
	}
}

void Grid::handleBoomerang(GameObject *object, GameObject *otherObject, COLLISION_DIRECTION collisionDirection, float collisionTime)
{
	KraidBoomerang* boomerange = dynamic_cast<KraidBoomerang*>(object);
	
	boomerange->setIsBottom(true);
	boomerange->setIsFall(false);

	if (otherObject->getType() == SAMUS) {
		Samus* samus = dynamic_cast<Samus*>(otherObject);
		if (!samus->isCollideWithEnemy) {
			samus->collideEnemy();
			boomerange->Reset(0.0f, 0.0f);
		}
	}
	else {
		boomerange->Reset(0.0f, 0.0f);
	}
}

void Grid::handleKraidBullet(GameObject *object, GameObject *otherObject, COLLISION_DIRECTION collsionDirection, float collisionTime)
{
	BulletKraid* bullet = dynamic_cast<BulletKraid*>(object);
	bullet->Reset(0.0f, 0.0f);
	bullet->setIsBottom(true);

	if (otherObject->getType() == SAMUS) {
		Samus* samus = dynamic_cast<Samus*>(otherObject);
		if (!samus->isCollideWithEnemy) {
			samus->collideEnemy();
			bullet->Reset(0.0f, 0.0f);
		}
	}
	else {
		bullet->Reset(0.0f, 0.0f);
	}
}

void Grid::handleMissible(GameObject *object, GameObject *otherObject, COLLISION_DIRECTION collisionDirection, float collisionTime)
{
	Missible *missble = dynamic_cast<Missible*>(object);

	missble->setIsTop(true);

	switch (otherObject->getType()) {
	case BRICK: case GATE: {
		missble->Reset(0.0f, 0.0f);
		break;
	}
	case KRAID: {
		Kraid *kraid = dynamic_cast<Kraid*>(otherObject);
		kraid->setHealth(kraid->getHealth() - 100);
		if (kraid->getHealth() <= 0) {
			kraid->Destroy(kraid->pos_x, kraid->pos_y);
		}
		missble->Reset(0.0f, 0.0f);
		break;
	}
	case RIDLEY: {
		Ridley *ridley = dynamic_cast<Ridley*>(otherObject);
		ridley->setHealth(ridley->getHealth() - 100);
		if (ridley->getHealth() <= 0) {
			ridley->Destroy(ridley->pos_x, ridley->pos_y);
		}
		missble->Reset(0.0f, 0.0f);
		break;
	}

	case ZOOMER_YELLOW: case ZOOMER_PINK: {
		Zoomer *zoomer = dynamic_cast<Zoomer*>(otherObject);
		zoomer->setHealth(zoomer->getHealth() - 100);
		if (zoomer->getHealth() <= 0) {
			zoomer->Destroy(zoomer->pos_x, zoomer->pos_y);
		}
		missble->Reset(0.0f, 0.0f);
		break;
	}

	case SKREE: {
		Skree *skree = dynamic_cast<Skree*>(otherObject);
		skree->setHealth(skree->getHealth() - 100);
		if (skree->getHealth() <= 0) {
			skree->Destroy(skree->pos_x, skree->pos_y);
		}
		missble->Reset(0.0f, 0.0f);
		break;
	}
	case EXPLOSION_BOMB: {
		missble->Reset(0.0f, 0.0f);
		break;
	}
	}
	
}

void Grid::updateGrid(GameObject* object, float newPosX, float newPosY) {

	// Kiểm tra xem nó có thay đổi cell hay không
	int oldRow = floor(object->getlastPosY() / CELL_SIZE);
	int oldColumn = floor(object->getlastPosX() / CELL_SIZE);

	int newRow = floor(newPosY / CELL_SIZE);
	int newColumn = floor(newPosX / CELL_SIZE);

	// Nếu không thay đổi cell thì thoát ra
	if (oldRow == newRow && oldColumn == newColumn) {
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

	// Cập nhật lại vị trí last Post của object
	object->setlastPosX(object->getPosX());
	object->setlastPosY(object->getPosY());
}

void Grid::setDeltaTime(float deltaTime) {
	this->deltaTime = deltaTime;
}

float Grid::getDeltaTime() {
	return this->deltaTime;
}
