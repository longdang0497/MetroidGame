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

float GameObject::sweptAABB(GameObject* object, float &normalX, float &normalY) {
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;

	// tim khoang cach giua 2 vat the 
	if (this->vx > 0.0f) {
		xInvEntry = object->getPosX() - (this->pos_x + this->width);
		xInvExit = (object->getWidth() + object->getPosX()) - this->pos_x;
	}
	else {
		xInvEntry = (object->getPosX() + object->getWidth()) - this->pos_x;
		xInvExit = object->getPosX() - (this->pos_x + this->width);
	}

	if (this->vy > 0.0f) {
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
	if (this->vx == 0.0f) {
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else {
		xEntry = xInvEntry / this->vx;
		xExit = xInvExit / this->vx;
	}

	if (this->vy == 0.0f) {
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else {
		yEntry = yInvEntry / this->vy;
		yExit = yInvExit / this->vy;
	}

	// Xac dinh truc nao bi va cham dau tien
	float entryTime = max(xEntry, yEntry);      // Cho biet thoi gian bat dau va cham
	float exitTime = min(xExit, yExit);			// Cho biet thoi gian ket thuc va cham

												// neu khong co va cham
	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f) {
		normalX = 0.0f;
		normalY = 0.0f;
		return 1.0f;
	}
	else {
		if (xEntry > yEntry) { // này là đã va chạm ở trục Y rồi
			if (xInvEntry < 0.0f) {  // Trường hợp nhân vật bị dính với object đang xét
				normalX = 1.0f;
				normalY = 0.0f;
			}
			else {					// Nếu chưa dính
				normalX = -1.0f;
				normalY = 0.0f;
			}
		}
		else {			// Này là va chạm với trục X rồi nè
			if (yInvEntry < 0.0f) {
				normalX = 0.0f;
				normalY = 1.0f;
			}
			else {
				normalX = 0.0f;
				normalY = -1.0f;
			}
		}
	}

	// Trả về thời gian va chạm
	return entryTime;
}

bool GameObject::isCollided(GameObject* otherObject) {
	RECT o1 = this->GetBound();
	RECT o2 = otherObject->GetBound();

	bool top = o1.top >= o2.top && o1.top <= o2.bottom;
	bool bot = o1.bottom >= o2.top && o1.bottom <= o2.bottom;
	bool right = o1.right <= o2.right && o1.right >= o2.left;
	bool left = o1.left <= o2.right && o1.left >= o2.left;

	bool first_case = (left && bot) || (left && top);
	bool second_case = (right && bot) || (right && top);

	bool third_caseA = left && (o1.bottom >= o2.bottom) && (o1.top <= o2.top);
	bool third_caseB = right && (o1.bottom >= o2.bottom) && (o1.top <= o2.top);
	bool third_case = third_caseA || third_caseB;

	bool fourth_caseA = top && (o1.left >= o2.left) && (o1.right <= o2.right);
	bool fourth_caseB = bot && (o1.left >= o2.left) && (o1.right <= o2.right);
	bool fourth_case = fourth_caseA || fourth_caseB;

	if (first_case || second_case || third_case || fourth_case)
		return true;

	return false;
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