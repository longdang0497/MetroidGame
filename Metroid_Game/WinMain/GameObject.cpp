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

RECT GameObject::GetBound()
{
	objBound.left = pos_x;
	objBound.right = pos_x + currentSprite->getWidth();
	objBound.top = pos_y;
	objBound.bottom = pos_y - currentSprite->getHeight();

	return objBound;
}