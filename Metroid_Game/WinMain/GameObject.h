#pragma once

#include <d3dx9.h>
#include "Sprite.h"
#include "Define.h"

class GameObject
{
public:
	friend class Grid;
	World * manager;	// con trỏ đến world để thao tác với các object ở world khi cần thiết
	Grid * grid;

	int width;
	int height;
	float pos_x;		// x postition of object
	float pos_y;		// y position of object
	float lastPosX;		
	float lastPosY;
	float friction = FRICTION;	//ma sát

	Sprite * currentSprite = nullptr;
	GameObject * previousUnit;
	GameObject * nextUnit;

	float vx;		// x velocity
	float vy;		// y velocity

	float vx_last; // last vx of object before stop ( to determine the direction of samus)
	float vy_last;

	float gravity;
	bool isOnGround = false;

	LPD3DXSPRITE spriteHandler;

	OBJECT_TYPE type;		//Loại GameObject, được định nghĩa trong file type
	bool isActive;	// Cho biết GameObject có đang hoạt động hay không
	//Sprite* sprite;
	DWORD last_time; // this is to control the animate rate of object
	RECT objBound;

	float collisionTimeScale; // thời gian va chạm

	float normalx;	// "vector pháp tuyến" để xét va chạm
	float normaly;

	bool pushedRightWall;
	bool pushesRightWall;

	bool pushedLeftWall;
	bool pushesLeftWall;

	bool wasOnGround;

	bool wasAtCeiling;
	bool isAtCeiling;
public:
	GameObject();
	~GameObject();

	//======================== GET - SET METHOD ================================
	OBJECT_TYPE getType();
	void setType(OBJECT_TYPE type);

	void SetOnGround(bool value) { isOnGround = value; };

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

	void setWidth(int value);
	int getWidth();

	void setHeight(int value);
	int getHeight();

	float getgravity();
	void setgravity(float value);

	/*void setNormalx(float value);
	float getNormalx();
	void setNormaly(float value);
	float getNormaly();*/

	void Translate(D3DXVECTOR2 vector);

	RECT GetBound();
	//===============================END GET - SET METHOD============================

	//=============================== VIRTUAL METHOD FOR INHERITANCE ================
	virtual void InitSprites();
	virtual void Update(float t);
	virtual void Render();
	virtual void updateState(); //thực hiện khi xét va chạm

	//Phương thức để active lại GameObject
	virtual void Init(float posX, float posY);

	// Hủy GameObject (Lưu ý: chỉ unactive chứ không delete GameObject)
	virtual void Destroy();

	// ============================== END VIRTUAL METHOD =============================

	// ============================== COLLISTION METHOD ==============================
	bool isCollide(RECT other);

	float sweptAABB(GameObject *target, const float &DeltaTime);

	// xử lý khi có va chạm
	virtual void Response(GameObject *target, const float &DeltaTime);
	void Deflect(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);
	virtual void SlideFromGround(GameObject *target, const float &DeltaTime, const float &CollisionTimeScale);
	// ============================== END COLLISTION METHOD ==========================
};
