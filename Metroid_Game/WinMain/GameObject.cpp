#include "GameObject.h"

GameObject::GameObject()
{
}

OBJECT_TYPE GameObject::getType()
{
	return type;
}

void GameObject::setType(OBJECT_TYPE type)
{
	this->type = type;
}

void GameObject::InitSprites()
{
}

GameObject::~GameObject()
{
	//delete(sprite);
	//delete(manager);
}

void GameObject::Render()
{
}

void GameObject::Init(float posX, float posY)
{
	this->pos_x = posX;
	this->pos_y = posY;
	this->isActive = true;
}

void GameObject::Destroy()
{
}

float GameObject::sweptAABB(GameObject* object, COLLISION_DIRECTION& collisionDirection, float deltaTime) {
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	float vX = this->vx * deltaTime;
	float vY = this->vy * deltaTime;

	// tim khoang cach giua 2 vat the 
	if (vX > 0.0f) {
		xInvEntry = object->getPosX() - (this->pos_x + this->width);
		xInvExit = (object->getWidth() + object->getPosX()) - this->pos_x;
	}
	else {
		xInvEntry = (object->getPosX() + object->getWidth()) - this->pos_x;
		xInvExit = object->getPosX() - (this->pos_x + this->width);
	}

	if (vY > 0.0f) {
		yInvEntry = object->getPosY() - (this->getPosY() + this->getHeight());
		yInvExit = object->getPosY() + object->getHeight() - this->getPosY();
	}
	else {
		yInvEntry = (object->getPosY() + object->getHeight()) - this->getPosY();
		yInvExit = object->getPosY() - (this->getPosY() + this->getHeight());
	}

	// Tinh khoang thoi gian va cham va thoi gian het va cham
	float xEntry, yEntry;
	float xExit, yExit;
	if (vX == 0.0f) {
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else {
		xEntry = xInvEntry / vX;
		xExit = xInvExit /  vX;
	}

	if (vY == 0.0f) {
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else {
		yEntry = yInvEntry / vY;
		yExit = yInvExit / vY;
	}

	// Xac dinh truc nao bi va cham dau tien
	float entryTime = max(xEntry, yEntry);      // Cho biet thoi gian bat dau va cham
	float exitTime = min(xExit, yExit);			// Cho biet thoi gian ket thuc va cham

												// neu khong co va cham
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f) {
		collisionDirection = NONE;
		return deltaTime;
	}
	// Chỗ này có một cái hơi fun đó là khi vy = 0 mà pos_y dù nó thấp hơn vật khác vẫn bị xét là va chạm với cạnh, tương tự với vx
	else {
		if (xEntry > yEntry) { // này là đã va chạm ở trục Y rồi
			if (xInvEntry >= 0.0f) {
				if (this->pos_y + this->height <= object->pos_y || this->pos_y >= object->pos_y + object->height)
					collisionDirection = NONE;
				else
					collisionDirection = RIGHT;
			}
			else {
				if (this->pos_y >= object->pos_y + object->height || this->pos_y + this->height <= object->pos_y)
					collisionDirection = NONE;
				else
					collisionDirection = LEFT;
			}
		}
		else {			// Này là va chạm với trục X rồi nè
			if (yInvEntry >= 0.0f) {
				if (this->pos_x + this->width <= object->pos_x || this->pos_x >= object->pos_x + object->width)
					collisionDirection = NONE;
				else
					collisionDirection = BOTTOM;
			}
			else {
				if (this->pos_x + this->width <= object->pos_x || this->pos_x >= object->pos_x + object->width)
					collisionDirection = NONE;
				else
					collisionDirection = TOP;
			}
		}
	}

	// Trả về thời gian va chạm
	return entryTime;
}


void GameObject::Update(float t)
{
}

void GameObject::setVelocityX(float value)
{
	vx = value;
}

float GameObject::getVelocityX()
{
	return vx;
}

void GameObject::setVelocityY(float value)
{
	vy = value;
}

float GameObject::getVelocityY()
{
	return vy;
}

void GameObject::setPosX(int value)
{
	pos_x = value;
}

float GameObject::getPosX()
{
	return pos_x;
}

void GameObject::setPosY(int value)
{
	pos_y = value;
}

float GameObject::getPosY()
{
	return pos_y;
}

bool GameObject::isActivated()
{
	return isActive;
}

void GameObject::setActive(bool value)
{
	this->isActive = value;
}

void GameObject::setlastPosX(float posx)
{
	this->lastPosX = posx;
}

void GameObject::setlastPosY(float posy)
{
	this->lastPosY = posy;
}

float GameObject::getlastPosX()
{
	return this->lastPosX;
}

float GameObject::getlastPosY()
{
	return lastPosY;
}

void GameObject::setVelocityYLast(float value)
{
	this->vy_last = value;
}

float GameObject::getVelocityYLast()
{
	return this->vy_last;
}

void GameObject::setVelocityXLast(float value)
{
	vx_last = value;
}

float GameObject::getVelocityXLast()
{
	return vx_last;
}

void GameObject::setWidth(int value)
{
	width = value;
}

int GameObject::getWidth()
{
	return width;
}

void GameObject::setHeight(int value)
{
	height = value;
}

int GameObject::getHeight()
{
	return height;
}

float GameObject::getgravity()
{
	return gravity;
}

void GameObject::setgravity(float value)
{
	gravity = value;
}

void GameObject::SetBound(int objWidth, int objHeight)
{
	rigidBody.x = objWidth;
	rigidBody.y = objHeight;
}

RECT GameObject::GetBound()
{
	objBound.left = pos_x;
	objBound.right = pos_x + rigidBody.x;
	objBound.top = pos_y;
	objBound.bottom = pos_y - rigidBody.y;

	return objBound;
}

bool GameObject::getJump()
{
	return canJump;
}

void GameObject::setJump(bool value)
{
	canJump = value;
}

bool GameObject::getFall()
{
	return isFalling;
}

void GameObject::setFall(bool value)
{
	isFalling = value;
}