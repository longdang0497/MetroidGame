#pragma once
#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_


#include <d3dx9.h>
#include "Sprite.h"
#include "Define.h"

class GameObject
{
public:
	World * manager;	// con trỏ đến world để thao tác với các object ở world khi cần thiết

	float pos_x;		// x postition of object
	float pos_y;		// y position of object
	float lastPosX;
	float lastPosY;
	float friction = FRICTION;	//ma sát

								/*float width;
								float height;*/

	float vx;		// x velocity
	float vy;		// y velocity

	float vx_last; // last vx of object before stop ( to determine the direction of samus)
	float vy_last;

	float gravity;

	LPD3DXSPRITE spriteHandler;

	OBJECT_TYPE type;		//Loại GameObject, được định nghĩa trong file type
	bool isActive;	// Cho biết GameObject có đang hoạt động hay không
	Sprite* sprite;
	DWORD last_time; // this is to control the animate rate of object
public:
	GameObject();
	~GameObject();

	//======================== GET - SET METHOD ================================
	OBJECT_TYPE getType();
	void setType(OBJECT_TYPE type);

	bool isActivated();
	void setActive(bool value);

	void setlastPosX(float posx);
	void setlastPosY(float posy);
	float getlastPosX();
	float getlastPosY();

	void setVelocityX(float value);
	float getVelocityX();
	void setVelocityY(float value);
	float getVelocityY();

	void setPosX(int value);
	float getPosX();
	void setPosY(int value);
	float getPosY();

	void setVelocityXLast(float value);
	float getVelocityXLast();
	void setVelocityYLast(float value);
	float getVelocityYLast();

	/*void setWidth(float value);
	float getWidth();

	void setHeight(float value);
	float getHeight();*/

	float getgravity();
	void setgravity(float value);
	//===============================END GET - SET METHOD============================

	//=============================== VIRTUAL METHOD FOR INHERITANCE ================
	virtual void InitSprites();
	virtual void Update(float t);
	virtual void Render();

	//Phương thức để active lại GameObject
	virtual void Init(float posX, float posY);

	// Hủy GameObject (Lưu ý: chỉ unactive chứ không delete GameObject)
	virtual void Destroy();

	// ============================== END VIRTUAL METHOD =============================
};
#endif // !_GAME_OBJECT_
