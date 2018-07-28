﻿#include "GameObject.h"

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

void GameObject::updateState()
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

bool GameObject::isCollide(RECT other)
{
	RECT object = this->GetBound();

	bool top = object.top >= other.top && object.top <= other.bottom;
	bool bot = object.bottom >= other.top && object.bottom <= other.bottom;
	bool right = object.right <= other.right && object.right >= other.left;
	bool left = object.left <= other.right && object.left >= other.left;

	//va chạm bên trái object
	bool first_case = (left && bot) || (left && top);

	//va chạm bên phải object
	bool second_case = (right && bot) || (right && top);

	bool third_caseA = left && (this->objBound.bottom >= other.bottom) && (this->objBound.top <= other.top);
	bool third_caseB = right && (this->objBound.bottom >= other.bottom) && (this->objBound.top <= other.top);
	bool third_case = third_caseA || third_caseB;

	bool fourth_caseA = top && (this->objBound.left >= other.left) && (this->objBound.right <= other.right);
	bool fourth_caseB = bot && (this->objBound.left >= other.left) && (this->objBound.right <= other.right);
	bool fourth_case = fourth_caseA || fourth_caseB;

	bool fifth_case_top = (this->objBound.top <= other.top) && (this->objBound.top < other.bottom);
	bool fifth_case_bot = (this->objBound.bottom > other.top) && (this->objBound.bottom >= other.bottom);
	bool fifth_case_left = (this->objBound.left <= other.left) && (this->objBound.left < other.right);
	bool fifth_case_right = (this->objBound.right > other.left) && (this->objBound.right >= other.right);
	bool fifth_case = fifth_case_top && fifth_case_bot &&fifth_case_right && fifth_case_left;


	if (first_case || second_case || third_case || fourth_case || fifth_case)
		return true;

	return false;
}

float GameObject::sweptAABB(GameObject * target, const float & DeltaTime)
{
	// ---------------======== Broad - Phasing ============-------------

	// delta velocity
	float deltaVX = ((this->vx) - (target->vx)) * DeltaTime;
	float deltaVY = ((this->vy) - (target->vy)) * DeltaTime;

	// tạo ra cái hộp bao quanh quỹ đạo của "this"
	RECT * broadPhaseBox = new RECT();

	if (deltaVX > 0.0f)	// left & right
	{
		broadPhaseBox->left = this->objBound.left;
		broadPhaseBox->right = this->objBound.right + deltaVX;
	}
	else
	{
		broadPhaseBox->left = this->objBound.left + deltaVX;
		broadPhaseBox->right = this->objBound.right;
	}

	if (deltaVY > 0.0f) // top & bottom
	{
		broadPhaseBox->top = this->objBound.top + deltaVY;
		broadPhaseBox->bottom = this->objBound.bottom;
	}
	else
	{
		broadPhaseBox->top = this->objBound.top;
		broadPhaseBox->bottom = this->objBound.bottom + deltaVY;
	}

	// --- xét coi Box có lồng vào target hay không ------------------

	// cạnh trái của hộp > cạnh phải của target
	if ((pos_x + broadPhaseBox->left) > (target->getPosX() + target->GetBound().right))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// cạnh phải của hộp < cạnh trái của target
	if ((pos_x + broadPhaseBox->right) < (target->getPosX() + target->GetBound().left))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// cạnh trên của hộp < cạnh dưới của target
	if ((pos_y + broadPhaseBox->top) < (target->getPosY() + target->GetBound().bottom))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// cạnh dưới của hộp > cạnh trên của target
	if ((pos_y + broadPhaseBox->bottom) > (target->getPosY() + target->GetBound().top))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	// end of Broad - Phasing
	// --------------------------===============================----------------------------


	// ---=== xét xem có lồng nhau ngay từ đầu không ===---
	if (this->isCollide(target->GetBound()))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 0.0f;
	}

	float dxEntry, dyEntry;
	float dxExit, dyExit;

	if (deltaVX > 0.0f)
	{
		dxEntry = (target->getPosX() + target->GetBound().left) - (this->pos_x + this->GetBound().right);
		dxExit = (target->getPosX() + target->GetBound().right) - (this->pos_x + this->GetBound().left);
	}
	else
	{
		dxEntry = (target->getPosX() + target->GetBound().right) - (this->pos_x + this->GetBound().left);
		dxExit = (target->getPosX() + target->GetBound().left) - (this->pos_x + this->GetBound().right);
	}

	if (deltaVY > 0.0f)
	{
		dyEntry = (target->getPosY() + target->GetBound().bottom) - (this->pos_y + this->GetBound().top);
		dyExit = (target->getPosY() + target->GetBound().top) - (this->pos_y + this->GetBound().bottom);
	}
	else
	{
		dyEntry = (target->getPosY() + target->GetBound().top) - (this->pos_y + this->GetBound().bottom);
		dyExit = (target->getPosY() + target->GetBound().bottom) - (this->pos_y + this->GetBound().top);
	}

	// thời gian va chạm của mỗi chiều
	float txEntry, tyEntry;
	float txExit, tyExit;

	if (deltaVX == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / deltaVX;
		txExit = dxExit / deltaVX;
	}

	if (deltaVY == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / deltaVY;
		tyExit = dyExit / deltaVY;
	}

	// --- thời gian va chạn theo 2 chiều
	float entryTimeScale = max(txEntry, tyEntry);
	float exitTimeScale = min(txExit, tyExit);

	// nếu như không có va chạm
	if ((entryTimeScale > exitTimeScale) || ((txEntry < 0.0f) && (tyEntry < 0.0f))
		|| (txEntry > 1.0f) || (tyEntry > 1.0f))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}


	// tính toán vector pháp tuyến của bề mặt va chạm
	if (txEntry > tyEntry)
	{
		if (dxEntry < 0.0f)
		{
			normalx = 1.0f;
			normaly = 0.0f;
		}
		else
		{
			normalx = -1.0f;
			normaly = 0.0f;
		}
	}
	else
	{
		if (dyEntry < 0.0f)
		{
			normalx = 0.0f;
			normaly = 1.0f;
		}
		else
		{
			normalx = 0.0f;
			normaly = -1.0f;
		}
	}

	// scale > 1.0f chưa va chạm
	// 0.0f < scale < 1.0f là có va chạm
	// 0.0f va chạm lồng vào nhau
	return entryTimeScale;
}

