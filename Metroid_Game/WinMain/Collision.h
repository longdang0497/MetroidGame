#pragma once
#include "Define.h"
#include <algorithm>
#include <string>
#include "GameObject.h"
using namespace std;

// Bản chất của thuật toán là tính toán thời gian va chạm của object mình đang xét với một object khác
// Ví dụ như khi ta đặt quản lý va chạm cho người chơi, nếu người chơi va chạm với gạch thì sẽ update trạng thái nhân vật là bị trượt xuống
// Nếu người chơi va chạm với quá thì sẽ bị đẩy lùi
// Còn khi xét quái va chạm với 
class Collision {
private:
	float x, y;
	float width, height;
	float vX, vY;
	float normalX, normalY;
	float remainingTime;
public:
	Collision();
	Collision(float x, float y, float width, float height, float vX, float vY);
	~Collision();

	float sweptAABB(GameObject* object, float &normalX, float &normalY);
	virtual void update(GameObject *object);


	float getX();
	void setX(float x);

	float getY();
	void setY(float y);

	float getWidth();
	void setWidth(float width);

	float getHeight();
	void setHeight(float height);

	float getVX();
	void setVX(float vX);

	float getVY();
	void setVY(float vY);

	float getNormalX();
	float getNormalY();
	float getRemainingTime();
};