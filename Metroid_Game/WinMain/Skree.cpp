﻿#include "Skree.h"
#include "World.h"


Skree::Skree()
{
}

Skree::Skree(LPD3DXSPRITE spriteHandler, World * manager, OBJECT_TYPE enemy_type)
{
	this->spriteHandler = spriteHandler;
	this->setType(enemy_type);
	this->setActive(false);
	this->width = SKREE_WIDTH;
	this->height = SKREE_HEIGHT;
	this->grid = manager->getMetroid()->getGrid();
	this->manager = manager;

	// thiết lập animate rate ban đầu
	this->animate_rate = SKREE_STANDARD_ANIMATE_RATE;
	this->setState(ON_HANGING);
	this->health = 100;
	this->isDeath = false;
	this->isEnemyFreezed = false;
	this->vx = 0.0f;
	this->vy = 0.0f;
	this->timeStartDie = 0.0f;
}


Skree::~Skree()
{
	delete(this->skreeSprite);
}

void Skree::InitSprites(LPDIRECT3DDEVICE9 d3ddv, LPDIRECT3DTEXTURE9 texture)
{
	if (d3ddv == NULL) return;

	skreeSprite = new Sprite(spriteHandler, texture, SKREE_PATH, SKREE_WIDTH, SKREE_HEIGHT, SKREE_COUNT);
}

void Skree::Update(float t)
{
	if (!isActive || isDeath) return;
	if (this->isEnemyFreezed) {
		this->isEnemyFreezed = false;
		return;
	}

	this->setIsTop(false);
	this->setIsBottom(false);
	this->setIsLeft(false);
	this->setIsRight(false);
	this->setIsCollisionHandled(false);

	if (this->getState() != LANDED && this->getState() != SHOT) {
		//tinh khoang cach voi samus bang dinh luat Pytago
		float rs = sqrt(((abs)(pos_x - samusPosX)) * ((abs)(pos_x - samusPosX)) + ((abs)(pos_y - samusPosY) * (abs)(pos_y - samusPosY)));

		if (rs < SKREE_DISTANCE_TO_SAMUS && getState() != LANDED) {
			animate_rate = SKREE_BOOST_ANIMATE_RATE;
			setState(ON_FALLING);
			setActive(true);
			vy = SKREE_SPEED + 50;
			if (samusPosX < pos_x)
				vx = -SKREE_SPEED;
			else if (samusPosX > pos_x)
				vx = SKREE_SPEED;
			else
				vx = 0;
		}

		int oldRow = floor(this->pos_y / CELL_SIZE);
		int oldColumn = floor(this->pos_x / CELL_SIZE);

		this->grid->handleCell(this, oldRow, oldColumn);
		if (!isCollisionHandled) {
			if (!this->isBottom) {
				pos_y = this->pos_y + vy * t;
			}
			pos_x = this->pos_x + vx * t;
		}
		this->grid->updateGrid(this, this->pos_x, this->pos_y);
		DWORD now = GetTickCount();
		if (now - last_time > 1000 / animate_rate)
		{
			skreeSprite->updateSprite();
			last_time = now;
		}
	}
	else if (this->getState() == LANDED) {
		liveTime += t * 75;
		if (liveTime > SKREE_LIVE_TIME) {
			this->health = 0.0f;
			

			for (int i = 0; i < manager->skreeBullet.size(); i++) {
				manager->skreeBullet[i]->setActive(true);
				manager->skreeBullet[i]->setPosXSkree(this->pos_x);
				manager->skreeBullet[i]->setPosYSkree(this->pos_y);
			}

			this->Destroy(this->pos_x, this->pos_y);
		}
		else {
			DWORD now = GetTickCount();
			if (now - last_time > 1000 / animate_rate)
			{
				skreeSprite->updateSprite();
				last_time = now;
			}
		}
	}
}

void Skree::Render()
{
	if (isActive && !isDeath) {
		if (getState() != SHOT) {
			D3DXVECTOR3 position;
			position.x = pos_x;
			position.y = pos_y;
			position.z = 0;

			// Nếu không active thì không render
			if (!isActive)
				return;
			skreeSprite->drawSprite(skreeSprite->getWidth(), skreeSprite->getHeight(), position);
		}
	}
}

void Skree::setEnemyStatefromString(string _state)
{
}

void Skree::startMoving()
{
}

void Skree::setSamusLocation(float _posX, float _posY)
{
	this->samusPosX = _posX;
	this->samusPosY = _posY;
}

void Skree::handleBullet(int bulletType)
{
}

void Skree::Destroy()
{

}

void Skree::Destroy(float x, float y)
{
	if (this->health == 0)
	{
		manager->explodeEffect->setTimeSurvive(EFFECT_TIME_SURVIVE);
		if (manager->explodeEffect->getTimeSurvive() > 0)
		{
			manager->explodeEffect->setActive(true);
			manager->explodeEffect->setPosX(x + this->width/2);
			manager->explodeEffect->setPosY(y);
		}
		this->isDeath = true;
		this->isEnemyFreezed = false;

		this->reset();
		GameObject* object = static_cast<GameObject*>(this);
		object->setActive(false);
		this->grid->updateGrid(object, this->getPosX(), this->getPosY());
		this->setTimeStartDie(GetTickCount());
	}
}

void Skree::reset()
{
	this->pos_x = this->getInitPosX();
	this->pos_y = this->getInitPosY();
	this->setState(ON_HANGING);
}

void Skree::setState(SKREE_STATE state)
{
	this->state = state;
}

SKREE_STATE Skree::getState()
{
	return this->state;
}

void Skree::setIsLeft(bool isLeft)
{
	this->isLeft = isLeft;
}

bool Skree::getIsLeft()
{
	return this->isLeft;
}

void Skree::setIsRight(bool isRight)
{
	this->isRight = isRight;
}

bool Skree::getIsRight()
{
	return this->isRight;
}

void Skree::setIsTop(bool isTop)
{
	this->isTop = isTop;
}

bool Skree::getIsTop()
{
	return this->isTop;
}

void Skree::setIsBottom(bool isBottom)
{
	this->isBottom = isBottom;
}

bool Skree::getIsBottom()
{
	return this->isBottom;
}

void Skree::setIsCollisionHandled(bool isHandled)
{
	this->isCollisionHandled = isHandled;
}

bool Skree::getisCollisionHandled()
{
	return this->isCollisionHandled;
}

void Skree::setSamusPosX(float posX)
{
	this->samusPosX = posX;
}

float Skree::getSamusPosX()
{
	return this->samusPosX;
}

void Skree::setSamusPosY(float posY)
{
	this->samusPosY = posY;
}

float Skree::getSamusPosY()
{
	return this->samusPosY;
}

void Skree::setRange(float range)
{
	this->range = range;
}

float Skree::getRange()
{
	return this->range;
}

void Skree::setLiveTime(float liveTime)
{
	this->liveTime = liveTime;
}

float Skree::getLiveTime()
{
	return this->liveTime;
}