// di chuyển sát tường (xử lý va chạm)
void GameObject::Response(GameObject * target, const float & DeltaTime)
{
}

//bật ngược ra khi có va chạm
void GameObject::Deflect(GameObject * target, const float & DeltaTime, const float & CollisionTimeScale)
{
	// bật ra
	if (normalx > 0.1f)	// tông bên phải
	{
		if (vx < -0.0f)// đang chạy qua trái => văng ngược lại
			vx *= -1;
	}
	else if (normalx < -0.1f) // tông bên trái
	{
		if (vx > 0.0f)//	đang chạy qua phải => văng ngược lại
			vx *= -1;
	}

	if (normaly > 0.1f) // tông phía trên
	{
		if (vy > 0.0f)// đang rơi xuống => văng lên trên
			vy = 0.0f;
	}
	else if (normaly < -0.1f) // tông phía dưới
	{
		if (vy < -0.0f)// đang bay lên => văng xuống
			vy *= -1;
	}

	if (normaly != 0)
	{
		pos_x += vx * (CollisionTimeScale)* DeltaTime;
		pos_y += vy * (CollisionTimeScale)* DeltaTime;
	}
}

void GameObject::SlideFromGround(GameObject * target, const float & DeltaTime, const float & CollisionTimeScale)
{
	if (normalx > 0.1f)	// tông bên phải gạch
	{
		this->pos_x = (target->getPosX() + target->GetBound().right - this->GetBound().left) + 0.1f;
		pos_x -= vx * DeltaTime;
	}

	else if (normalx < -0.1f)// tông bên trái gạch
	{
		this->pos_x = (target->getPosX() + target->GetBound().left - this->GetBound().right) - 0.1f;
		pos_x -= vx * DeltaTime;
	}

	if (normaly > 0.1f) // trên xuống
	{
		this->pos_y = (target->pos_y + target->GetBound().top - this->GetBound().bottom) + 0.1f;
		pos_y -= vy * DeltaTime;
		vy = 0;
	}
	else if (normaly < -0.1f)	// tông ở dưới lên
	{		
		pos_y -= vy * DeltaTime;
		vy = 0;
	}
	return;
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

void GameObject::Translate(D3DXVECTOR2 vector)
{
	pos_x += vector.x;
	pos_y -= vector.y;
}

RECT GameObject::GetBound()
{
	if (currentSprite != nullptr)
	{
		objBound.left = pos_x;
		objBound.right = pos_x + currentSprite->getWidth();
		objBound.top = pos_y;
		objBound.bottom = pos_y + currentSprite->getHeight();
	}

	return objBound;
}